/***************************************************************************
 *
 * Copyright (c) 2020 qbwu All Rights Reserved
 *
 **************************************************************************/

/**
 * @file bits_utils.h
 * @author qb.wu@outlook.com
 * @date 2020/08/03
 * @brief
 **/

#ifndef _MEDIAN_BITS_UTILS_H_
#define _MEDIAN_BITS_UTILS_H_

#include <cassert>
#include <iostream>

namespace median {

constexpr size_t INT_BITS = sizeof(int) * 8;

inline size_t order(int n) {
    auto b = 0;
    while ((n >>= 1) > 0) {
        ++b;
    }
    return b;
}

// pre-condition: len > 0 && beg + len <= INT_BITS
inline unsigned bits(unsigned num, size_t beg, size_t len) {
    assert(len > 0);
    assert(beg + len <= INT_BITS);
    return (num << beg) >> (INT_BITS - len);
}

inline unsigned hilo(unsigned hbits, unsigned lbits, size_t hlen, size_t llen) {
    // For suppressing unused-parameter warnings if compiled with -DNDEBUG
    (void) hlen;
    assert(hlen + llen <= INT_BITS);
    return (hbits << llen) | lbits;
}

} // median

#endif //_MEDIAN_BITS_UTILS_H_
