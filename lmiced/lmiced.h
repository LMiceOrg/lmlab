#ifndef LMICED_H
#define LMICED_H

#include "lmice_eal_common.h"
#include "lmice_eal_list.h"

#include "resource.h"
#include <stdint.h>




extern lmapp_t* lmapp;

static inline lmlist_t* maplist() {
    lmapp;
}



/* 初始化平台 */
int lmice_server_create();

/* 初始化资源 */
int lmice_resource_init(void* addr);

#endif // LMICED_H
