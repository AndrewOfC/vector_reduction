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

template<typename T>
T vector_reduce_cpu(const T *src, size_t len, T initial /* = 0 */)
{
    /*
     *
     */
    while( len >= 32 ) {
        T r00, r01, r02, r03, r04, r05, r06, r07, r08, r09, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31 ;
        r00 = src[0] ;
        r01 = src[1] ;
        r02 = src[2] ;
        r03 = src[3] ;
        r04 = src[4] ;
        r05 = src[5] ;
        r06 = src[6] ;
        r07 = src[7] ;
        r08 = src[8] ;
        r09 = src[9] ;
        r10 = src[10] ;
        r11 = src[11] ;
        r12 = src[12] ;
        r13 = src[13] ;
        r14 = src[14] ;
        r15 = src[15] ;
        r16 = src[16] ;
        r17 = src[17] ;
        r18 = src[18] ;
        r19 = src[19] ;
        r20 = src[20] ;
        r21 = src[21] ;
        r22 = src[22] ;
        r23 = src[23] ;
        r24 = src[24] ;
        r25 = src[25] ;
        r26 = src[26] ;
        r27 = src[27] ;
        r28 = src[28] ;
        r29 = src[29] ;
        r30 = src[30] ;
        r31 = src[31] ;
        
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

        initial += r00 ;

        len -= 32 ;
        src += 32 ;
    } // while
    /*
     *
     */
    while( len >= 16 ) {
        T r00, r01, r02, r03, r04, r05, r06, r07, r08, r09, r10, r11, r12, r13, r14, r15 ;
        r00 = src[0] ;
        r01 = src[1] ;
        r02 = src[2] ;
        r03 = src[3] ;
        r04 = src[4] ;
        r05 = src[5] ;
        r06 = src[6] ;
        r07 = src[7] ;
        r08 = src[8] ;
        r09 = src[9] ;
        r10 = src[10] ;
        r11 = src[11] ;
        r12 = src[12] ;
        r13 = src[13] ;
        r14 = src[14] ;
        r15 = src[15] ;
        
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

        initial += r00 ;

        len -= 16 ;
        src += 16 ;
    } // while
    /*
     *
     */
    while( len >= 8 ) {
        T r00, r01, r02, r03, r04, r05, r06, r07 ;
        r00 = src[0] ;
        r01 = src[1] ;
        r02 = src[2] ;
        r03 = src[3] ;
        r04 = src[4] ;
        r05 = src[5] ;
        r06 = src[6] ;
        r07 = src[7] ;
        
        r00 += r04 ;
        r01 += r05 ;
        r02 += r06 ;
        r03 += r07 ;
        
        r00 += r02 ;
        r01 += r03 ;
        
        r00 += r01 ;

        initial += r00 ;

        len -= 8 ;
        src += 8 ;
    } // while
    /*
     *
     */
    while( len >= 4 ) {
        T r00, r01, r02, r03 ;
        r00 = src[0] ;
        r01 = src[1] ;
        r02 = src[2] ;
        r03 = src[3] ;
        
        r00 += r02 ;
        r01 += r03 ;
        
        r00 += r01 ;

        initial += r00 ;

        len -= 4 ;
        src += 4 ;
    } // while
    /*
     *
     */
    while( len >= 2 ) {
        T r00, r01 ;
        r00 = src[0] ;
        r01 = src[1] ;
        
        r00 += r01 ;

        initial += r00 ;

        len -= 2 ;
        src += 2 ;
    } // while
    /*
     *
     */
    while( len >= 1 ) {
        T r00 ;
        r00 = src[0] ;

        initial += r00 ;

        len -= 1 ;
        src += 1 ;
    } // while
    // clean up on aisle 3
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }

    return initial ;
}

template double vector_reduce_cpu<double>(const double *src, size_t len, double initial /* = 0 */) ;
template float vector_reduce_cpu<float>(const float *src, size_t len, float initial /* = 0 */) ;
template int64_t vector_reduce_cpu<int64_t>(const int64_t *src, size_t len, int64_t initial /* = 0 */) ;
template int32_t vector_reduce_cpu<int32_t>(const int32_t *src, size_t len, int32_t initial /* = 0 */) ;
