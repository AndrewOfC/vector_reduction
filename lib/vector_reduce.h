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

#pragma once
/**
* @file
 * @brief take care to align memory for vectorized operations
 *
 *  Alignment is 64 bytes for AVX-512, and 16 bytes for NEON.
 *  ```C
 * alignas(64) double x[1024];
 * alignas(16) float y[1024];
 * #include <boost/align/aligned_allocator.hpp>
 * typedef double target_type ;
 * typedef std::vector<target_type, boost::alignment::aligned_allocator<target_type, 64>> vector_aligned64_t;
 * #include <stdlib.h>
 * int posix_memalign(void **memptr, size_t alignment, size_t size);
 *  ```
 */

#ifndef REDUX_VECTOR_REDUCE_H
#define REDUX_VECTOR_REDUCE_H
#include <stdint.h>

#ifdef __cplusplus
#include <experimental/simd>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
double vector_reduce_double(const double *src, size_t len, double initial);
/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
float vector_reduce_float(const float *src, size_t len, float initial);
/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
int8_t vector_reduce_int8(const int8_t *src, size_t len, int8_t initial);
/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
int16_t vector_reduce_int16(const int16_t *src, size_t len, int16_t initial);
/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
int32_t vector_reduce_int32(const int32_t *src, size_t len, int32_t initial);
/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
int64_t vector_reduce_int64(const int64_t *src, size_t len, int64_t initial);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
template<typename T>
using vector_t = std::experimental::native_simd<T>;
/*
 * C++ wrapper functions to leverage function overloading for different types
 */


/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
inline double vector_reduce(const double *src, size_t len, double initial = 0.0 )
{
    return vector_reduce_double(src, len, initial);
}

/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
inline float vector_reduce(const float *src, size_t len, float initial = 0.0 )
{
    return vector_reduce_float(src, len, initial);
}

/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
inline int8_t vector_reduce(const int8_t *src, size_t len, int8_t initial = 0)
{
    return vector_reduce_int8(src, len, initial);
}

/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
inline int16_t vector_reduce(const int16_t *src, size_t len, int16_t initial = 0)
{
    return vector_reduce_int16(src, len, initial);
}

/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
inline int32_t vector_reduce(const int32_t *src, size_t len, int32_t initial = 0)
{
    return vector_reduce_int32(src, len, initial);
}

/**
 * @brief perform a reduction of an array
 * @param src source array (aligned to 64 bytes for AVX-512 or 16 bytes for NEON)
 * @param len length of the source array
 * @param initial initial value to start the reduction
 * @return reduced value
 */
inline int64_t vector_reduce(const int64_t *src, size_t len, int64_t initial = 0)
{
    return vector_reduce_int64(src, len, initial);
}

/**
 * @brief perform a reduction of an array using SIMD operations
 * @tparam T
 * @param src
 * @param len
 * @param initial
 * @return
 */
template<typename T>
T vector_reduce_simd(const T *src, size_t len, T initial = 0) ;


/**
 * ruduction using C++ variadic templates.  This is a simple implementation that
 * @tparam T
 * @param data
 * @param len
 * @param initial
 * @return
 */
template<typename T>
T va_reduce(T *data, size_t len, T initial) ;

/**
 * reduction using C++ variadic templates and SIMD operations
 * @tparam T
 * @param data
 * @param len
 * @param initial
 * @return
 */
template<typename T>
T va_reduce_simd(T *data, size_t len, T initial) ;

/**
 * @brief perform a reduction of an array using simple C for loop
 * @tparam T
 * @param src
 * @param len
 * @param initial
 * @return
 */
template<typename T>
T vector_reduce_simple(T *src, size_t len, T initial) ;

/**
 * @brief perform a reduction of an array using SIMD operations in a simple_loop
 * @tparam T
 * @param src
 * @param len
 * @param initial
 * @return
 */
template<typename T>
T vector_reduce_simple_simd(T *src, size_t len, T initial) ;


#endif

#endif //REDUX_VECTOR_REDUCE_H
