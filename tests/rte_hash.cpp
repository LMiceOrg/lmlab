
#include <stdio.h>
#include "lmice_eal_hash.h"
#include "lmrte.hpp"

int main() {
  // constexpr std::array<int, 3> i3 = {1, 2, 3};
  constexpr int i3[] = {1, 2, 3};
  constexpr uint64_t hvala = eal_hash64_fnv1a(i3);

  constexpr char s[] = {'\1', '\0', '\0', '\0', '\2', '\0', '\0', '\0', '\3',
                        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
  constexpr uint64_t hval = eal_hash64_fnv1a(s);
  // static_assert(hvala == hval, "equal");
  printf("h1=%16llx\nh2=%16llx\n", hvala, hval);
  for (int i = 0; i < 6; i++) {
    printf("h%d=%16llx\n", i, eal_hash64_fnv1a(s, 12));
  }

  printf("size =%lu\n", sizeof(i3));
  for (unsigned i = 0; i < sizeof(i3); ++i) {
    const char* p = reinterpret_cast<const char*>(&i3);
    printf("[%u]: \t%u\n", i, *(p + i));
  }

  int integer = 1;
  char p = static_cast<char>(integer);
}
