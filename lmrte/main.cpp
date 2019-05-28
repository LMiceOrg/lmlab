#include <stdint.h>
#include <stdio.h>


#include "lmice_eal_hash.h"
#include "lmrte.hpp"



int main() {
    printf("lmrte\n");
    const char c_hello[]="hello";
    const uint64_t hvala = eal_hash64_fnv1a({1,2,3});
    const uint64_t hval =eal_hash64_fnv1a("hello");
    //static_assert( (hval == 12230803299529341361ULL), "hello hval");
    printf("value = %llu\t", hvala );
    printf("eal =%llu\n",
           eal_hash64_fnv1a(c_hello, sizeof(c_hello)));
    const wchar_t w_hello[] = L"hello";
    // printf("wchar sized %llu\n", sizeof(w_hello));
    printf("value = %llu\t", eal_hash64_fnv1a(L"hello"));
    printf("eal =%llu\n",
           eal_hash64_fnv1a(w_hello, sizeof(w_hello)));
    return 0;
}

