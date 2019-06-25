#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lmice_eal_hash.h"
#include "lmrte.hpp"
template <class T, int count>
struct byte_n {
  constexpr static uint8_t byten(const T &, int) { return 0; }
};
template <class T>
struct byte_n<T, 1> {
  constexpr static uint8_t byten(const T &str, int) {
    return static_cast<uint8_t>(str);
  }
};
template <class T>
struct byte_n<T, 2> {
  constexpr static uint8_t byten(const T &str, int idx) {
    return static_cast<uint8_t>(static_cast<uint16_t>(str) &
                                (0xff << (8 * idx)) >> (8 * idx));
  }
};

template <class T>
struct byte_n<T, 4> {
  constexpr static uint8_t byten(const T &str, int idx) {
    return static_cast<uint8_t>(static_cast<uint32_t>(str) &
                                (0xff << (8 * idx)) >> (8 * idx));
  }
};

template <class T>
struct byte_n<T, 8> {
  constexpr static uint8_t byten(const T &str, int idx) {
    return static_cast<uint8_t>(((*reinterpret_cast<const uint64_t *>(&str)) &
                                 (0xffULL << (8 * idx))) >>
                                (8 * idx));
  }
};

int main() {
  printf("lmrte\n");
  constexpr char c_hello[] = "hhhhh";
  constexpr uint64_t hvala = eal_hash64_fnv1a({1, 2, 3});
  constexpr uint64_t hval = eal_hash64_fnv1a(c_hello);
  // static_assert( (hval == 12230803299529341361ULL), "hello hval");
  printf("value=\t%llu\t sizeof(v)=%lu\n", hval, sizeof(c_hello));
  printf("eal=\t%llu\t sizeof(v)=%lu\n",
         eal_hash64_fnv1a(c_hello, sizeof(c_hello)), sizeof(c_hello));
  constexpr wchar_t w_hello[] = L"hello";
  // printf("wchar sized %llu\n", sizeof(w_hello));
  printf("value=\t%llu\n", eal_hash64_fnv1a(w_hello));
  printf("eal=\t%llu\t%lu\n", eal_hash64_fnv1a(w_hello, sizeof(w_hello)),
         sizeof(w_hello));

  printf("test double array\n");
  constexpr double zero = 1.1;
  constexpr double darray[] = {zero, zero, zero};

  uint64_t d_val = eal_hash64_fnv1a(darray);

  printf("val=%llu\tsize=%lu\n", d_val, sizeof(darray));
  printf("eal=%llu\tsize=%lu\n", eal_hash64_fnv1a(darray, sizeof(darray)),
         sizeof(darray));

  printf("test integer array\n");
  constexpr char iarr_c[] = {'\1', '\0', '\0', '\0',
                             /* */
                             '\2', '\0', '\0', '\0',
                             /* */
                             '\3', '\0', '\0', '\0',
                             /* */
                             '\0', '\0', '\0', '\0',
                             /* */
                             '\0', '\0', '\0', '\0',
                             /* */
                             '\0', '\0', '\0', '\0'};
  constexpr int32_t iarray[] = {1, 2, 3, 0, 0, 0};
  constexpr uint64_t i_val = eal_hash64_fnv1a(iarray);
  constexpr uint64_t ic_val = eal_hash64_fnv1a(iarr_c);
  printf("icv=%llu\t\tsize=%lu\n", ic_val, sizeof(iarr_c));
  printf("val=%llu\t\tsize=%lu\n", i_val, sizeof(iarray));
  printf("eal=%llu\t\tsize=%lu\n", eal_hash64_fnv1a(iarray, sizeof(iarray)),
         sizeof(iarray));
  //  for (unsigned i = 0; i < sizeof(iarray) / sizeof(int); ++i) {
  //    int d = iarray[i];
  //    for (unsigned j = 0; j < sizeof(int); ++j)
  //      printf("%lu:\t%u\n", i * sizeof(int) + j, byte_n<int, 8>::byten(d,
  //      j));
  //  }
  printf("hash more\n\n");
  constexpr char cmore[] = "welcome";
  constexpr uint64_t h_cmore = eal_hash64_more_fnv1a(cmore, 0x1234);
  printf("val=%llu\t%lu\n", h_cmore, sizeof(cmore));
  printf("eal=%llu\t%lu\n", eal_hash64_more_fnv1a(cmore, sizeof(cmore), 0x1234),
         sizeof(cmore));
  printf("test float array\n");
  const float farray[] = {1.0, 2.0, 3.0};
  uint64_t f_val = eal_hash64_fnv1a(farray);
  uint64_t f_eal = eal_hash64_fnv1a(farray, sizeof(farray));
  printf("val=\t%016llx\n", f_val);
  printf("eal=\t%016llx\n", f_eal);

  printf("test user-defined struct array\n");
  struct usd_t {
    int ival;
    double dblval;
    char carrval[32];
  };
  constexpr usd_t uarray[3] = {
      {1, 1.0, "hello"}, {2, 2.0, "world"}, {3, 3.0, "hehao"}};
  // memset(&uarray, 0, sizeof(usd_t) * 3);
  //  uarray[0].ival = 1;
  //  uarray[0].dblval = 1.0;

  //  uarray[1].ival = 2;
  //  uarray[1].dblval = 2.0;

  //  uarray[2].ival = 3;
  //  uarray[2].dblval = 3.0;

  uint64_t u_val = eal_hash64_fnv1a(uarray);
  uint64_t u_eal = eal_hash64_fnv1a(uarray, sizeof(uarray));
  printf("val=\t%016llx\n", u_val);
  printf("eal=\t%016llx\n", u_eal);

  return 0;
}
