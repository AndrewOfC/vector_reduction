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
#if defined(__ARM_FEATURE_SVE)
#include <arm_sve.h>
#else
#error "SVE not supported or not enabled"
#endif

int32_t sve_reduce_int32(const int32_t *src, size_t len, int32_t initial /* = 0 */)
{    int32_t final[32] ;
    svbool_t pg = svptrue_b64();
    uint64_t lanes = svcntd();
    /*
     * 
     */
    while( len >= 32 * lanes ) {
        svint32_t r000 = svld1_s32(pg, &src[0*lanes]) ;
        svint32_t r001 = svld1_s32(pg, &src[1*lanes]) ;
        svint32_t r002 = svld1_s32(pg, &src[2*lanes]) ;
        svint32_t r003 = svld1_s32(pg, &src[3*lanes]) ;
        svint32_t r004 = svld1_s32(pg, &src[4*lanes]) ;
        svint32_t r005 = svld1_s32(pg, &src[5*lanes]) ;
        svint32_t r006 = svld1_s32(pg, &src[6*lanes]) ;
        svint32_t r007 = svld1_s32(pg, &src[7*lanes]) ;
        svint32_t r008 = svld1_s32(pg, &src[8*lanes]) ;
        svint32_t r009 = svld1_s32(pg, &src[9*lanes]) ;
        svint32_t r010 = svld1_s32(pg, &src[10*lanes]) ;
        svint32_t r011 = svld1_s32(pg, &src[11*lanes]) ;
        svint32_t r012 = svld1_s32(pg, &src[12*lanes]) ;
        svint32_t r013 = svld1_s32(pg, &src[13*lanes]) ;
        svint32_t r014 = svld1_s32(pg, &src[14*lanes]) ;
        svint32_t r015 = svld1_s32(pg, &src[15*lanes]) ;
        svint32_t r016 = svld1_s32(pg, &src[16*lanes]) ;
        svint32_t r017 = svld1_s32(pg, &src[17*lanes]) ;
        svint32_t r018 = svld1_s32(pg, &src[18*lanes]) ;
        svint32_t r019 = svld1_s32(pg, &src[19*lanes]) ;
        svint32_t r020 = svld1_s32(pg, &src[20*lanes]) ;
        svint32_t r021 = svld1_s32(pg, &src[21*lanes]) ;
        svint32_t r022 = svld1_s32(pg, &src[22*lanes]) ;
        svint32_t r023 = svld1_s32(pg, &src[23*lanes]) ;
        svint32_t r024 = svld1_s32(pg, &src[24*lanes]) ;
        svint32_t r025 = svld1_s32(pg, &src[25*lanes]) ;
        svint32_t r026 = svld1_s32(pg, &src[26*lanes]) ;
        svint32_t r027 = svld1_s32(pg, &src[27*lanes]) ;
        svint32_t r028 = svld1_s32(pg, &src[28*lanes]) ;
        svint32_t r029 = svld1_s32(pg, &src[29*lanes]) ;
        svint32_t r030 = svld1_s32(pg, &src[30*lanes]) ;
        svint32_t r031 = svld1_s32(pg, &src[31*lanes]) ;
        
        r000 = svadd_s32_x(pg, r000, r016) ;
        r001 = svadd_s32_x(pg, r001, r017) ;
        r002 = svadd_s32_x(pg, r002, r018) ;
        r003 = svadd_s32_x(pg, r003, r019) ;
        r004 = svadd_s32_x(pg, r004, r020) ;
        r005 = svadd_s32_x(pg, r005, r021) ;
        r006 = svadd_s32_x(pg, r006, r022) ;
        r007 = svadd_s32_x(pg, r007, r023) ;
        r008 = svadd_s32_x(pg, r008, r024) ;
        r009 = svadd_s32_x(pg, r009, r025) ;
        r010 = svadd_s32_x(pg, r010, r026) ;
        r011 = svadd_s32_x(pg, r011, r027) ;
        r012 = svadd_s32_x(pg, r012, r028) ;
        r013 = svadd_s32_x(pg, r013, r029) ;
        r014 = svadd_s32_x(pg, r014, r030) ;
        r015 = svadd_s32_x(pg, r015, r031) ;
        
        r000 = svadd_s32_x(pg, r000, r008) ;
        r001 = svadd_s32_x(pg, r001, r009) ;
        r002 = svadd_s32_x(pg, r002, r010) ;
        r003 = svadd_s32_x(pg, r003, r011) ;
        r004 = svadd_s32_x(pg, r004, r012) ;
        r005 = svadd_s32_x(pg, r005, r013) ;
        r006 = svadd_s32_x(pg, r006, r014) ;
        r007 = svadd_s32_x(pg, r007, r015) ;
        
        r000 = svadd_s32_x(pg, r000, r004) ;
        r001 = svadd_s32_x(pg, r001, r005) ;
        r002 = svadd_s32_x(pg, r002, r006) ;
        r003 = svadd_s32_x(pg, r003, r007) ;
        
        r000 = svadd_s32_x(pg, r000, r002) ;
        r001 = svadd_s32_x(pg, r001, r003) ;
        
        r000 = svadd_s32_x(pg, r000, r001) ;

        
        
        svst1_s32(pg, &final[0], r000) ;
        for (uint64_t i = 0; i < lanes; i++)
            initial += final[i] ;
        
        len -= 32 * lanes ;
        src += 32 * lanes  ;
    } // while
    /*
     * 
     */
    while( len >= 16 * lanes ) {
        svint32_t r000 = svld1_s32(pg, &src[0*lanes]) ;
        svint32_t r001 = svld1_s32(pg, &src[1*lanes]) ;
        svint32_t r002 = svld1_s32(pg, &src[2*lanes]) ;
        svint32_t r003 = svld1_s32(pg, &src[3*lanes]) ;
        svint32_t r004 = svld1_s32(pg, &src[4*lanes]) ;
        svint32_t r005 = svld1_s32(pg, &src[5*lanes]) ;
        svint32_t r006 = svld1_s32(pg, &src[6*lanes]) ;
        svint32_t r007 = svld1_s32(pg, &src[7*lanes]) ;
        svint32_t r008 = svld1_s32(pg, &src[8*lanes]) ;
        svint32_t r009 = svld1_s32(pg, &src[9*lanes]) ;
        svint32_t r010 = svld1_s32(pg, &src[10*lanes]) ;
        svint32_t r011 = svld1_s32(pg, &src[11*lanes]) ;
        svint32_t r012 = svld1_s32(pg, &src[12*lanes]) ;
        svint32_t r013 = svld1_s32(pg, &src[13*lanes]) ;
        svint32_t r014 = svld1_s32(pg, &src[14*lanes]) ;
        svint32_t r015 = svld1_s32(pg, &src[15*lanes]) ;
        
        r000 = svadd_s32_x(pg, r000, r008) ;
        r001 = svadd_s32_x(pg, r001, r009) ;
        r002 = svadd_s32_x(pg, r002, r010) ;
        r003 = svadd_s32_x(pg, r003, r011) ;
        r004 = svadd_s32_x(pg, r004, r012) ;
        r005 = svadd_s32_x(pg, r005, r013) ;
        r006 = svadd_s32_x(pg, r006, r014) ;
        r007 = svadd_s32_x(pg, r007, r015) ;
        
        r000 = svadd_s32_x(pg, r000, r004) ;
        r001 = svadd_s32_x(pg, r001, r005) ;
        r002 = svadd_s32_x(pg, r002, r006) ;
        r003 = svadd_s32_x(pg, r003, r007) ;
        
        r000 = svadd_s32_x(pg, r000, r002) ;
        r001 = svadd_s32_x(pg, r001, r003) ;
        
        r000 = svadd_s32_x(pg, r000, r001) ;

        
        
        svst1_s32(pg, &final[0], r000) ;
        for (uint64_t i = 0; i < lanes; i++)
            initial += final[i] ;
        
        len -= 16 * lanes ;
        src += 16 * lanes  ;
    } // while
    /*
     * 
     */
    while( len >= 8 * lanes ) {
        svint32_t r000 = svld1_s32(pg, &src[0*lanes]) ;
        svint32_t r001 = svld1_s32(pg, &src[1*lanes]) ;
        svint32_t r002 = svld1_s32(pg, &src[2*lanes]) ;
        svint32_t r003 = svld1_s32(pg, &src[3*lanes]) ;
        svint32_t r004 = svld1_s32(pg, &src[4*lanes]) ;
        svint32_t r005 = svld1_s32(pg, &src[5*lanes]) ;
        svint32_t r006 = svld1_s32(pg, &src[6*lanes]) ;
        svint32_t r007 = svld1_s32(pg, &src[7*lanes]) ;
        
        r000 = svadd_s32_x(pg, r000, r004) ;
        r001 = svadd_s32_x(pg, r001, r005) ;
        r002 = svadd_s32_x(pg, r002, r006) ;
        r003 = svadd_s32_x(pg, r003, r007) ;
        
        r000 = svadd_s32_x(pg, r000, r002) ;
        r001 = svadd_s32_x(pg, r001, r003) ;
        
        r000 = svadd_s32_x(pg, r000, r001) ;

        
        
        svst1_s32(pg, &final[0], r000) ;
        for (uint64_t i = 0; i < lanes; i++)
            initial += final[i] ;
        
        len -= 8 * lanes ;
        src += 8 * lanes  ;
    } // while
    /*
     * 
     */
    while( len >= 4 * lanes ) {
        svint32_t r000 = svld1_s32(pg, &src[0*lanes]) ;
        svint32_t r001 = svld1_s32(pg, &src[1*lanes]) ;
        svint32_t r002 = svld1_s32(pg, &src[2*lanes]) ;
        svint32_t r003 = svld1_s32(pg, &src[3*lanes]) ;
        
        r000 = svadd_s32_x(pg, r000, r002) ;
        r001 = svadd_s32_x(pg, r001, r003) ;
        
        r000 = svadd_s32_x(pg, r000, r001) ;

        
        
        svst1_s32(pg, &final[0], r000) ;
        for (uint64_t i = 0; i < lanes; i++)
            initial += final[i] ;
        
        len -= 4 * lanes ;
        src += 4 * lanes  ;
    } // while
    /*
     * 
     */
    while( len >= 2 * lanes ) {
        svint32_t r000 = svld1_s32(pg, &src[0*lanes]) ;
        svint32_t r001 = svld1_s32(pg, &src[1*lanes]) ;
        
        r000 = svadd_s32_x(pg, r000, r001) ;

        
        
        svst1_s32(pg, &final[0], r000) ;
        for (uint64_t i = 0; i < lanes; i++)
            initial += final[i] ;
        
        len -= 2 * lanes ;
        src += 2 * lanes  ;
    } // while
    /*
     * 
     */
    while( len >= 1 * lanes ) {
        svint32_t r000 = svld1_s32(pg, &src[0*lanes]) ;

        
        
        svst1_s32(pg, &final[0], r000) ;
        for (uint64_t i = 0; i < lanes; i++)
            initial += final[i] ;
        
        len -= 1 * lanes ;
        src += 1 * lanes  ;
    } // while

    // clean up on aisle 3
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }

    return initial ;
}