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
#define VECTOR_SIZE_IN_BITS 128
#else
#error "Unsupported architecture"
#endif

template<typename T>
void CreateTrivialData(vector_aligned64_t<T>& data, size_t n) {
    data.resize(n);
    for (size_t i = 0; i < n; ++i) {
        data[i] = static_cast<T>(i);
    }
}

template<typename T>
void TrivialTest()
{
    vector_aligned64_t<T> data;
    size_t n = (VECTOR_SIZE_IN_BITS/(sizeof(T)*8))*64;
    CreateTrivialData(data, n+1);

    auto correct = std::reduce(data.begin(), data.end(), static_cast<T>(0));
    auto check = vector_reduce(data.data(), data.size(), static_cast<T>(0));
    EXPECT_EQ(correct, check);

    CreateTrivialData(data, n+129);
    correct = std::reduce(data.begin(), data.end(), static_cast<T>(0));
    check = vector_reduce(data.data(), data.size(), static_cast<T>(0));
    EXPECT_EQ(correct, check);

    CreateTrivialData(data, n+65);
    correct = std::reduce(data.begin(), data.end(), static_cast<T>(0));
    check = vector_reduce(data.data(), data.size(), static_cast<T>(0));
    EXPECT_EQ(correct, check);

    CreateTrivialData(data, n+33);
    correct = std::reduce(data.begin(), data.end(), static_cast<T>(0));
    check = vector_reduce(data.data(), data.size(), static_cast<T>(0));
    EXPECT_EQ(correct, check);

    CreateTrivialData(data, n+17);
    correct = std::reduce(data.begin(), data.end(), static_cast<T>(0));
    check = vector_reduce(data.data(), data.size(), static_cast<T>(0));
    EXPECT_EQ(correct, check);
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