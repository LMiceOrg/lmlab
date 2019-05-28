#ifndef LMRTE_HPP
#define LMRTE_HPP

#include <stdint.h>

#include "lmrte.h"
#pragma warning(push)
#pragma warning(disable : 4307)

template <unsigned N, unsigned pos>
struct hash_fnv1a_helper{

    constexpr static uint64_t hash(uint64_t hval) {
        return hval
                + (hval << 1)
                + (hval << 4)
                + (hval << 5)
                + (hval << 7)
                + (hval << 8)
                + (hval << 40);
    }

    constexpr static uint64_t hash64(const char (&str)[N]) {
        return hash( hash_fnv1a_helper<N, pos - 1>::hash64(str)
                     ^ static_cast<uint64_t>( str[pos-1] )
                ) ;
    }

    template<class T, int count=4>
    constexpr static uint64_t hash64_32(const T (&str)[N], uint64_t hval,  int idx) {
        return hash(hval ^ static_cast<uint64_t>(
                        static_cast<uint32_t>(str[pos-1]
                        & (0xff<<(8*idx))) >>(8*idx)
                    ));
    }

    template <class T, int count=sizeof(T)>
    constexpr static uint64_t hash64(const T (&str)[N]) {
        return 0;
    }
    constexpr static uint64_t hash64(const int (&str)[N]) {
        return hash64_32(str,
                         hash64_32(str,
                                   hash64_32(str,
                                             hash64_32(str, hash_fnv1a_helper<N, pos - 1>::hash64(str)
                                                       , 0), 1), 2), 3);
    }

#ifdef _WIN32
    constexpr static uint64_t hash64_16(const wchar_t (&str)[N], uint64_t hval,  int idx) {
        return hash(hval ^ static_cast<uint64_t>(
                        (static_cast<uint16_t>(str[pos-1])
                        & (0xff<<(8*idx))) >>(8*idx)
                    ));
    }
    constexpr static uint64_t hash64(const wchar_t (&str)[N]) {
        return hash64_16(str,
                         hash64_16(str,
                                   hash_fnv1a_helper<N, pos - 1>::hash64(str)
                                   , 0)
                         , 1);
    }
#else
    constexpr static uint64_t hash64_32(const wchar_t (&str)[N], uint64_t hval,  int idx) {
        return hash(hval ^ static_cast<uint64_t>(
                        static_cast<uint32_t>(str[pos-1]
                        & (0xff<<(8*idx))) >>(8*idx)
                    ));
    }
    constexpr static uint64_t hash64(const wchar_t (&str)[N]) {
        return hash64_32(str,
                         hash64_32(str,
                                   hash64_32(str,
                                             hash64_32(str, hash_fnv1a_helper<N, pos - 1>::hash64(str)
                                                       , 0), 1), 2), 3);
    }
#endif
};

template <unsigned N>
struct hash_fnv1a_helper<N,0> {
    template<class T>
    constexpr static uint64_t hash64(const T (&str)[N]) {
        return 14695981039346656037ULL;
    }
};

template<unsigned N, class T>
constexpr uint64_t eal_hash64_fnv1a(const T (&str)[N])
{
    return hash_fnv1a_helper<N,N>::hash64(str);
}

#pragma warning(pop)

#endif // LMRTE_HPP
