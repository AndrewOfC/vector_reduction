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

float vector_reduce_float(const float *src, size_t len, float initial /* = 0 */)
{
#if defined(__AVX512F__)
    /*
     * 
     */
    while( len >= 32 * 16 ) {
        __m512 r000 = _mm512_load_ps(&src[0]) ;
        __m512 r001 = _mm512_load_ps(&src[16]) ;
        __m512 r002 = _mm512_load_ps(&src[32]) ;
        __m512 r003 = _mm512_load_ps(&src[48]) ;
        __m512 r004 = _mm512_load_ps(&src[64]) ;
        __m512 r005 = _mm512_load_ps(&src[80]) ;
        __m512 r006 = _mm512_load_ps(&src[96]) ;
        __m512 r007 = _mm512_load_ps(&src[112]) ;
        __m512 r008 = _mm512_load_ps(&src[128]) ;
        __m512 r009 = _mm512_load_ps(&src[144]) ;
        __m512 r010 = _mm512_load_ps(&src[160]) ;
        __m512 r011 = _mm512_load_ps(&src[176]) ;
        __m512 r012 = _mm512_load_ps(&src[192]) ;
        __m512 r013 = _mm512_load_ps(&src[208]) ;
        __m512 r014 = _mm512_load_ps(&src[224]) ;
        __m512 r015 = _mm512_load_ps(&src[240]) ;
        __m512 r016 = _mm512_load_ps(&src[256]) ;
        __m512 r017 = _mm512_load_ps(&src[272]) ;
        __m512 r018 = _mm512_load_ps(&src[288]) ;
        __m512 r019 = _mm512_load_ps(&src[304]) ;
        __m512 r020 = _mm512_load_ps(&src[320]) ;
        __m512 r021 = _mm512_load_ps(&src[336]) ;
        __m512 r022 = _mm512_load_ps(&src[352]) ;
        __m512 r023 = _mm512_load_ps(&src[368]) ;
        __m512 r024 = _mm512_load_ps(&src[384]) ;
        __m512 r025 = _mm512_load_ps(&src[400]) ;
        __m512 r026 = _mm512_load_ps(&src[416]) ;
        __m512 r027 = _mm512_load_ps(&src[432]) ;
        __m512 r028 = _mm512_load_ps(&src[448]) ;
        __m512 r029 = _mm512_load_ps(&src[464]) ;
        __m512 r030 = _mm512_load_ps(&src[480]) ;
        __m512 r031 = _mm512_load_ps(&src[496]) ;
        
        r000 = _mm512_add_ps(r000, r016) ;
        r001 = _mm512_add_ps(r001, r017) ;
        r002 = _mm512_add_ps(r002, r018) ;
        r003 = _mm512_add_ps(r003, r019) ;
        r004 = _mm512_add_ps(r004, r020) ;
        r005 = _mm512_add_ps(r005, r021) ;
        r006 = _mm512_add_ps(r006, r022) ;
        r007 = _mm512_add_ps(r007, r023) ;
        r008 = _mm512_add_ps(r008, r024) ;
        r009 = _mm512_add_ps(r009, r025) ;
        r010 = _mm512_add_ps(r010, r026) ;
        r011 = _mm512_add_ps(r011, r027) ;
        r012 = _mm512_add_ps(r012, r028) ;
        r013 = _mm512_add_ps(r013, r029) ;
        r014 = _mm512_add_ps(r014, r030) ;
        r015 = _mm512_add_ps(r015, r031) ;
        
        r000 = _mm512_add_ps(r000, r008) ;
        r001 = _mm512_add_ps(r001, r009) ;
        r002 = _mm512_add_ps(r002, r010) ;
        r003 = _mm512_add_ps(r003, r011) ;
        r004 = _mm512_add_ps(r004, r012) ;
        r005 = _mm512_add_ps(r005, r013) ;
        r006 = _mm512_add_ps(r006, r014) ;
        r007 = _mm512_add_ps(r007, r015) ;
        
        r000 = _mm512_add_ps(r000, r004) ;
        r001 = _mm512_add_ps(r001, r005) ;
        r002 = _mm512_add_ps(r002, r006) ;
        r003 = _mm512_add_ps(r003, r007) ;
        
        r000 = _mm512_add_ps(r000, r002) ;
        r001 = _mm512_add_ps(r001, r003) ;
        
        r000 = _mm512_add_ps(r000, r001) ;

        initial += _mm512_reduce_add_ps(r000) ;
        
        
        len -= 32 * 16 ;
        src += 32 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 16 * 16 ) {
        __m512 r000 = _mm512_load_ps(&src[0]) ;
        __m512 r001 = _mm512_load_ps(&src[16]) ;
        __m512 r002 = _mm512_load_ps(&src[32]) ;
        __m512 r003 = _mm512_load_ps(&src[48]) ;
        __m512 r004 = _mm512_load_ps(&src[64]) ;
        __m512 r005 = _mm512_load_ps(&src[80]) ;
        __m512 r006 = _mm512_load_ps(&src[96]) ;
        __m512 r007 = _mm512_load_ps(&src[112]) ;
        __m512 r008 = _mm512_load_ps(&src[128]) ;
        __m512 r009 = _mm512_load_ps(&src[144]) ;
        __m512 r010 = _mm512_load_ps(&src[160]) ;
        __m512 r011 = _mm512_load_ps(&src[176]) ;
        __m512 r012 = _mm512_load_ps(&src[192]) ;
        __m512 r013 = _mm512_load_ps(&src[208]) ;
        __m512 r014 = _mm512_load_ps(&src[224]) ;
        __m512 r015 = _mm512_load_ps(&src[240]) ;
        
        r000 = _mm512_add_ps(r000, r008) ;
        r001 = _mm512_add_ps(r001, r009) ;
        r002 = _mm512_add_ps(r002, r010) ;
        r003 = _mm512_add_ps(r003, r011) ;
        r004 = _mm512_add_ps(r004, r012) ;
        r005 = _mm512_add_ps(r005, r013) ;
        r006 = _mm512_add_ps(r006, r014) ;
        r007 = _mm512_add_ps(r007, r015) ;
        
        r000 = _mm512_add_ps(r000, r004) ;
        r001 = _mm512_add_ps(r001, r005) ;
        r002 = _mm512_add_ps(r002, r006) ;
        r003 = _mm512_add_ps(r003, r007) ;
        
        r000 = _mm512_add_ps(r000, r002) ;
        r001 = _mm512_add_ps(r001, r003) ;
        
        r000 = _mm512_add_ps(r000, r001) ;

        initial += _mm512_reduce_add_ps(r000) ;
        
        
        len -= 16 * 16 ;
        src += 16 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 8 * 16 ) {
        __m512 r000 = _mm512_load_ps(&src[0]) ;
        __m512 r001 = _mm512_load_ps(&src[16]) ;
        __m512 r002 = _mm512_load_ps(&src[32]) ;
        __m512 r003 = _mm512_load_ps(&src[48]) ;
        __m512 r004 = _mm512_load_ps(&src[64]) ;
        __m512 r005 = _mm512_load_ps(&src[80]) ;
        __m512 r006 = _mm512_load_ps(&src[96]) ;
        __m512 r007 = _mm512_load_ps(&src[112]) ;
        
        r000 = _mm512_add_ps(r000, r004) ;
        r001 = _mm512_add_ps(r001, r005) ;
        r002 = _mm512_add_ps(r002, r006) ;
        r003 = _mm512_add_ps(r003, r007) ;
        
        r000 = _mm512_add_ps(r000, r002) ;
        r001 = _mm512_add_ps(r001, r003) ;
        
        r000 = _mm512_add_ps(r000, r001) ;

        initial += _mm512_reduce_add_ps(r000) ;
        
        
        len -= 8 * 16 ;
        src += 8 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 4 * 16 ) {
        __m512 r000 = _mm512_load_ps(&src[0]) ;
        __m512 r001 = _mm512_load_ps(&src[16]) ;
        __m512 r002 = _mm512_load_ps(&src[32]) ;
        __m512 r003 = _mm512_load_ps(&src[48]) ;
        
        r000 = _mm512_add_ps(r000, r002) ;
        r001 = _mm512_add_ps(r001, r003) ;
        
        r000 = _mm512_add_ps(r000, r001) ;

        initial += _mm512_reduce_add_ps(r000) ;
        
        
        len -= 4 * 16 ;
        src += 4 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 2 * 16 ) {
        __m512 r000 = _mm512_load_ps(&src[0]) ;
        __m512 r001 = _mm512_load_ps(&src[16]) ;
        
        r000 = _mm512_add_ps(r000, r001) ;

        initial += _mm512_reduce_add_ps(r000) ;
        
        
        len -= 2 * 16 ;
        src += 2 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 1 * 16 ) {
        __m512 r000 = _mm512_load_ps(&src[0]) ;

        initial += _mm512_reduce_add_ps(r000) ;
        
        
        len -= 1 * 16 ;
        src += 1 * 16  ;
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
    while( len >= 32 * 4 ) {
        float32x4_t r000 = vld1q_f32(&src[0]) ;
        float32x4_t r001 = vld1q_f32(&src[4]) ;
        float32x4_t r002 = vld1q_f32(&src[8]) ;
        float32x4_t r003 = vld1q_f32(&src[12]) ;
        float32x4_t r004 = vld1q_f32(&src[16]) ;
        float32x4_t r005 = vld1q_f32(&src[20]) ;
        float32x4_t r006 = vld1q_f32(&src[24]) ;
        float32x4_t r007 = vld1q_f32(&src[28]) ;
        float32x4_t r008 = vld1q_f32(&src[32]) ;
        float32x4_t r009 = vld1q_f32(&src[36]) ;
        float32x4_t r010 = vld1q_f32(&src[40]) ;
        float32x4_t r011 = vld1q_f32(&src[44]) ;
        float32x4_t r012 = vld1q_f32(&src[48]) ;
        float32x4_t r013 = vld1q_f32(&src[52]) ;
        float32x4_t r014 = vld1q_f32(&src[56]) ;
        float32x4_t r015 = vld1q_f32(&src[60]) ;
        float32x4_t r016 = vld1q_f32(&src[64]) ;
        float32x4_t r017 = vld1q_f32(&src[68]) ;
        float32x4_t r018 = vld1q_f32(&src[72]) ;
        float32x4_t r019 = vld1q_f32(&src[76]) ;
        float32x4_t r020 = vld1q_f32(&src[80]) ;
        float32x4_t r021 = vld1q_f32(&src[84]) ;
        float32x4_t r022 = vld1q_f32(&src[88]) ;
        float32x4_t r023 = vld1q_f32(&src[92]) ;
        float32x4_t r024 = vld1q_f32(&src[96]) ;
        float32x4_t r025 = vld1q_f32(&src[100]) ;
        float32x4_t r026 = vld1q_f32(&src[104]) ;
        float32x4_t r027 = vld1q_f32(&src[108]) ;
        float32x4_t r028 = vld1q_f32(&src[112]) ;
        float32x4_t r029 = vld1q_f32(&src[116]) ;
        float32x4_t r030 = vld1q_f32(&src[120]) ;
        float32x4_t r031 = vld1q_f32(&src[124]) ;
        
        r000 = vaddq_f32(r000, r016) ;
        r001 = vaddq_f32(r001, r017) ;
        r002 = vaddq_f32(r002, r018) ;
        r003 = vaddq_f32(r003, r019) ;
        r004 = vaddq_f32(r004, r020) ;
        r005 = vaddq_f32(r005, r021) ;
        r006 = vaddq_f32(r006, r022) ;
        r007 = vaddq_f32(r007, r023) ;
        r008 = vaddq_f32(r008, r024) ;
        r009 = vaddq_f32(r009, r025) ;
        r010 = vaddq_f32(r010, r026) ;
        r011 = vaddq_f32(r011, r027) ;
        r012 = vaddq_f32(r012, r028) ;
        r013 = vaddq_f32(r013, r029) ;
        r014 = vaddq_f32(r014, r030) ;
        r015 = vaddq_f32(r015, r031) ;
        
        r000 = vaddq_f32(r000, r008) ;
        r001 = vaddq_f32(r001, r009) ;
        r002 = vaddq_f32(r002, r010) ;
        r003 = vaddq_f32(r003, r011) ;
        r004 = vaddq_f32(r004, r012) ;
        r005 = vaddq_f32(r005, r013) ;
        r006 = vaddq_f32(r006, r014) ;
        r007 = vaddq_f32(r007, r015) ;
        
        r000 = vaddq_f32(r000, r004) ;
        r001 = vaddq_f32(r001, r005) ;
        r002 = vaddq_f32(r002, r006) ;
        r003 = vaddq_f32(r003, r007) ;
        
        r000 = vaddq_f32(r000, r002) ;
        r001 = vaddq_f32(r001, r003) ;
        
        r000 = vaddq_f32(r000, r001) ;

        
        initial += vgetq_lane_f32(r000, 0) + vgetq_lane_f32(r000, 1) + vgetq_lane_f32(r000, 2) + vgetq_lane_f32(r000, 3) ;
        
        
        len -= 32 * 4 ;
        src += 32 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 16 * 4 ) {
        float32x4_t r000 = vld1q_f32(&src[0]) ;
        float32x4_t r001 = vld1q_f32(&src[4]) ;
        float32x4_t r002 = vld1q_f32(&src[8]) ;
        float32x4_t r003 = vld1q_f32(&src[12]) ;
        float32x4_t r004 = vld1q_f32(&src[16]) ;
        float32x4_t r005 = vld1q_f32(&src[20]) ;
        float32x4_t r006 = vld1q_f32(&src[24]) ;
        float32x4_t r007 = vld1q_f32(&src[28]) ;
        float32x4_t r008 = vld1q_f32(&src[32]) ;
        float32x4_t r009 = vld1q_f32(&src[36]) ;
        float32x4_t r010 = vld1q_f32(&src[40]) ;
        float32x4_t r011 = vld1q_f32(&src[44]) ;
        float32x4_t r012 = vld1q_f32(&src[48]) ;
        float32x4_t r013 = vld1q_f32(&src[52]) ;
        float32x4_t r014 = vld1q_f32(&src[56]) ;
        float32x4_t r015 = vld1q_f32(&src[60]) ;
        
        r000 = vaddq_f32(r000, r008) ;
        r001 = vaddq_f32(r001, r009) ;
        r002 = vaddq_f32(r002, r010) ;
        r003 = vaddq_f32(r003, r011) ;
        r004 = vaddq_f32(r004, r012) ;
        r005 = vaddq_f32(r005, r013) ;
        r006 = vaddq_f32(r006, r014) ;
        r007 = vaddq_f32(r007, r015) ;
        
        r000 = vaddq_f32(r000, r004) ;
        r001 = vaddq_f32(r001, r005) ;
        r002 = vaddq_f32(r002, r006) ;
        r003 = vaddq_f32(r003, r007) ;
        
        r000 = vaddq_f32(r000, r002) ;
        r001 = vaddq_f32(r001, r003) ;
        
        r000 = vaddq_f32(r000, r001) ;

        
        initial += vgetq_lane_f32(r000, 0) + vgetq_lane_f32(r000, 1) + vgetq_lane_f32(r000, 2) + vgetq_lane_f32(r000, 3) ;
        
        
        len -= 16 * 4 ;
        src += 16 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 8 * 4 ) {
        float32x4_t r000 = vld1q_f32(&src[0]) ;
        float32x4_t r001 = vld1q_f32(&src[4]) ;
        float32x4_t r002 = vld1q_f32(&src[8]) ;
        float32x4_t r003 = vld1q_f32(&src[12]) ;
        float32x4_t r004 = vld1q_f32(&src[16]) ;
        float32x4_t r005 = vld1q_f32(&src[20]) ;
        float32x4_t r006 = vld1q_f32(&src[24]) ;
        float32x4_t r007 = vld1q_f32(&src[28]) ;
        
        r000 = vaddq_f32(r000, r004) ;
        r001 = vaddq_f32(r001, r005) ;
        r002 = vaddq_f32(r002, r006) ;
        r003 = vaddq_f32(r003, r007) ;
        
        r000 = vaddq_f32(r000, r002) ;
        r001 = vaddq_f32(r001, r003) ;
        
        r000 = vaddq_f32(r000, r001) ;

        
        initial += vgetq_lane_f32(r000, 0) + vgetq_lane_f32(r000, 1) + vgetq_lane_f32(r000, 2) + vgetq_lane_f32(r000, 3) ;
        
        
        len -= 8 * 4 ;
        src += 8 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 4 * 4 ) {
        float32x4_t r000 = vld1q_f32(&src[0]) ;
        float32x4_t r001 = vld1q_f32(&src[4]) ;
        float32x4_t r002 = vld1q_f32(&src[8]) ;
        float32x4_t r003 = vld1q_f32(&src[12]) ;
        
        r000 = vaddq_f32(r000, r002) ;
        r001 = vaddq_f32(r001, r003) ;
        
        r000 = vaddq_f32(r000, r001) ;

        
        initial += vgetq_lane_f32(r000, 0) + vgetq_lane_f32(r000, 1) + vgetq_lane_f32(r000, 2) + vgetq_lane_f32(r000, 3) ;
        
        
        len -= 4 * 4 ;
        src += 4 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 2 * 4 ) {
        float32x4_t r000 = vld1q_f32(&src[0]) ;
        float32x4_t r001 = vld1q_f32(&src[4]) ;
        
        r000 = vaddq_f32(r000, r001) ;

        
        initial += vgetq_lane_f32(r000, 0) + vgetq_lane_f32(r000, 1) + vgetq_lane_f32(r000, 2) + vgetq_lane_f32(r000, 3) ;
        
        
        len -= 2 * 4 ;
        src += 2 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 1 * 4 ) {
        float32x4_t r000 = vld1q_f32(&src[0]) ;

        
        initial += vgetq_lane_f32(r000, 0) + vgetq_lane_f32(r000, 1) + vgetq_lane_f32(r000, 2) + vgetq_lane_f32(r000, 3) ;
        
        
        len -= 1 * 4 ;
        src += 1 * 4  ;
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