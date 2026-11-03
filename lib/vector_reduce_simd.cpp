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


/*
 *  GENERATED CODE.  Do not make permanent modifications here.
 */
#include "vector_reduce.h"
namespace stdx = std::experimental;

int Unfolds = 32 ;

template<typename T>
T vector_reduce_simd(const T *src, size_t len, T initial /* = 0 */)
{
    const auto sz = vector_t<T>::size() ;
    /*
     *
     */
    while( len >= 32 * sz ) {
        vector_t<T> r00, r01, r02, r03, r04, r05, r06, r07, r08, r09, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31 ;
        r00.copy_from(&src[0 * sz], stdx::vector_aligned) ;
        r01.copy_from(&src[1 * sz], stdx::vector_aligned) ;
        r02.copy_from(&src[2 * sz], stdx::vector_aligned) ;
        r03.copy_from(&src[3 * sz], stdx::vector_aligned) ;
        r04.copy_from(&src[4 * sz], stdx::vector_aligned) ;
        r05.copy_from(&src[5 * sz], stdx::vector_aligned) ;
        r06.copy_from(&src[6 * sz], stdx::vector_aligned) ;
        r07.copy_from(&src[7 * sz], stdx::vector_aligned) ;
        r08.copy_from(&src[8 * sz], stdx::vector_aligned) ;
        r09.copy_from(&src[9 * sz], stdx::vector_aligned) ;
        r10.copy_from(&src[10 * sz], stdx::vector_aligned) ;
        r11.copy_from(&src[11 * sz], stdx::vector_aligned) ;
        r12.copy_from(&src[12 * sz], stdx::vector_aligned) ;
        r13.copy_from(&src[13 * sz], stdx::vector_aligned) ;
        r14.copy_from(&src[14 * sz], stdx::vector_aligned) ;
        r15.copy_from(&src[15 * sz], stdx::vector_aligned) ;
        r16.copy_from(&src[16 * sz], stdx::vector_aligned) ;
        r17.copy_from(&src[17 * sz], stdx::vector_aligned) ;
        r18.copy_from(&src[18 * sz], stdx::vector_aligned) ;
        r19.copy_from(&src[19 * sz], stdx::vector_aligned) ;
        r20.copy_from(&src[20 * sz], stdx::vector_aligned) ;
        r21.copy_from(&src[21 * sz], stdx::vector_aligned) ;
        r22.copy_from(&src[22 * sz], stdx::vector_aligned) ;
        r23.copy_from(&src[23 * sz], stdx::vector_aligned) ;
        r24.copy_from(&src[24 * sz], stdx::vector_aligned) ;
        r25.copy_from(&src[25 * sz], stdx::vector_aligned) ;
        r26.copy_from(&src[26 * sz], stdx::vector_aligned) ;
        r27.copy_from(&src[27 * sz], stdx::vector_aligned) ;
        r28.copy_from(&src[28 * sz], stdx::vector_aligned) ;
        r29.copy_from(&src[29 * sz], stdx::vector_aligned) ;
        r30.copy_from(&src[30 * sz], stdx::vector_aligned) ;
        r31.copy_from(&src[31 * sz], stdx::vector_aligned) ;
        
        r00 += r16 ;
        r01 += r17 ;
        r02 += r18 ;
        r03 += r19 ;
        r04 += r20 ;
        r05 += r21 ;
        r06 += r22 ;
        r07 += r23 ;
        r08 += r24 ;
        r09 += r25 ;
        r10 += r26 ;
        r11 += r27 ;
        r12 += r28 ;
        r13 += r29 ;
        r14 += r30 ;
        r15 += r31 ;
        
        r00 += r08 ;
        r01 += r09 ;
        r02 += r10 ;
        r03 += r11 ;
        r04 += r12 ;
        r05 += r13 ;
        r06 += r14 ;
        r07 += r15 ;
        
        r00 += r04 ;
        r01 += r05 ;
        r02 += r06 ;
        r03 += r07 ;
        
        r00 += r02 ;
        r01 += r03 ;
        
        r00 += r01 ;

        initial += stdx::reduce(r00) ;

        len -= 32 * sz ;
        src += 32 * sz ;
    } // while
    /*
     *
     */
    while( len >= 16 * sz ) {
        vector_t<T> r00, r01, r02, r03, r04, r05, r06, r07, r08, r09, r10, r11, r12, r13, r14, r15 ;
        r00.copy_from(&src[0 * sz], stdx::vector_aligned) ;
        r01.copy_from(&src[1 * sz], stdx::vector_aligned) ;
        r02.copy_from(&src[2 * sz], stdx::vector_aligned) ;
        r03.copy_from(&src[3 * sz], stdx::vector_aligned) ;
        r04.copy_from(&src[4 * sz], stdx::vector_aligned) ;
        r05.copy_from(&src[5 * sz], stdx::vector_aligned) ;
        r06.copy_from(&src[6 * sz], stdx::vector_aligned) ;
        r07.copy_from(&src[7 * sz], stdx::vector_aligned) ;
        r08.copy_from(&src[8 * sz], stdx::vector_aligned) ;
        r09.copy_from(&src[9 * sz], stdx::vector_aligned) ;
        r10.copy_from(&src[10 * sz], stdx::vector_aligned) ;
        r11.copy_from(&src[11 * sz], stdx::vector_aligned) ;
        r12.copy_from(&src[12 * sz], stdx::vector_aligned) ;
        r13.copy_from(&src[13 * sz], stdx::vector_aligned) ;
        r14.copy_from(&src[14 * sz], stdx::vector_aligned) ;
        r15.copy_from(&src[15 * sz], stdx::vector_aligned) ;
        
        r00 += r08 ;
        r01 += r09 ;
        r02 += r10 ;
        r03 += r11 ;
        r04 += r12 ;
        r05 += r13 ;
        r06 += r14 ;
        r07 += r15 ;
        
        r00 += r04 ;
        r01 += r05 ;
        r02 += r06 ;
        r03 += r07 ;
        
        r00 += r02 ;
        r01 += r03 ;
        
        r00 += r01 ;

        initial += stdx::reduce(r00) ;

        len -= 16 * sz ;
        src += 16 * sz ;
    } // while
    /*
     *
     */
    while( len >= 8 * sz ) {
        vector_t<T> r00, r01, r02, r03, r04, r05, r06, r07 ;
        r00.copy_from(&src[0 * sz], stdx::vector_aligned) ;
        r01.copy_from(&src[1 * sz], stdx::vector_aligned) ;
        r02.copy_from(&src[2 * sz], stdx::vector_aligned) ;
        r03.copy_from(&src[3 * sz], stdx::vector_aligned) ;
        r04.copy_from(&src[4 * sz], stdx::vector_aligned) ;
        r05.copy_from(&src[5 * sz], stdx::vector_aligned) ;
        r06.copy_from(&src[6 * sz], stdx::vector_aligned) ;
        r07.copy_from(&src[7 * sz], stdx::vector_aligned) ;
        
        r00 += r04 ;
        r01 += r05 ;
        r02 += r06 ;
        r03 += r07 ;
        
        r00 += r02 ;
        r01 += r03 ;
        
        r00 += r01 ;

        initial += stdx::reduce(r00) ;

        len -= 8 * sz ;
        src += 8 * sz ;
    } // while
    /*
     *
     */
    while( len >= 4 * sz ) {
        vector_t<T> r00, r01, r02, r03 ;
        r00.copy_from(&src[0 * sz], stdx::vector_aligned) ;
        r01.copy_from(&src[1 * sz], stdx::vector_aligned) ;
        r02.copy_from(&src[2 * sz], stdx::vector_aligned) ;
        r03.copy_from(&src[3 * sz], stdx::vector_aligned) ;
        
        r00 += r02 ;
        r01 += r03 ;
        
        r00 += r01 ;

        initial += stdx::reduce(r00) ;

        len -= 4 * sz ;
        src += 4 * sz ;
    } // while
    /*
     *
     */
    while( len >= 2 * sz ) {
        vector_t<T> r00, r01 ;
        r00.copy_from(&src[0 * sz], stdx::vector_aligned) ;
        r01.copy_from(&src[1 * sz], stdx::vector_aligned) ;
        
        r00 += r01 ;

        initial += stdx::reduce(r00) ;

        len -= 2 * sz ;
        src += 2 * sz ;
    } // while
    /*
     *
     */
    while( len >= 1 * sz ) {
        vector_t<T> r00 ;
        r00.copy_from(&src[0 * sz], stdx::vector_aligned) ;

        initial += stdx::reduce(r00) ;

        len -= 1 * sz ;
        src += 1 * sz ;
    } // while
    // clean up on aisle 3
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }

    return initial ;
}

template double vector_reduce_simd<double>(const double *src, size_t len, double initial /* = 0 */) ;
template float vector_reduce_simd<float>(const float *src, size_t len, float initial /* = 0 */) ;
template int64_t vector_reduce_simd<int64_t>(const int64_t *src, size_t len, int64_t initial /* = 0 */) ;
template int32_t vector_reduce_simd<int32_t>(const int32_t *src, size_t len, int32_t initial /* = 0 */) ;
