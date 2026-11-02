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
#include <stddef.h>
#include "vector_reduce.h"

/*
 *  GENERATED CODE.  Do not make permanent modifications here.
 */
#if defined(__AVX512F__)
#include <immintrin.h>
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#else
#error "Unsupported CPU"
#endif

double vector_reduce_double(const double *src, size_t len, double initial /* = 0 */)
{
#if defined(__AVX512F__)
    /*
     * 
     */
    while( len >= 32 * 8 ) {
        __m512d r000 = _mm512_load_pd(&src[0]);
        __m512d r001 = _mm512_load_pd(&src[8]);
        __m512d r002 = _mm512_load_pd(&src[16]);
        __m512d r003 = _mm512_load_pd(&src[24]);
        __m512d r004 = _mm512_load_pd(&src[32]);
        __m512d r005 = _mm512_load_pd(&src[40]);
        __m512d r006 = _mm512_load_pd(&src[48]);
        __m512d r007 = _mm512_load_pd(&src[56]);
        __m512d r008 = _mm512_load_pd(&src[64]);
        __m512d r009 = _mm512_load_pd(&src[72]);
        __m512d r010 = _mm512_load_pd(&src[80]);
        __m512d r011 = _mm512_load_pd(&src[88]);
        __m512d r012 = _mm512_load_pd(&src[96]);
        __m512d r013 = _mm512_load_pd(&src[104]);
        __m512d r014 = _mm512_load_pd(&src[112]);
        __m512d r015 = _mm512_load_pd(&src[120]);
        __m512d r016 = _mm512_load_pd(&src[128]);
        __m512d r017 = _mm512_load_pd(&src[136]);
        __m512d r018 = _mm512_load_pd(&src[144]);
        __m512d r019 = _mm512_load_pd(&src[152]);
        __m512d r020 = _mm512_load_pd(&src[160]);
        __m512d r021 = _mm512_load_pd(&src[168]);
        __m512d r022 = _mm512_load_pd(&src[176]);
        __m512d r023 = _mm512_load_pd(&src[184]);
        __m512d r024 = _mm512_load_pd(&src[192]);
        __m512d r025 = _mm512_load_pd(&src[200]);
        __m512d r026 = _mm512_load_pd(&src[208]);
        __m512d r027 = _mm512_load_pd(&src[216]);
        __m512d r028 = _mm512_load_pd(&src[224]);
        __m512d r029 = _mm512_load_pd(&src[232]);
        __m512d r030 = _mm512_load_pd(&src[240]);
        __m512d r031 = _mm512_load_pd(&src[248]);
        
        r000 = _mm512_add_pd(r000, r016);
        r001 = _mm512_add_pd(r001, r017);
        r002 = _mm512_add_pd(r002, r018);
        r003 = _mm512_add_pd(r003, r019);
        r004 = _mm512_add_pd(r004, r020);
        r005 = _mm512_add_pd(r005, r021);
        r006 = _mm512_add_pd(r006, r022);
        r007 = _mm512_add_pd(r007, r023);
        r008 = _mm512_add_pd(r008, r024);
        r009 = _mm512_add_pd(r009, r025);
        r010 = _mm512_add_pd(r010, r026);
        r011 = _mm512_add_pd(r011, r027);
        r012 = _mm512_add_pd(r012, r028);
        r013 = _mm512_add_pd(r013, r029);
        r014 = _mm512_add_pd(r014, r030);
        r015 = _mm512_add_pd(r015, r031);
        
        r000 = _mm512_add_pd(r000, r008);
        r001 = _mm512_add_pd(r001, r009);
        r002 = _mm512_add_pd(r002, r010);
        r003 = _mm512_add_pd(r003, r011);
        r004 = _mm512_add_pd(r004, r012);
        r005 = _mm512_add_pd(r005, r013);
        r006 = _mm512_add_pd(r006, r014);
        r007 = _mm512_add_pd(r007, r015);
        
        r000 = _mm512_add_pd(r000, r004);
        r001 = _mm512_add_pd(r001, r005);
        r002 = _mm512_add_pd(r002, r006);
        r003 = _mm512_add_pd(r003, r007);
        
        r000 = _mm512_add_pd(r000, r002);
        r001 = _mm512_add_pd(r001, r003);
        
        r000 = _mm512_add_pd(r000, r001);

        initial += _mm512_reduce_add_pd(r000) ;
        

        len -= 32 * 8 ;
        src += 32 * 8  ;
    } // while
    /*
     * 
     */
    while( len >= 16 * 8 ) {
        __m512d r000 = _mm512_load_pd(&src[0]);
        __m512d r001 = _mm512_load_pd(&src[8]);
        __m512d r002 = _mm512_load_pd(&src[16]);
        __m512d r003 = _mm512_load_pd(&src[24]);
        __m512d r004 = _mm512_load_pd(&src[32]);
        __m512d r005 = _mm512_load_pd(&src[40]);
        __m512d r006 = _mm512_load_pd(&src[48]);
        __m512d r007 = _mm512_load_pd(&src[56]);
        __m512d r008 = _mm512_load_pd(&src[64]);
        __m512d r009 = _mm512_load_pd(&src[72]);
        __m512d r010 = _mm512_load_pd(&src[80]);
        __m512d r011 = _mm512_load_pd(&src[88]);
        __m512d r012 = _mm512_load_pd(&src[96]);
        __m512d r013 = _mm512_load_pd(&src[104]);
        __m512d r014 = _mm512_load_pd(&src[112]);
        __m512d r015 = _mm512_load_pd(&src[120]);
        
        r000 = _mm512_add_pd(r000, r008);
        r001 = _mm512_add_pd(r001, r009);
        r002 = _mm512_add_pd(r002, r010);
        r003 = _mm512_add_pd(r003, r011);
        r004 = _mm512_add_pd(r004, r012);
        r005 = _mm512_add_pd(r005, r013);
        r006 = _mm512_add_pd(r006, r014);
        r007 = _mm512_add_pd(r007, r015);
        
        r000 = _mm512_add_pd(r000, r004);
        r001 = _mm512_add_pd(r001, r005);
        r002 = _mm512_add_pd(r002, r006);
        r003 = _mm512_add_pd(r003, r007);
        
        r000 = _mm512_add_pd(r000, r002);
        r001 = _mm512_add_pd(r001, r003);
        
        r000 = _mm512_add_pd(r000, r001);

        initial += _mm512_reduce_add_pd(r000) ;
        

        len -= 16 * 8 ;
        src += 16 * 8  ;
    } // while
    /*
     * 
     */
    while( len >= 8 * 8 ) {
        __m512d r000 = _mm512_load_pd(&src[0]);
        __m512d r001 = _mm512_load_pd(&src[8]);
        __m512d r002 = _mm512_load_pd(&src[16]);
        __m512d r003 = _mm512_load_pd(&src[24]);
        __m512d r004 = _mm512_load_pd(&src[32]);
        __m512d r005 = _mm512_load_pd(&src[40]);
        __m512d r006 = _mm512_load_pd(&src[48]);
        __m512d r007 = _mm512_load_pd(&src[56]);
        
        r000 = _mm512_add_pd(r000, r004);
        r001 = _mm512_add_pd(r001, r005);
        r002 = _mm512_add_pd(r002, r006);
        r003 = _mm512_add_pd(r003, r007);
        
        r000 = _mm512_add_pd(r000, r002);
        r001 = _mm512_add_pd(r001, r003);
        
        r000 = _mm512_add_pd(r000, r001);

        initial += _mm512_reduce_add_pd(r000) ;
        

        len -= 8 * 8 ;
        src += 8 * 8  ;
    } // while
    /*
     * 
     */
    while( len >= 4 * 8 ) {
        __m512d r000 = _mm512_load_pd(&src[0]);
        __m512d r001 = _mm512_load_pd(&src[8]);
        __m512d r002 = _mm512_load_pd(&src[16]);
        __m512d r003 = _mm512_load_pd(&src[24]);
        
        r000 = _mm512_add_pd(r000, r002);
        r001 = _mm512_add_pd(r001, r003);
        
        r000 = _mm512_add_pd(r000, r001);

        initial += _mm512_reduce_add_pd(r000) ;
        

        len -= 4 * 8 ;
        src += 4 * 8  ;
    } // while
    /*
     * 
     */
    while( len >= 2 * 8 ) {
        __m512d r000 = _mm512_load_pd(&src[0]);
        __m512d r001 = _mm512_load_pd(&src[8]);
        
        r000 = _mm512_add_pd(r000, r001);

        initial += _mm512_reduce_add_pd(r000) ;
        

        len -= 2 * 8 ;
        src += 2 * 8  ;
    } // while
    /*
     * 
     */
    while( len >= 1 * 8 ) {
        __m512d r000 = _mm512_load_pd(&src[0]);

        initial += _mm512_reduce_add_pd(r000) ;
        

        len -= 1 * 8 ;
        src += 1 * 8  ;
    } // while

    // clean up on aisle 3
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }

    return initial ;
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
    /*
     * 
     */
    while( len >= 32 * 2 ) {
        float64x2_t r000 = vld1q_f64(&src[0]);
        float64x2_t r001 = vld1q_f64(&src[2]);
        float64x2_t r002 = vld1q_f64(&src[4]);
        float64x2_t r003 = vld1q_f64(&src[6]);
        float64x2_t r004 = vld1q_f64(&src[8]);
        float64x2_t r005 = vld1q_f64(&src[10]);
        float64x2_t r006 = vld1q_f64(&src[12]);
        float64x2_t r007 = vld1q_f64(&src[14]);
        float64x2_t r008 = vld1q_f64(&src[16]);
        float64x2_t r009 = vld1q_f64(&src[18]);
        float64x2_t r010 = vld1q_f64(&src[20]);
        float64x2_t r011 = vld1q_f64(&src[22]);
        float64x2_t r012 = vld1q_f64(&src[24]);
        float64x2_t r013 = vld1q_f64(&src[26]);
        float64x2_t r014 = vld1q_f64(&src[28]);
        float64x2_t r015 = vld1q_f64(&src[30]);
        float64x2_t r016 = vld1q_f64(&src[32]);
        float64x2_t r017 = vld1q_f64(&src[34]);
        float64x2_t r018 = vld1q_f64(&src[36]);
        float64x2_t r019 = vld1q_f64(&src[38]);
        float64x2_t r020 = vld1q_f64(&src[40]);
        float64x2_t r021 = vld1q_f64(&src[42]);
        float64x2_t r022 = vld1q_f64(&src[44]);
        float64x2_t r023 = vld1q_f64(&src[46]);
        float64x2_t r024 = vld1q_f64(&src[48]);
        float64x2_t r025 = vld1q_f64(&src[50]);
        float64x2_t r026 = vld1q_f64(&src[52]);
        float64x2_t r027 = vld1q_f64(&src[54]);
        float64x2_t r028 = vld1q_f64(&src[56]);
        float64x2_t r029 = vld1q_f64(&src[58]);
        float64x2_t r030 = vld1q_f64(&src[60]);
        float64x2_t r031 = vld1q_f64(&src[62]);
        
        r000 = vaddq_f64(r000, r016);
        r001 = vaddq_f64(r001, r017);
        r002 = vaddq_f64(r002, r018);
        r003 = vaddq_f64(r003, r019);
        r004 = vaddq_f64(r004, r020);
        r005 = vaddq_f64(r005, r021);
        r006 = vaddq_f64(r006, r022);
        r007 = vaddq_f64(r007, r023);
        r008 = vaddq_f64(r008, r024);
        r009 = vaddq_f64(r009, r025);
        r010 = vaddq_f64(r010, r026);
        r011 = vaddq_f64(r011, r027);
        r012 = vaddq_f64(r012, r028);
        r013 = vaddq_f64(r013, r029);
        r014 = vaddq_f64(r014, r030);
        r015 = vaddq_f64(r015, r031);
        
        r000 = vaddq_f64(r000, r008);
        r001 = vaddq_f64(r001, r009);
        r002 = vaddq_f64(r002, r010);
        r003 = vaddq_f64(r003, r011);
        r004 = vaddq_f64(r004, r012);
        r005 = vaddq_f64(r005, r013);
        r006 = vaddq_f64(r006, r014);
        r007 = vaddq_f64(r007, r015);
        
        r000 = vaddq_f64(r000, r004);
        r001 = vaddq_f64(r001, r005);
        r002 = vaddq_f64(r002, r006);
        r003 = vaddq_f64(r003, r007);
        
        r000 = vaddq_f64(r000, r002);
        r001 = vaddq_f64(r001, r003);
        
        r000 = vaddq_f64(r000, r001);

        
        initial += vgetq_lane_f64(r000, 0) + vgetq_lane_f64(r000, 1) ;
        

        len -= 32 * 2 ;
        src += 32 * 2  ;
    } // while
    /*
     * 
     */
    while( len >= 16 * 2 ) {
        float64x2_t r000 = vld1q_f64(&src[0]);
        float64x2_t r001 = vld1q_f64(&src[2]);
        float64x2_t r002 = vld1q_f64(&src[4]);
        float64x2_t r003 = vld1q_f64(&src[6]);
        float64x2_t r004 = vld1q_f64(&src[8]);
        float64x2_t r005 = vld1q_f64(&src[10]);
        float64x2_t r006 = vld1q_f64(&src[12]);
        float64x2_t r007 = vld1q_f64(&src[14]);
        float64x2_t r008 = vld1q_f64(&src[16]);
        float64x2_t r009 = vld1q_f64(&src[18]);
        float64x2_t r010 = vld1q_f64(&src[20]);
        float64x2_t r011 = vld1q_f64(&src[22]);
        float64x2_t r012 = vld1q_f64(&src[24]);
        float64x2_t r013 = vld1q_f64(&src[26]);
        float64x2_t r014 = vld1q_f64(&src[28]);
        float64x2_t r015 = vld1q_f64(&src[30]);
        
        r000 = vaddq_f64(r000, r008);
        r001 = vaddq_f64(r001, r009);
        r002 = vaddq_f64(r002, r010);
        r003 = vaddq_f64(r003, r011);
        r004 = vaddq_f64(r004, r012);
        r005 = vaddq_f64(r005, r013);
        r006 = vaddq_f64(r006, r014);
        r007 = vaddq_f64(r007, r015);
        
        r000 = vaddq_f64(r000, r004);
        r001 = vaddq_f64(r001, r005);
        r002 = vaddq_f64(r002, r006);
        r003 = vaddq_f64(r003, r007);
        
        r000 = vaddq_f64(r000, r002);
        r001 = vaddq_f64(r001, r003);
        
        r000 = vaddq_f64(r000, r001);

        
        initial += vgetq_lane_f64(r000, 0) + vgetq_lane_f64(r000, 1) ;
        

        len -= 16 * 2 ;
        src += 16 * 2  ;
    } // while
    /*
     * 
     */
    while( len >= 8 * 2 ) {
        float64x2_t r000 = vld1q_f64(&src[0]);
        float64x2_t r001 = vld1q_f64(&src[2]);
        float64x2_t r002 = vld1q_f64(&src[4]);
        float64x2_t r003 = vld1q_f64(&src[6]);
        float64x2_t r004 = vld1q_f64(&src[8]);
        float64x2_t r005 = vld1q_f64(&src[10]);
        float64x2_t r006 = vld1q_f64(&src[12]);
        float64x2_t r007 = vld1q_f64(&src[14]);
        
        r000 = vaddq_f64(r000, r004);
        r001 = vaddq_f64(r001, r005);
        r002 = vaddq_f64(r002, r006);
        r003 = vaddq_f64(r003, r007);
        
        r000 = vaddq_f64(r000, r002);
        r001 = vaddq_f64(r001, r003);
        
        r000 = vaddq_f64(r000, r001);

        
        initial += vgetq_lane_f64(r000, 0) + vgetq_lane_f64(r000, 1) ;
        

        len -= 8 * 2 ;
        src += 8 * 2  ;
    } // while
    /*
     * 
     */
    while( len >= 4 * 2 ) {
        float64x2_t r000 = vld1q_f64(&src[0]);
        float64x2_t r001 = vld1q_f64(&src[2]);
        float64x2_t r002 = vld1q_f64(&src[4]);
        float64x2_t r003 = vld1q_f64(&src[6]);
        
        r000 = vaddq_f64(r000, r002);
        r001 = vaddq_f64(r001, r003);
        
        r000 = vaddq_f64(r000, r001);

        
        initial += vgetq_lane_f64(r000, 0) + vgetq_lane_f64(r000, 1) ;
        

        len -= 4 * 2 ;
        src += 4 * 2  ;
    } // while
    /*
     * 
     */
    while( len >= 2 * 2 ) {
        float64x2_t r000 = vld1q_f64(&src[0]);
        float64x2_t r001 = vld1q_f64(&src[2]);
        
        r000 = vaddq_f64(r000, r001);

        
        initial += vgetq_lane_f64(r000, 0) + vgetq_lane_f64(r000, 1) ;
        

        len -= 2 * 2 ;
        src += 2 * 2  ;
    } // while
    /*
     * 
     */
    while( len >= 1 * 2 ) {
        float64x2_t r000 = vld1q_f64(&src[0]);

        
        initial += vgetq_lane_f64(r000, 0) + vgetq_lane_f64(r000, 1) ;
        

        len -= 1 * 2 ;
        src += 1 * 2  ;
    } // while

    // clean up on aisle 3
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }

    return initial ;
#else
#error "Unsupported CPU or no vectorization defined"
#endif
}