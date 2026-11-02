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
// Created by ANDREW PAGE on 10/19/26.
//

#include <experimental/simd>

using namespace std;
namespace stdx = std::experimental;

template<typename T>
T vector_reduce_simple(T *src, size_t len, T initial)
{
    for(size_t i = 0; i < len; i++)
    {
        initial += src[i];
    }
    return initial;
}

template double vector_reduce_simple<double>(double *src, size_t len, double initial);
template float vector_reduce_simple<float>(float *src, size_t len, float initial);
template int8_t vector_reduce_simple<int8_t>(int8_t *src, size_t len, int8_t initial);
template int16_t vector_reduce_simple<int16_t>(int16_t *src, size_t len, int16_t initial);
template int32_t vector_reduce_simple<int32_t>(int32_t *src, size_t len, int32_t initial);
template int64_t vector_reduce_simple<int64_t>(int64_t *src, size_t len, int64_t initial);

template<typename T>
T vector_reduce_simple_simd(T *src, size_t len, T initial)
{
    typedef stdx::native_simd<T> vector_t ;
    vector_t r, vinitial(0) ;
    size_t n = len / vector_t::size() ;
//#pragma GCC unroll 4
    for ( size_t i = 0 ; i < n ; i++ )
    {
        r.copy_from(src, stdx::vector_aligned);
        vinitial += r;
        len -= vector_t::size();
        src += vector_t::size();
    }
    initial += stdx::reduce(vinitial) ;
//#pragma GCC unroll 4
    for( size_t i = 0 ; i < len % vector_t::size() ; i++, src++ ) {
        initial += *src ;
    }
    return initial;
}

template double vector_reduce_simple_simd<double>(double *src, size_t len, double initial);
template float vector_reduce_simple_simd<float>(float *src, size_t len, float initial);
template int8_t vector_reduce_simple_simd<int8_t>(int8_t *src, size_t len, int8_t initial);
template int16_t vector_reduce_simple_simd<int16_t>(int16_t *src, size_t len, int16_t initial);
template int32_t vector_reduce_simple_simd<int32_t>(int32_t *src, size_t len, int32_t initial);
template int64_t vector_reduce_simple_simd<int64_t>(int64_t *src, size_t len, int64_t initial);

