/** Copyright 2018, 2019 He Hao<hehaoslj@sina.com> */

#ifndef LMICE_EAL_LIST_H
#define LMICE_EAL_LIST_H

#include <stdint.h>
#include "lmice_eal_common.h"

/* 列表类型 */
struct lmice_list_s {
  uint32_t bytes;        /* 列表所占大小 */
  int base;              /* 描述符初始索引 */
  volatile int64_t lock; /* 自旋锁 */
  uint32_t size;         /* 数据大小 */
  uint32_t count;        /* 数据数量 */
  int next_board;        /* 指向下一块共享区域 */
  uint32_t next_pos;     /* 共享区域偏移量 */
  char item[8];          /* 列表数据 */
} forcepack(8);

typedef struct lmice_list_s lmlist_t;

/* 数据对象 */
struct lmice_item_s {
  int fd;
  int flags;
};
typedef struct lmice_item_s lmitem_t;

#define LMLIST_SIZE (sizeof(lmlist_t) - sizeof(char[8]))

#ifdef __cplusplus
extern "C" {
#endif

/* 在指定地址初始化列表 */
lmlist_t* eal_list_init(void* addr, uint32_t size, uint32_t count);

/* 查找指定状态数据对象 */
char* eal_list_find(lmlist_t* ll, int flag, int* fd);

#ifdef __cplusplus
}
#endif
#endif  // LMICE_EAL_LIST_H
