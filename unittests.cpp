/*
 * MIT License
 * 
 * Copyright (c) 2026 Andrew Ellis Page
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * SPDX short identifier: MIT
 */

//
// Created by andrew on 10/21/26.
//

#include <numeric>
#include <boost/align/aligned_allocator.hpp>
#include <gtest/gtest.h>

#include "vector_reduce.h"

template<typename ty>
using vector_aligned64_t = std::vector<ty, boost::alignment::aligned_allocator<ty, 64>>;

#ifdef __AVX512F__
#define VECTOR_SIZE_IN_BITS 512
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#define VECTOR_SIZE_IN_BITS vector_t<double>::size() * 8
#else
#error "Unsupported architecture"
#endif

template<typename T>
void CreateTrivialData(vector_aligned64_t<T>& data, size_t n) {
    data.resize(n);
    for (size_t i = 0; i < n; ++i) {
      data[i] = 1 ; // static_cast<T>(i);
    }
}

template<typename T>
void TrivialTestInner(size_t n) {
    vector_aligned64_t<T> data;
    CreateTrivialData(data, n);
    auto correct = std::reduce(data.begin(), data.end(), static_cast<T>(0));
    auto check = vector_reduce(data.data(), data.size(), static_cast<T>(0));
    EXPECT_EQ(correct, check) << " vector_reduce";

    check = vector_reduce_simd(data.data(), data.size(), static_cast<T>(0));
    EXPECT_EQ(correct, check) << " vector_reduce_simd";

    check = va_reduce(data.data(), data.size(), static_cast<T>(0));
    EXPECT_EQ(correct, check) << " va_reduce";

    check = va_reduce_simd(data.data(), data.size(), static_cast<T>(0));
    EXPECT_EQ(correct, check) << " va_reduce_simd";
}

template<typename T>
void TrivialTest()
{
    vector_aligned64_t<T> data;
    size_t n = (VECTOR_SIZE_IN_BITS/(sizeof(T)*8))*64;
    TrivialTestInner<T>(n);
    // TrivialTestInner<T>(n+129);
    // TrivialTestInner<T>(n+65);
    // TrivialTestInner<T>(n+33);
    // TrivialTestInner<T>(n+17);
    // TrivialTestInner<T>(511);
    // TrivialTestInner<T>(255);
    // TrivialTestInner<T>(127);
    // TrivialTestInner<T>(63);
    // TrivialTestInner<T>(31);
    // TrivialTestInner<T>(15);
    // TrivialTestInner<T>(7);
}

TEST(VectorReduceTest, TrivialDouble) {
    TrivialTest<double>();
}

TEST(VectorReduceTest, TrivialFloat) {
    TrivialTest<float>();
}

TEST(VectorReduceTest, TrivialInt64) {
    TrivialTest<int64_t>();
}

TEST(VectorReduceTest, TrivialInt32) {
    TrivialTest<int32_t>();
}
