#include "lmice_eal_list.h"

void* board_address(lmfd_t fd, unsigned int pos);

lmlist_t* eal_list_init(void* addr, uint32_t size, uint32_t count) {
    lmlist_t* l=(lmlist_t*)addr;

    size_t bytes = sizeof(lmlist_t) - sizeof(char[8]) + size*count;
    memset(l, 0, bytes);
    l->bytes = bytes;
    l->base = 0;
    l->lock = 0;
    l->size = size;
    l->count = count;
    l->next_board = 0;
    l->next_pos = 0;

    return l;
}

char* eal_list_find(lmlist_t* item_list, int flag, int* item_fd) {
    char* item_data = 0;
    int item_find = 0;
    do {
        item_data = item_list->item;
        /* 查找列表 */
        for(size_t pos = 1; pos <= item_list->count; ++ pos, item_data += item_list->size) {
            lmitem_t* item = (lmitem_t*)(item_data);
            if(item->flags == flag) {
                *item_fd = item_list->base+pos;
                item_find = 1;
                break;
            }
        }
        /* 已经找到，退出 */
        if(item_find==1) {
            break;
        }

        if(item_list->next_board != 0) {
            /* 查找下一个列表 */
            void* addr = board_address(item_list->next_board, item_list->next_pos);
            item_list = (lmlist_t *)(addr);
        } else {
            /* 到达列表末尾 */
           break;
        }
    } while(item_list);

    if(item_find)
        return item_data;
    return 0;
}
