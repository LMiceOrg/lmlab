///** Copyright 2018, 2019 He Hao<hehaoslj@sina.com> */

//#include <stdio.h>

//#include "lmiced.h"
//#include "board.h"
//#include "resource.h"
//#include "lmrte.hpp"

//#include "lmice_eal_shm.h"
//#include "lmice_eal_list.h"
//#include "lmice_trace.h"

//#define SERVER_BOARD_NAME "/private/tmp/LMiced V1.0 Board 000"
//#define RESOURCE_LIST_NAME "Lmice resource list type"

// lmapp_t* lmapp;

int main() {
  //    int ret;
  //    SIZE_T sz = GetLargePageMinimum();
  //    lmice_info_print("Lmice daemon starting...\n");
  //    lmice_info_print("page size %ld\n", sz);
  //    /** 1. 初始化服务 */
  //    ret = lmice_server_create();

  //    if(ret != 0) return 0;
  //}

  // int lmice_server_create() {
  //    int ret = 0;
  //    /** 1. 打开平台/检查平台是否存在 */
  //    constexpr uint64_t board_id = eal_hash64_fnv1a(SERVER_BOARD_NAME);

  //    void* server_board = board_open(board_id, BOARD_LENGTH);
  //    if(server_board == nullptr)
  //        return 1;

  //    /** 2. 初始化资源表 共享区域表 类型表 实例表 节点表  注册常用类型 */
  //    lmice_resource_init(server_board);
  //    getchar();
  //    return 0;
  //}

  // int lmice_resource_init(void* addr){
  //    constexpr uint64_t reslist_type = eal_hash64_fnv1a(RESOURCE_LIST_NAME);

  //    /** 1. 初始化资源列表 */
  //    void* res_addr = addr;
  //    lmlist_t* res_list;
  //    res_list= eal_list_init(res_addr, sizeof(lmres_t), LMRES_COUNT);

  //    /** 1.1 注册资源 资源列表 */
  //    {
  //        lmres_t* item = reinterpret_cast<lmres_t*>(res_list->item);
  //        item->fd = LM_RESLIST_FD;
  //        item->type = LM_RESLIST_TP;
  //        item->board = 0;
  //        item->pos = 0;
  //        item->size = LMRESLIST_SIZE;
  //        item->flags = LM_ALIVE;
  //    }

  //    /** 2. 初始化共享区域列表 */
  //    void* brd_addr = (char*)addr + LMRESLIST_SIZE;
  //    lmlist_t* brd_list;
  //    brd_list = eal_list_init(brd_addr, sizeof(lmbrd_t), LMBRD_COUNT);
  //    /** 2.1 注册资源 共享区域列表 */
  //    {
  //        lmres_t* item = reinterpret_cast<lmres_t*>(res_list->item)+1;
  //        item->fd = LM_BRDLIST_FD;
  //        item->type = LM_BRDLIST_TP;
  //        item->board = 0;
  //        item->pos = LMRESLIST_SIZE;
  //        item->size = LMBRDLIST_SIZE;
  //        item->flags = LM_ALIVE;
  //    }
  //    /** 2.2 注册资源 共享区域 */
  //    {
  //        lmbrd_t* item = reinterpret_cast<lmbrd_t*>(brd_list->item);
  //        item->fd = 0;
  //        item->size = BOARD_LENGTH;
  //        item->pos = 0;
  //        item->flags = LM_ALIVE;

  //    }

  return 0;
}
