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
#include "vector_reduce.h"


inline static auto reduce(auto a, auto b) // terminal case for recursion
{
    return a + b ;
}

inline static auto reduce(auto a, auto b, auto... args) // consume two arguments and recurse
{
    return reduce(reduce(a, b), args...) ;
}


template<typename T>
T va_reduce(T *src, size_t len, T initial)
{
    while( len >= 32 ) {
        initial += reduce(src[0], src[1], src[2], src[3], src[4], src[5], src[6], src[7], src[8], src[9], src[10], src[11], src[12], src[13], src[14], src[15], src[16], src[17], src[18], src[19], src[20], src[21], src[22], src[23], src[24], src[25], src[26], src[27], src[28], src[29], src[30], src[31]) ;
        len -= 32 ;
        src += 32 ;
    } // while
    while( len >= 16 ) {
        initial += reduce(src[0], src[1], src[2], src[3], src[4], src[5], src[6], src[7], src[8], src[9], src[10], src[11], src[12], src[13], src[14], src[15]) ;
        len -= 16 ;
        src += 16 ;
    } // while
    while( len >= 8 ) {
        initial += reduce(src[0], src[1], src[2], src[3], src[4], src[5], src[6], src[7]) ;
        len -= 8 ;
        src += 8 ;
    } // while
    while( len >= 4 ) {
        initial += reduce(src[0], src[1], src[2], src[3]) ;
        len -= 4 ;
        src += 4 ;
    } // while
    while( len >= 2 ) {
        initial += reduce(src[0], src[1]) ;
        len -= 2 ;
        src += 2 ;
    } // while

    if( len != 0 )
        initial += src[0] ;

    return initial ;
}


template double va_reduce<double>(double *, size_t, double) ;
template float va_reduce<float>(float *, size_t, float) ;
template int32_t va_reduce<int32_t>(int32_t *, size_t, int32_t) ;
template int64_t va_reduce<int64_t>(int64_t *, size_t, int64_t) ;