/***************************************************************************
 *
 * Copyright (c) 2020 qbwu All Rights Reserved
 *
 **************************************************************************/

/**
 * @file median.cpp
 * @author qb.wu@outlook.com
 * @date 2020/08/03
 * @brief compute median of integer stream by bitwise radix sorting
 **/

#include "median.h"

#include <cmath>
#include <limits>
#include <vector>
#include <fstream>
#include <exception>

#include "bits_utils.h"

namespace median {

inline void reset_input_stream(std::istream& file) {
    file.clear();
    file.seekg(0);
    if (!file.good()) {
        throw std::runtime_error("Failed to seekg on input stream.");
    }
}

unsigned find_lower_n_key(const std::vector<size_t> &map,
        size_t target,
        size_t &res) {
    size_t sum = 0;
    for (auto i = 0U; i < map.size(); ++i) {
        sum += map[i];
        if (sum > target) {
            res = sum - map[i];
            return i;
        }
    }
    throw std::runtime_error("Fix me");
}

int find_nearest(std::istream &file, int upper) {
    reset_input_stream(file);
    std::string line;

    int cand = 0;
    int min_diff = std::numeric_limits<int>::max();

    while (file >> line) {
        int n = 0;
        try {
            n = std::stoi(line);
        } catch (const std::exception &ex) {
            std::cerr << "Not integer line: " << line << ", err: " << ex.what() << std::endl;
            continue;
        }

        if (n < upper) {
            if (upper - n < min_diff) {
                min_diff = upper - n;
                cand = n;
            }
        }
    }
    return cand;
}

// pre-condition: max_buf_size >= 4 && max_buf_size <= (1 << 32)
int median(std::istream &file, size_t max_buf_size) {

    std::string line;
    
    // log_2(FLAGS_max_size)
    auto key_len = order(max_buf_size);

    int prefix = 0;
    bool is_even = false;
    size_t mid_n = 0;
    size_t total_n = 0;
    size_t lower_n = 0;
    
    // 1. with i bits used
    // 2. the highest bit of key_len is always the sign flag, so take (key_len - 1) bits every step
    for (auto i = 0U; i < INT_BITS; i += key_len - 1) {

        // read file from the beginning
        reset_input_stream(file);
        
        // initialize the counting map with zeros
        std::vector<size_t> map(1 << (key_len), 0);
        
        // in the last loop, the curr_len may be smaller than (key_len - 1)
        auto curr_len = std::min(INT_BITS - i, key_len - 1);

        while (std::getline(file, line)) {
            int n = 0;
            try {
                n = std::stoi(line);
            } catch (const std::exception &ex) {
                std::cerr << "Not integer line: " << line << ", err: " << ex.what() << std::endl;
                continue;
            }

            if (i != 0 && bits(n, 0, i) ^ prefix) {
                continue;
            }
            // 0 for neg, 1 for pos
            unsigned sign = (n >> 31) + 1;
            auto k = hilo(sign, bits(n, i, curr_len), 1, curr_len);
            ++map[k];

            ++total_n;
        }

        if (i == 0) {
            mid_n = total_n >> 1;
            is_even = (total_n == mid_n << 1);
        }

        auto k = find_lower_n_key(map, mid_n, lower_n);
        mid_n -= lower_n;

        // throw away the sign bit, only take the last curr_len of bits in k
        prefix = hilo(prefix, bits(k, INT_BITS - curr_len, curr_len), i, curr_len);
    }

    if (!is_even || mid_n > 0) {
        return prefix;
    }
    // average number
    return (find_nearest(file, prefix) + prefix) / 2;
}

} // median
