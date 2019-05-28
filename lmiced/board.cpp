#include "board.h"
#include "resource.h"
#include "lmiced.h"
#include "lmice_eal_shm.h"

void* board_open(lmid_t id, int size) {
    int ret;
    lmice_shm_t shm;

    eal_shm_zero(&shm);
    eal_shm_hash_name(id, shm.name);
    shm.size = size;

    ret = eal_shm_create(&shm);
    if(ret != 0)
        return nullptr;
    return shm.addr;
}

void* board_address(lmfd_t fd, unsigned int pos) {
    return nullptr;
}

lmfd_t board_create(lmid_t id, int size) {
    int ret;
    lmice_shm_t shm;

    /* 0. 查找依赖项 */
    lmfd_t brd_fd = 0;
    char* brd_item;
    brd_item = eal_list_find(lmapp->brd_list, LM_EMPTY, &brd_fd);
    if(brd_item == 0) {

    }

    /* 1. 创建 共享内存 */
    eal_shm_zero(&shm);
    eal_shm_hash_name(id, shm.name);
    shm.size = size;

    ret = eal_shm_create(&shm);
    if(ret != 0) return 0;

    /* 初始化内存区域 */
    memset(shm.addr, 0, size);


    /* 2. 注册 区域 区域列表 */
    lmlist_t * brdlist = lmapp->brd_list;
    lmbrd_t *brd;
    lmbrd_t *brd_workable = nullptr;
    bool find = false;
    do {
        brd = reinterpret_cast<lmbrd_t*>(brdlist->item);
        uint32_t pos = 1;
        for(; pos <= brdlist->count; ++pos,++brd) {
            if(brd->flags == LM_EMPTY) {
                find = true;
                break;
            }
            /* 可用于创建区域列表的区域 */
            if(brd_workable == nullptr
                    && (brd->size - brd->pos) >=LMBRDLIST_SIZE ) {
                brd_workable = brd;
            }
        }
        /* 已经找到，注册 退出循环 */
        if(find == true) {
            lmbrd_t* item = reinterpret_cast<lmbrd_t*>(brdlist->item);
            item->fd = brdlist->base + pos;
            item->size = size;
            item->pos = 0;
            item->flags = LM_ALIVE;

            brd_fd = item->fd;
            break;
        }

        if(brdlist->next_board == LM_EMPTY) {
            lmlist_t *newlist = nullptr;
            /* 区域列表已满, 创建新区域列表 */
            if(brd_workable != nullptr) {
                /* 有可用区域 */
                /* 分配BRDLIST空间 */
                brdlist->next_board = brd_workable->fd;
                brdlist->next_pos = brd_workable->pos;

                brd_workable->pos -= LMBRDLIST_SIZE;

                void* addr = board_address(brdlist->next_board, brdlist->next_pos);

                newlist = reinterpret_cast<lmlist_t *>(addr);
                eal_list_init(newlist, sizeof(lmbrd_t), LMBRD_COUNT);
                newlist->base = brdlist->base + brdlist->count;

                /*注册资源 共享区域 */
                lmbrd_t* item = reinterpret_cast<lmbrd_t*>(newlist->item);
                item->fd = newlist->base + 1;
                item->size = BOARD_LENGTH;
                item->pos = 0;
                item->flags = LM_ALIVE;

                brd_fd = item->fd;
            } else {
                /* 无可用区域 */
                /* 在新建区域上创建 区域列表 */
                newlist = reinterpret_cast<lmlist_t*>(shm.addr);
                eal_list_init(newlist, sizeof(lmbrd_t), LMBRD_COUNT);
                newlist->base = brdlist->base + brdlist->count;

                brdlist->next_board = newlist->base + 1;
                brdlist->next_pos = 0;

                /*注册资源 共享区域 */
                lmbrd_t* item = reinterpret_cast<lmbrd_t*>(newlist->item);
                item->fd = newlist->base + 1;
                item->size = BOARD_LENGTH;
                item->pos = LMBRDLIST_SIZE;
                item->flags = LM_ALIVE;

                brd_fd = item->fd;
            }

            break;
        } else {
            /* 查找下一个区域列表 */
            void* addr = board_address(brdlist->next_board, brdlist->next_pos);
            brdlist = reinterpret_cast<lmlist_t *>(addr);
        }
    } while(brdlist != nullptr);

    /* 3 注册 区域映射 */
    int fd = LM_EMPTY;
    char* item_data;
    uint32_t item_size = sizeof(lmbmp_t);
    uint32_t item_count = LMBMP_COUNT;
    lmlist_t *item_list = lmapp->map_list;

    /* 查找 映射列表 */
    item_data = eal_list_find(item_list, LM_EMPTY, &fd);
    if(item_data == 0) {
        /* 映射列表已满，创建区域映射列表资源 */

        item_list = lmapp->res_list;
        item_size = sizeof(lmres_t);
        item_count = LMRES_COUNT;
        /* 查找 资源列表 */
        item_data = eal_list_find(item_list, LM_EMPTY, &fd);
        if(item_data == 0) {
            /* 资源列表已满， 创建资源列表 */
        } else {

        }
    }
    if(item_data) {
        lmres_init_bmp( reinterpret_cast<lmbmp_t*>(item_data), /* 区域映射 */
                        fd, /* 描述符 */
                        shm.size, /* 区域大小 */
                        shm.addr, /* 区域地址 */
                        shm.fd/* 区域句柄 */);
    }

    return 0;
}
