#ifndef BOARD_H
#define BOARD_H

#include "lmice_eal_common.h"


#define BOARD_LENGTH (2*1024*1024)

#ifdef __cplusplus
extern "C" {
#endif

/* 创建共享区域 */
lmfd_t board_create(lmid_t id, int size);

/* 打开共享区域 */
void* board_open(lmid_t id, int size);

void* board_address(lmfd_t fd, unsigned int pos = 0);
int board_close(lmfd_t fd);

#ifdef __cplusplus
}
#endif

#endif // BOARD_H
