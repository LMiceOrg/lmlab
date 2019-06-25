/** Copyright 2018, 2019 He Hao<hehaoslj@sina.com> */

#include "lmrte.h"

namespace lmice {
uint64_t getid(const unsigned char* blob, int size) {}

}  // namespace lmice

/** C only - Low Level API */

static struct lmrte_helper_api lmrte_helper_capi {};

const struct lmrte_helper_api* lmrte_helper(void) { return &lmrte_helper_capi; }

