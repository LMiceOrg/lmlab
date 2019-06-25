/** Copyright 2018, 2019 He Hao<hehaoslj@sina.com> */

#ifndef LMRTE_H
#define LMRTE_H

#include <stdint.h>

#include "lmice_eal_common.h"

#if defined(_WIN32) /* Windows */

#if defined(LMRTE_PROJECT)
#define RTEFUNC __declspec(dllexport)
#else
#define RTEFUNC __declspec(dllimport)
#endif

#elif defined(__MACH__) || defined(__linux__)

#if defined(LMRTE_PROJECT)
#define RTEFUNC __attribute__((visibility("default")))
#else
#define RTEFUNC __attribute__((visibility("hidden")))
#endif

#endif

/** 类型/结构 */

/* C interface type */
typedef void* lmrte_t;

/** 接口/函数 */

///* 创建模型实例 */
// lmrte_t rte_open_client(lmid_t id);
// void rte_close_client(lmrte_t rte);

///* 打开会话 */
// lmfd_t rte_open_session(lmid_t sid);

///* 关闭会话 */
// int rte_close_session(lmfd_t sfd);

///* 进入会话状态 */
// int rte_with_session(lmfd_t sfd);

///* 获取当前会话  */
// lmfd_t rte_session();

///* 注册类型
// * size: 0 可变长度， 其他：固定长度
//*/
// lmfd_t rte_reg_type(lmid_t type, uint64_t size);

///* 注册实例 */
// lmfd_t rte_reg_instance(lmid_t inst);

// lmfd_t rte_reg_publish(lmfd_t type, lmfd_t inst);
// lmfd_t rte_reg_subscribe(lmfd_t type, lmfd_t inst);

///* 发布信息 */
// int rte_publish(lmfd_t fd, void* data, uint64_t size);

#endif  // LMRTE_H
