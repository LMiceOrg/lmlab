#include "board.h"
#include <errno.h>
#include <string.h>
#include "lmice_eal_shm.h"
#include "lmiced.h"
#include "lmrte.hpp"
#include "resource.h"
#define SERVER_BOARD_NAME "/private/tmp/LMiced V1.0 Board 000"
#define RESOURCE_LIST_NAME "Lmice resource list type"

struct lmcnt_desc {
  lmice_shm_t shm;
  uint32_t size;
  uint32_t bpb;
  uint32_t usage_pos;
  uint32_t index_pos;
  uint32_t data_pos;

  uint32_t usage_size;
  uint32_t index_size;
  uint32_t data_size;
};

struct lmcnt_usage {
  // bit array; bpb (byte per bit)
  uint8_t bits[8];
};

struct lmboard {
  int64_t lock;
  void* prev;
  void* next;
  lmcnt_desc desc;
};

struct lmcnt_index {
  uint64_t id;
  int64_t tick;
  int32_t type;
  uint32_t size;
  uint32_t from;
  uint32_t to;
};

static inline lmcnt_desc* lmdesc(lmboard* brd) { return &(brd->desc); }

static inline lmcnt_usage* lmusage(lmboard* brd) {
  lmcnt_desc* desc = lmdesc(brd);
  char* ptr = reinterpret_cast<char*>(brd) + desc->usage_pos;
  return reinterpret_cast<lmcnt_usage*>(ptr);
}

static inline lmcnt_index* lmindex(lmboard* brd) {
  lmcnt_desc* desc = lmdesc(brd);
  char* ptr = reinterpret_cast<char*>(brd) + desc->index_pos;
  return reinterpret_cast<lmcnt_index*>(ptr);
}

static inline char* lmdata(lmboard* brd) {
  lmcnt_desc* desc = lmdesc(brd);
  char* ptr = reinterpret_cast<char*>(brd) + desc->data_pos;
  return reinterpret_cast<char*>(ptr);
}

static inline void usage_mask(uint8_t* bit, int n) {
  uint8_t* ptr = bit;
  do {
    int pos = n / 8;
    int remain = n % 8;
    if (remain > 0) {
      ptr = bit + pos;
      *ptr = (1 << remain) - 1;
      n -= remain;
    } else if (pos > 0) {
      ptr = bit + pos - 1;
      *ptr = (1 << 8) - 1;
      n -= 8;
    }

  } while (n > 0);
}

/** 第一层操作 */
/* 创建共享区域 */
lmbrd_pt lmbrd_create(uint64_t id, unsigned int size) {
  int ret = 0;
  lmice_shm_t shm;

  // 创建共享区域
  eal_shm_zero(&shm);
  shm.size = size;
  eal_shm_hash_name(id, shm.name);

  ret = eal_shm_create(&shm);
  if (ret != 0) return nullptr;

  // 初始化共享区域 - 链表
  lmboard* board = reinterpret_cast<lmboard*>(shm.addr);
  board->lock = 0;
  board->prev = nullptr;
  board->next = nullptr;
  lmcnt_desc* desc = lmdesc(board);

  // 初始化共享区域 - 描述表
  memcpy(&(desc->shm), &shm, sizeof(shm));
  desc->size = sizeof(lmcnt_desc);
  desc->bpb = 16 * 1024;

  desc->usage_pos = 128;
  desc->usage_size = size / desc->bpb / 8;

  desc->index_pos = desc->usage_pos + desc->usage_size;
  desc->index_size = size / desc->bpb * sizeof(lmcnt_index);

  int used = (desc->index_pos + desc->index_size + desc->bpb - 1) / desc->bpb;
  desc->data_pos = used * desc->bpb;

  // 初始化共享区域 - 使用情况
  lmcnt_usage* usage = lmusage(board);
  memset(usage->bits, 0, desc->usage_size);
  usage_mask(usage->bits, used);

  return board;
}

/* 删除共享区域 */
void lmbrd_delete(lmbrd_pt ptr) {
  // 更新链表
  lmboard* board = reinterpret_cast<lmboard*>(ptr);
  lmboard* next = reinterpret_cast<lmboard*>(board->next);
  lmboard* prev = reinterpret_cast<lmboard*>(board->prev);
  if (prev != nullptr) {
    prev->next = next;
  }
  if (next != nullptr) {
    next->prev = prev;
  }

  // 删除当前节点
  lmcnt_desc* desc = lmdesc(board);
  eal_shm_destroy(&(desc->shm));
  
}

/* 打开共享区域 */
int lmbrd_open(uint64_t id) {
  
}

/* 关闭共享区域 */
void lmbrd_close(int fd);
