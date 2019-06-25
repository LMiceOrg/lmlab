#ifndef RESOURCE_H
#define RESOURCE_H

#include "lmice_eal_common.h"
#include "lmice_eal_list.h"

/* FIXME 内存文件系统 参考ext2/bsd */
/*  board 对应 文件系统根文件
 * bitmap 块 表示 使用情况
 * 【区域描述块】【区域使用状态块 bitmap】【索引块 inode】【数据块】
 */

/* FIXME 系统调用 参考 system trap */
/* 系统 对应 LMICED 服务
 *
 * 系统调用API
 */

///* 资源类型 */
// struct lmice_res_item_s {
//    int fd;
//    int flags;
//    int type;
//    int board;
//    int pos;
//    uint32_t size;

//}forcepack(8);
// typedef struct lmice_res_item_s lmres_t;

///* 共享区域类型 */
// struct lmice_board_s {
//    int fd;
//    int flags;
//    uint32_t size;
//    int pos;
//    char name[32];
//}forcepack(8);
// typedef struct lmice_board_s lmbrd_t;

///* 共享区域映射类型 */
// struct lmice_board_mapping_s {
//    int fd;
//    int flags;
//    uint32_t size;
//    void* addr;
//    void* handle;
//};
// typedef struct lmice_board_mapping_s lmbmp_t;

///* 平台类型 */
// struct lmice_application_s {
//    volatile int64_t lock;
//    lmlist_t *map_list; /* 共享区域映射列表 */
//    lmlist_t *res_list; /* 资源列表 */
//    lmlist_t *brd_list; /* 共享区域列表 */
//    lmlist_t *type_list; /* 类型列表 */
//    lmlist_t *inst_list; /* 实例列表 */
//    lmlist_t *sess_list; /* 会话列表 */
//    lmlist_t *node_list; /* 节点列表 */
//};
// typedef struct lmice_application_s lmapp_t;

// enum lmice_list_e {
//    LM_EMPTY = 0,
//    LM_ALIVE = 1,
//    LMRES_COUNT = 64,
//    LMBRD_COUNT =64,
//    LMBMP_COUNT = 64,

//    /* 基本类型大小 */
//    LMRESLIST_SIZE = LMLIST_SIZE + sizeof(lmres_t)*LMRES_COUNT,
//    LMBRDLIST_SIZE = LMLIST_SIZE + sizeof(lmbrd_t)*LMBRD_COUNT,
//    LMMAPLIST_SIZE = LMLIST_SIZE + sizeof(lmbmp_t)*LMBMP_COUNT,

//    /* 平台 列表位置 */
//    LMMAPLIST_POS =  sizeof(lmapp_t),
//    LMRESLIST_POS = LMMAPLIST_POS + LMMAPLIST_SIZE,
//    LMBRDLIST_POS = LMRESLIST_POS + LMRESLIST_SIZE,
//    LMTYPELIST_POS = LMBRDLIST_POS + LMBRDLIST_SIZE,

//    /** internal fd */
//    LM_RESLIST_FD = 1,
//    LM_BRDLIST_FD,

//    /** internal type */
//    LM_RESLIST_TP = 0,
//    LM_BRDLIST_TP,
//};

///* 申请共享数据 */
// void* lmres_malloc(uint32_t size);

// void lmres_init_bmp(void*, int fd, uint32_t size, void* addr, void* handle);

///* 创建列表 */
// lmfd_t lmres_create_list(lmfd_t type, uint32_t size, uint32_t count);
// void* lmres_open(lmfd_t);

#endif  // RESOURCE_H
