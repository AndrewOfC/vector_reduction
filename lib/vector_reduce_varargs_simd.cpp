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

using namespace std;
namespace stdx = std::experimental;

template<typename T>
using vector_t = stdx::native_simd<T> ;


template<typename T>
inline static vector_t<T> reduce(vector_t<T> a, T *srcB) // terminal case for recursion
{
    vector_t<T> b ;
    b.copy_from(srcB, stdx::vector_aligned);
    return a + b ;
}

inline static auto reduce(auto a, auto srcB, auto... args) // consume argument and recurse
{
    return reduce(reduce(a, srcB), args...) ;
}


template<typename T>
T va_reduce_simd(T *src, size_t len, T initial)
{
    const auto sz = vector_t<T>::size() ;
    vector_t<T> vinitial ;
    /*
     *
     */
    vinitial = 0 ;
    while( len >= 32 * sz ) {
        vinitial += reduce(vector_t<T>(0), &src[0 * sz], &src[1 * sz], &src[2 * sz], &src[3 * sz], &src[4 * sz], &src[5 * sz], &src[6 * sz], &src[7 * sz], &src[8 * sz], &src[9 * sz], &src[10 * sz], &src[11 * sz], &src[12 * sz], &src[13 * sz], &src[14 * sz], &src[15 * sz], &src[16 * sz], &src[17 * sz], &src[18 * sz], &src[19 * sz], &src[20 * sz], &src[21 * sz], &src[22 * sz], &src[23 * sz], &src[24 * sz], &src[25 * sz], &src[26 * sz], &src[27 * sz], &src[28 * sz], &src[29 * sz], &src[30 * sz], &src[31 * sz]) ;
        len -= 32 * sz ;
        src += 32 * sz ;
    } // while

    initial += stdx::reduce(vinitial) ;
    /*
     *
     */
    vinitial = 0 ;
    while( len >= 16 * sz ) {
        vinitial += reduce(vector_t<T>(0), &src[0 * sz], &src[1 * sz], &src[2 * sz], &src[3 * sz], &src[4 * sz], &src[5 * sz], &src[6 * sz], &src[7 * sz], &src[8 * sz], &src[9 * sz], &src[10 * sz], &src[11 * sz], &src[12 * sz], &src[13 * sz], &src[14 * sz], &src[15 * sz]) ;
        len -= 16 * sz ;
        src += 16 * sz ;
    } // while

    initial += stdx::reduce(vinitial) ;
    /*
     *
     */
    vinitial = 0 ;
    while( len >= 8 * sz ) {
        vinitial += reduce(vector_t<T>(0), &src[0 * sz], &src[1 * sz], &src[2 * sz], &src[3 * sz], &src[4 * sz], &src[5 * sz], &src[6 * sz], &src[7 * sz]) ;
        len -= 8 * sz ;
        src += 8 * sz ;
    } // while

    initial += stdx::reduce(vinitial) ;
    /*
     *
     */
    vinitial = 0 ;
    while( len >= 4 * sz ) {
        vinitial += reduce(vector_t<T>(0), &src[0 * sz], &src[1 * sz], &src[2 * sz], &src[3 * sz]) ;
        len -= 4 * sz ;
        src += 4 * sz ;
    } // while

    initial += stdx::reduce(vinitial) ;
    /*
     *
     */
    vinitial = 0 ;
    while( len >= 2 * sz ) {
        vinitial += reduce(vector_t<T>(0), &src[0 * sz], &src[1 * sz]) ;
        len -= 2 * sz ;
        src += 2 * sz ;
    } // while

    initial += stdx::reduce(vinitial) ;
    /*
     *
     */
    vinitial = 0 ;
    while( len >= 1 * sz ) {
        vinitial.copy_from(&src[0], stdx::vector_aligned) ;
        len -= 1 * sz ;
        src += 1 * sz ;
    } // while

    initial += stdx::reduce(vinitial) ;

    // clean up on aisle 3
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }

    return initial ;
}


template double va_reduce_simd<double>(double *, size_t, double) ;
template float va_reduce_simd<float>(float *, size_t, float) ;
template int32_t va_reduce_simd<int32_t>(int32_t *, size_t, int32_t) ;
template int64_t va_reduce_simd<int64_t>(int64_t *, size_t, int64_t) ;