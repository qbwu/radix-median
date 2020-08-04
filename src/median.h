/***************************************************************************
 *
 * Copyright (c) 2020 qbwu All Rights Reserved
 *
 **************************************************************************/

/**
 * @file median.h
 * @author qb.wu@outlook.com
 * @date 2020/08/03
 * @brief compute median of integer stream by bitwise radix sorting
 **/

#ifndef _MEDIAN_MEDIAN_H_
#define _MEDIAN_MEDIAN_H_

#include <fstream>

namespace median {

int median(std::istream &file, size_t max_buf_size);

}

#endif // _MEDIAN_MEDIAN_H_
