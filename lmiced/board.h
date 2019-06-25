#ifndef BOARD_H
#define BOARD_H

/****************************
FIXME 共享区域管理

## 基本概念

- 共享区域

共享区域（前缀lmbrd）是离散事件驱动系统（DEDS）中发布订阅事件与数据的入端（Source/Sink
port）。

共享区域数据结构是链表
lmboard
 -----
| lock  原子锁
|-----
| prev  指向链表上一条记录，如果是第一条则为NULL
|-----
| next  指向链表下一条记录，如果是最后一条则为NULL
|-----
| ...<lmcontent> 数据内容

数据内容包含共享区域描述信息（lmbrd_desc_t），使用情况列表（lmbrd_usage_t），信息索引列表（lmbrd_index_t），
信息数据.
lmcontent
 -----
| lmbrd_desc
|-----
| lmbrd_usage
|-----
| lmbrd_index
|-----
| ...<lmdata> 信息数据

- 主共享区域

系统第一个共享区域，包含系统信息数据列表。

- 从共享区域

系统继续创建的共享区域。

## 基本数据类型

共享区域句柄 lmbrd_t

## 基本操作

- 打开共享区域

系统应用端初始化时打开共享区域（lmbrd_open）。

app:
  board = lmbrd_open(inst_id);

- 关闭共享区域
系统应用端结束执行时关闭共享区域（lmbrd_close）。

app:
  lmbrd_close(fd);

- 创建共享区域

系统服务端执行创建新的共享区域（lmbrd_create）。

lmiced:
  board = lmbrd_create(inst_id, size);

- 删除共享区域

系统服务端执行删除共享区域(lmbrd_delete)。

lmiced:
  lmbrd_delete(inst_id);

- 初始化共享区域

系统服务端执行创建后完成初始化（lmbrd_init）。

lmiced:
  board = lmbrd_init();

-
app本身也是一种数据

app -->|打开| 共享区域
app 注册 自己资源



*****************************/

#include "lmice_eal_common.h"

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/** 数据类型 */
/* 共享区域指针 */
typedef void* lmbrd_pt;

/* 共享区域资源标识 */
typedef uint64_t lmbrd_id;

/* 共享区域资源句柄 */
typedef int lmbrd_fd;

/** 第一层操作 */
/* 创建共享区域 */
lmbrd_pt lmbrd_create(uint64_t id, unsigned int size);

/* 初始化共享区域 */
void lmbrd_init(lmbrd_pt ptr);

/* 删除共享区域 */
void lmbrd_delete(lmbrd_pt ptr);

/* 打开共享区域 */
lmbrd_fd lmbrd_open(lmbrd_id id);

/* 关闭共享区域 */
void lmbrd_close(lmbrd_fd fd);

void* board_address(int fd, unsigned int pos = 0);
void board_close(int fd);

#ifdef __cplusplus
}
#endif

#endif  // BOARD_H
