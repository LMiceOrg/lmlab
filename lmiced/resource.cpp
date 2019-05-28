#include "resource.h"
#include "board.h"
#include "lmiced.h"
#include "lmice_eal_hash.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define BOARD_NAME "/private/tmp/LMiced V1.0 Board %03d"


static lmlist_t* lmres_lastlist(lmlist_t* ll) {
    do {
        if(ll->next_board != LM_EMPTY) {
            void* addr = board_address(ll->next_board, ll->next_pos);
            ll = reinterpret_cast<lmlist_t*>(addr);
        } else {
            break;
        }
    } while(true);
    return ll;
}


static lmres_t* lmres_create_reslist(lmlist_t* ll) {
    lmbrd_t* brd = reinterpret_cast<lmbrd_t*>(lmapp->brd_list->item);
    lmbrd_t* brd_empty= nullptr;
    lmres_t* item;
    bool find = false;

    /* 遍历 共享区域列表 */
    for(size_t i=0; i< lmapp->brd_list->count; ++i,++brd) {

        /* 找到第一个可用 空共享区域 */
        if(brd_empty == nullptr && brd->flags == LM_EMPTY) {
            brd_empty = brd;
            brd_empty->fd = i+1;
        }


        if(brd->flags == LM_ALIVE) {
            /* 活动共享区域 */
            int remain = (brd->size - brd->pos);
            if(remain >= LMRESLIST_SIZE) {
                /* 拥有可分配空间 */
                ll->next_board = brd->fd;
                ll->next_pos = brd->pos;
                brd->pos += LMRESLIST_SIZE;
                find = true;
                break;
            }
        }
    }


    if(find == false && brd_empty != nullptr) {
        /* 无可分配空间 共享区域列表未满 */
        char name[512];
        memset(name, 0, sizeof(name));
        snprintf(name, sizeof(name), BOARD_NAME, brd_empty->fd);
        lmid_t board_id = eal_hash64_fnv1a(name, strlen(name));
        void* addr = board_open(board_id, BOARD_LENGTH);
    } else if(find == false && brd_empty == nullptr) {
        /* 无可分配空间 共享区域列表已满 */
    }
    return nullptr;
}

static lmres_t* lmres_find_first(lmlist_t* ll) {
    lmres_t * item = reinterpret_cast<lmres_t*>(ll->item);
    bool find = false;
    for(size_t i=0; i< ll->count; ++i, ++item) {
        if( item->flags == LM_EMPTY ) {
            find = true;
            break;
        }
    }
    if(find == false) {
        if( ll->next_board == LM_EMPTY) {
            item = nullptr;
        } else {
            lmlist_t* next;
            void* addr =
                    board_address(ll->next_board, ll->next_pos);
            next = reinterpret_cast<lmlist_t*>(addr);
            item = lmres_find_first(next);
        }
    }

    return item;

}

lmfd_t lmres_create_list(lmfd_t type, uint32_t size, uint32_t count) {
    /* 1. 从资源列表中查找一个可用数据 */
    lmres_t* res = nullptr;
    lmlist_t* lst = lmapp->res_list;
    res = lmres_find_first(lst);

    if(res == nullptr)
    {
        // 创建资源列表
        lmres_create_reslist(lst);
    }
    //lmapp->res_list
    return 0;
}
void* lmres_open(lmfd_t);

void lmres_init_bmp(void* item, int fd, uint32_t size, void* addr, void* handle){
    lmbmp_t* bmp = reinterpret_cast<lmbmp_t*>(item);
    bmp->addr = addr;
    bmp->fd = fd;
    bmp->flags = LM_ALIVE;
    bmp->handle = handle;
    bmp->size = size;
}


void* lmres_malloc(uint32_t size) {
    lmlist_t *bmp_list = lmapp->map_list;
    lmlist_t *brd_list = lmapp->brd_list;
    void* addr = nullptr;

    do {
        lmbrd_t* brd = reinterpret_cast<lmbrd_t*>(brd_list->item);
        for(size_t i=0; i<brd_list->count; ++i,++brd) {
            if(brd->flags == LM_ALIVE && (brd->size - brd->pos) >= size) {
                addr = board_address(brd->fd, brd->pos);
                brd->pos += size;
                break;
            }
        }
        if(addr == nullptr && brd_list->next_board != LM_EMPTY) {
            brd_list = reinterpret_cast<lmlist_t*>(
                        board_address(brd_list->next_board,brd_list->next_pos) );
        }
    } while(brd_list);

    return addr;
}
