#include "board.h"
#include <errno.h>
#include <string.h>
#include "lmice_eal_shm.h"
#include "lmiced.h"
#include "lmrte.hpp"
#include "resource.h"
#define SERVER_BOARD_NAME "/private/tmp/LMiced V1.0 Board 000"
#define RESOURCE_LIST_NAME "Lmice resource list type"

struct lmbrd_desc {
  lmice_shm_t shm;
  int64_t usage_pos;
  int64_t index_pos;
  int64_t data_pos;
};

struct lmboard {
  int64_t lock;
  void* prev;
  void* next;
  lmbrd_desc desc;
  char data[8];
};

struct lmbrd_usage {};
struct lmbrd_index {
  char name[32];
};

/** 第一层操作 */
/* 创建共享区域 */
lmbrd_pt lmbrd_create(uint64_t id, unsigned int size) {
  int ret = 0;
  lmbrd_pt brd = nullptr;
  lmice_shm_t shm;

  // 创建共享区域
  eal_shm_zero(&shm);
  shm.size = size;
  eal_shm_hash_name(id, shm.name);

  ret = eal_shm_create(&shm);
  if (ret != 0) return brd;

  // 初始化共享区域 - 链表
  lmboard* board = reinterpret_cast<lmboard*>(shm.addr);
  board->lock = 0;
  board->prev = nullptr;
  board->next = nullptr;

  // 初始化共享区域 - 描述表
  memcpy(&(board->desc.shm), &shm, sizeof(shm));
  board->desc.usage_pos = 0;
  board->desc.index_pos = (size / 32768);
  board->desc.data_pos = board->desc.index_pos + (size / 65536) * 4096;

  return brd;
}

/* 初始化共享区域 */
void lmbrd_init(lmbrd_pt ptr);

/* 删除共享区域 */
void lmbrd_delete(lmbrd_pt ptr);

/* 打开共享区域 */
int lmbrd_open(uint64_t id);

/* 关闭共享区域 */
void lmbrd_close(int fd);
