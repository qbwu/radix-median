/***************************************************************************
 *
 * Copyright (c) 2020 qbwu All Rights Reserved
 *
 **************************************************************************/

/**
 * @file main.cpp
 * @author qb.wu@outlook.com
 * @date 2020/08/03
 * @brief
 **/

#include <iostream>
#include <fstream>

#include <gflags/gflags.h>

#include "median.h"
#include "bits_utils.h"

DEFINE_string(filename, "data", "Intput filename.");
DEFINE_int32(max_size, 65536, "Max size of the hash map.");

int main(int argc, char **argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);

    static std::ifstream file(FLAGS_filename, std::ios::in);
    if (!file.good()) {
        throw std::invalid_argument("Invalid filename: " + FLAGS_filename);
    }
    
    if (FLAGS_max_size < 4) {
        throw std::invalid_argument("Too small buffer size(<4): " + std::to_string(FLAGS_max_size));
    }
    auto res = median::median(file, FLAGS_max_size);
    
    std::cout << "median: " << res << std::endl;
    
    return 0;
}
