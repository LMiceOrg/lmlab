
#include "lmrte.hpp"

#include <stdio.h>

int main() {
    const uint64_t hvala = eal_hash64_fnv1a({1,2,3});
    constexpr const char s[] = {'\1','\0','\0','\0',
                      '\2','\0','\0','\0',
                      '\3','\0','\0','\0'};
    constexpr uint64_t hval =eal_hash64_fnv1a(s);
    static_assert(hvala==hval, "equal");
    printf("h1=%llx\nh2=%llx\n", hvala, hval);
}
