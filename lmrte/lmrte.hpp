#ifndef LMRTE_HPP
#define LMRTE_HPP

#include <stdint.h>

#include "lmrte.h"
#pragma warning(push)
#pragma warning(disable : 4307)
namespace helper {

template <class T, int count>
struct byte_n {
  constexpr static uint8_t byten(const T &str, int idx) {
    return *((reinterpret_cast<const uint8_t *>(&str) + idx));
  }
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
    return static_cast<uint8_t>(
        (static_cast<uint16_t>(str) & (0xff << (8 * idx))) >> (8 * idx));
  }
};

template <class T>
struct byte_n<T, 4> {
  constexpr static uint8_t byten(const T &str, int idx) {
    return static_cast<uint8_t>(
        (static_cast<uint32_t>(str) & (0xffULL << (8 * idx))) >> (8 * idx));
  }
};

template <class T>
struct byte_n<T, 8> {
  constexpr static uint8_t byten(const T &str, int idx) {
    return static_cast<uint8_t>(
        (static_cast<uint64_t>(str) & (0xffULL << (8 * idx))) >> (8 * idx));
  }
};

template <>
struct byte_n<double, 8> {
  constexpr static uint8_t byten(const double &str, int idx) {
    return static_cast<uint8_t>(
        (*(static_cast<const uint64_t *>(static_cast<const void *>(&str))) &
         (0xffULL << (8 * idx))) >>
        (8 * idx));
  }
};

template <>
struct byte_n<float, 4> {
  constexpr static uint8_t byten(const float &str, int idx) {
    return static_cast<uint8_t>(
        (*(static_cast<const uint32_t *>(static_cast<const void *>(&str))) &
         (0xffULL << (8 * idx))) >>
        (8 * idx));
  }
};

template <unsigned N, unsigned pos>
struct hash_fnv1a_helper {
  constexpr static uint64_t hash(uint64_t hval) {
    return hval + (hval << 1) + (hval << 4) + (hval << 5) + (hval << 7) +
           (hval << 8) + (hval << 40);
  }

  template <class T, int idx>
  struct hash_n {
    typedef hash_n<T, idx - 1> hashn_prev;
    typedef byte_n<T, sizeof(T)> byten;
    constexpr static uint64_t hashn(const T (&str)[N], uint64_t hval) {
      return hash(hashn_prev::hashn(str, hval) ^
                  byten::byten(str[pos - 1], idx - 1));
    };
  };
  template <class T>
  struct hash_n<T, 1> {
    typedef byte_n<T, sizeof(T)> byten;
    constexpr static uint64_t hashn(const T (&str)[N], uint64_t hval) {
      return hash(hval ^ byten::byten(str[pos - 1], 0));
    };
  };

  template <class T, int count = sizeof(T)>
  struct hash64 {
    typedef
        typename hash_fnv1a_helper<N, pos - 1>::template hash64<T, sizeof(T)>
            hash64_t;

    constexpr static uint64_t hash(const T (&str)[N]) {
      return hash_n<T, sizeof(T)>::hashn(str, hash64_t::hash(str));
    }
    constexpr static uint64_t hash_more(const T (&str)[N], uint64_t old) {
      return hash_n<T, sizeof(T)>::hashn(str, hash64_t::hash_more(str, old));
    }
  };
};

template <unsigned N>
struct hash_fnv1a_helper<N, 0> {
  template <class T, int count>
  struct hash64 {
    constexpr static uint64_t hash(const T (&)[N]) {
      return 14695981039346656037ULL;
    }
    constexpr static uint64_t hash_more(const T (&)[N], uint64_t old) {
      return old;
    }
  };
};

}  // namespace helper

template <unsigned N, class T>
constexpr uint64_t eal_hash64_fnv1a(const T (&str)[N]) {
  typedef
      typename helper::hash_fnv1a_helper<N, N>::template hash64<T, sizeof(T)>
          hash64;
  return hash64::hash(str);
}

template <unsigned N, class T>
constexpr uint64_t eal_hash64_more_fnv1a(const T (&str)[N], uint64_t old) {
  typedef
      typename helper::hash_fnv1a_helper<N, N>::template hash64<T, sizeof(T)>
          hash64;
  return hash64::hash_more(str, old);
}

#pragma warning(pop)

#endif  // LMRTE_HPP
