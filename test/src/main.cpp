/***************************************************************************
 *
 * Copyright (c) 2020 qbwu All Rights Reserved
 *
 **************************************************************************/

/**
 * @file main.cpp 
 * @author qb.wu@outlook.com
 * @date 2020/08/04
 * @brief unit test
 **/

#include <limits>
#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "median.h"
#include "bits_utils.h"

namespace {

int g_max_size = 6;

}

namespace median {

TEST(bits_utils, order) {
    EXPECT_EQ(order(0), 0);
    EXPECT_EQ(order(4), 2);
    EXPECT_EQ(order(5), 2);
    EXPECT_EQ(order(6), 2);
    EXPECT_EQ(order(255), 7);
    EXPECT_EQ(order(256), 8);
    EXPECT_EQ(order(65536), 16);
    EXPECT_EQ(order(std::numeric_limits<int>::max()), 30);
}

TEST(bits_utils, bits) {
    EXPECT_EQ(bits(0x05050505, 0, 8), 0x05);
    EXPECT_EQ(bits(0x05050505, 8, 8), 0x05);
    EXPECT_EQ(bits(0x05050505, 0, 12), 0x050);
    EXPECT_EQ(bits(0x05050505, 0, 6), 1);
    EXPECT_EQ(bits(0x05050505, 6, 6), 16);
    EXPECT_EQ(bits(-1, 0, 7), 127);
}

TEST(bits_utils, hilo) {
    EXPECT_EQ(hilo(1, 0, 1, 7), 128);
    EXPECT_EQ(hilo(1, 16, 6, 6), 0x050);
    EXPECT_EQ(hilo(1, 0x7FFFFFFF, 1, 31), (unsigned) -1);
}

TEST(median, even_pos1) {
    // 0 ~ 15
    std::string input = "0\n12\n14\n13\n1\n5\n6\n3\n10\n2\n7\n4\n9\n11\n15\n8";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), (7 + 8) / 2);
}

TEST(median, even_pos2) {
    // 0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 10, 11, 12, 13, 14, 15
    std::string input = "0\n12\n14\n13\n1\n5\n6\n3\n10\n2\n7\n4\n7\n11\n15\n7";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), 7);
}

TEST(median, even_pos3) {
    // 0, 1, 2, 3, 4, 5, 8, 8, 8, 9, 10, 11, 12, 13, 14, 15
    std::string input = "0\n12\n14\n13\n1\n5\n8\n3\n10\n2\n8\n4\n9\n11\n15\n8";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), 8);
}

TEST(median, even_pos4) {
    // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    std::string input = "1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), 1);
}

TEST(median, even_neg1) {
    // -16 ~ -1
    std::string input = "-16\n-12\n-14\n-13\n-1\n-5\n-6\n-3\n-10\n-2\n-7\n-4\n-9\n-11\n-15\n-8";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), (-8 + -9) / 2);
}

TEST(median, even_neg2) {
    // -1, -2, -3, -4, -5, -6, -7, -9, -9, -9, -11, -12, -13, -14, -15, -16
    std::string input = "-16\n-12\n-14\n-13\n-1\n-5\n-6\n-3\n-9\n-2\n-7\n-4\n-9\n-11\n-15\n-9";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), -9);
}

TEST(median, even_neg3) {
    // -1, -2, -3, -4, -5, -6, -8, -8, -8, -10, -11, -12, -13, -14, -15, -16
    std::string input = "-16\n-12\n-14\n-13\n-1\n-5\n-6\n-3\n-10\n-2\n-8\n-4\n-8\n-11\n-15\n-8";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), -8);
}

TEST(median, even_neg4) {
    // -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 
    std::string input = "-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), -1);
}

TEST(median, even_pos_neg1) {
    // -7 ~ 8 
    std::string input = "-1\n-2\n7\n-3\n8\n6\n5\n0\n-5\n-6\n4\n-4\n-7\n2\n3\n1";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), (0 + 1) / 2);
}

TEST(median, even_pos_neg2) {
    // -7, -6, -5, -4, -3, -2, -1, -1, -1, 2, 3, 4, 5, 6, 7, 8 
    std::string input = "-1\n-2\n7\n-3\n8\n6\n5\n-1\n-5\n-6\n4\n-4\n-7\n2\n3\n-1";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), -1);
}

TEST(median, even_two) {
    std::string input = "1\n2";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), (1 + 2) / 2);
}

TEST(median, even_random) {
    std::srand(std::time(0));

    std::vector<int> buf;
    buf.reserve(100);
    
    std::stringstream ss;
    for (auto i = 0; i < 100; ++i) {
        auto r = (std::rand() % 100) - 50;
        ss << r << "\n";
        buf.push_back(r);
    }
    std::sort(buf.begin(), buf.end());
    EXPECT_EQ(median(ss, g_max_size), (buf[49] + buf[50]) / 2);
}

TEST(median, odd_pos1) {
    // 0 ~ 14
    std::string input = "0\n12\n14\n13\n1\n5\n6\n3\n10\n2\n7\n4\n9\n11\n8";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), 7);
}

TEST(median, odd_pos2) {
    // 0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 10, 11, 12, 13, 14
    std::string input = "0\n12\n14\n13\n1\n5\n6\n3\n10\n2\n7\n4\n7\n11\n7";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), 7);
}

TEST(median, odd_pos3) {
    // 0, 1, 2, 3, 4, 5, 8, 8, 8, 9, 10, 11, 12, 13, 14
    std::string input = "0\n12\n14\n13\n1\n5\n8\n3\n10\n2\n8\n4\n9\n11\n8";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), 8);
}

TEST(median, odd_pos4) {
    // 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    std::string input = "1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), 1);
}

TEST(median, odd_neg1) {
    // -15 ~ -1
    std::string input = "-12\n-14\n-13\n-1\n-5\n-6\n-3\n-10\n-2\n-7\n-4\n-9\n-11\n-15\n-8";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), -8);
}

TEST(median, odd_neg2) {
    // -1, -2, -3, -4, -5, -6, -7, -9, -9, -9, -11, -12, -13, -14, -15
    std::string input = "-12\n-14\n-13\n-1\n-5\n-6\n-3\n-9\n-2\n-7\n-4\n-9\n-11\n-15\n-9";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), -9);
}

TEST(median, odd_neg3) {
    // -1, -2, -3, -4, -5, -6, -8, -8, -8, -10, -11, -12, -13, -14, -15
    std::string input = "-12\n-14\n-13\n-1\n-5\n-6\n-3\n-10\n-2\n-8\n-4\n-8\n-11\n-15\n-8";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), -8);
}

TEST(median, odd_neg4) {
    //-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 
    std::string input = "-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1\n-1";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), -1);
}

TEST(median, odd_pos_neg1) {
    // -7 ~ 7 
    std::string input = "-1\n-2\n7\n-3\n6\n5\n0\n-5\n-6\n4\n-4\n-7\n2\n3\n1";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), 0);
}

TEST(median, odd_pos_neg2) {
    // -7, -6, -5, -4, -3, -2, -1, -1, -1, 2, 3, 4, 5, 6, 7
    std::string input = "-1\n-2\n7\n-3\n6\n5\n-1\n-5\n-6\n4\n-4\n-7\n2\n3\n-1";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), -1);
}

TEST(median, even_two) {
    std::string input = "1\n2";
    std::istringstream iss(input);
    EXPECT_EQ(median(iss, g_max_size), (1 + 2) / 2);
}

TEST(median, odd_random) {
    std::srand(std::time(0));

    std::vector<int> buf;
    buf.reserve(101);
    
    std::stringstream ss;
    for (auto i = 0; i < 101; ++i) {
        auto r = (std::rand() % 101) - 50;
        ss << r << "\n";
        buf.push_back(r);
    }
    std::sort(buf.begin(), buf.end());
    EXPECT_EQ(median(ss, g_max_size), buf[50]);
}

}

int main(int argc, char **argv) {
    (void) argc; (void) argv;

    testing::InitGoogleTest();
    for (auto i : {4, 8, 17, 15, 16, 100, 256}) {
        g_max_size = i;
        std::cerr << "******* Begin test with g_max_size=" << i << " *******\n\n";
        if (::RUN_ALL_TESTS() != 0) {
            return -1;
        }
        std::cerr << std::endl;
    }
    return 0;
}
