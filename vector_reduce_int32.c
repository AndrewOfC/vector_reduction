#include <stddef.h>
#include "vector_reduce.h"

#if defined(__AVX512F__)
#include <immintrin.h>
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#else
#error "Unsupported CPU"
#endif

int32_t vector_reduce_int32(const int32_t *src, size_t len, int32_t initial /* = 0 */)
{
#if defined(__AVX512F__)
    /*
     * 
     */
    while( len >= 32 * 16 ) {
        __m512i r000 = _mm512_loadu_epi32(src+0);
        __m512i r001 = _mm512_loadu_epi32(src+16);
        __m512i r002 = _mm512_loadu_epi32(src+32);
        __m512i r003 = _mm512_loadu_epi32(src+48);
        __m512i r004 = _mm512_loadu_epi32(src+64);
        __m512i r005 = _mm512_loadu_epi32(src+80);
        __m512i r006 = _mm512_loadu_epi32(src+96);
        __m512i r007 = _mm512_loadu_epi32(src+112);
        __m512i r008 = _mm512_loadu_epi32(src+128);
        __m512i r009 = _mm512_loadu_epi32(src+144);
        __m512i r010 = _mm512_loadu_epi32(src+160);
        __m512i r011 = _mm512_loadu_epi32(src+176);
        __m512i r012 = _mm512_loadu_epi32(src+192);
        __m512i r013 = _mm512_loadu_epi32(src+208);
        __m512i r014 = _mm512_loadu_epi32(src+224);
        __m512i r015 = _mm512_loadu_epi32(src+240);
        __m512i r016 = _mm512_loadu_epi32(src+256);
        __m512i r017 = _mm512_loadu_epi32(src+272);
        __m512i r018 = _mm512_loadu_epi32(src+288);
        __m512i r019 = _mm512_loadu_epi32(src+304);
        __m512i r020 = _mm512_loadu_epi32(src+320);
        __m512i r021 = _mm512_loadu_epi32(src+336);
        __m512i r022 = _mm512_loadu_epi32(src+352);
        __m512i r023 = _mm512_loadu_epi32(src+368);
        __m512i r024 = _mm512_loadu_epi32(src+384);
        __m512i r025 = _mm512_loadu_epi32(src+400);
        __m512i r026 = _mm512_loadu_epi32(src+416);
        __m512i r027 = _mm512_loadu_epi32(src+432);
        __m512i r028 = _mm512_loadu_epi32(src+448);
        __m512i r029 = _mm512_loadu_epi32(src+464);
        __m512i r030 = _mm512_loadu_epi32(src+480);
        __m512i r031 = _mm512_loadu_epi32(src+496);
        
        r000 = _mm512_add_epi32(r000, r016);
        r001 = _mm512_add_epi32(r001, r017);
        r002 = _mm512_add_epi32(r002, r018);
        r003 = _mm512_add_epi32(r003, r019);
        r004 = _mm512_add_epi32(r004, r020);
        r005 = _mm512_add_epi32(r005, r021);
        r006 = _mm512_add_epi32(r006, r022);
        r007 = _mm512_add_epi32(r007, r023);
        r008 = _mm512_add_epi32(r008, r024);
        r009 = _mm512_add_epi32(r009, r025);
        r010 = _mm512_add_epi32(r010, r026);
        r011 = _mm512_add_epi32(r011, r027);
        r012 = _mm512_add_epi32(r012, r028);
        r013 = _mm512_add_epi32(r013, r029);
        r014 = _mm512_add_epi32(r014, r030);
        r015 = _mm512_add_epi32(r015, r031);
        
        r000 = _mm512_add_epi32(r000, r008);
        r001 = _mm512_add_epi32(r001, r009);
        r002 = _mm512_add_epi32(r002, r010);
        r003 = _mm512_add_epi32(r003, r011);
        r004 = _mm512_add_epi32(r004, r012);
        r005 = _mm512_add_epi32(r005, r013);
        r006 = _mm512_add_epi32(r006, r014);
        r007 = _mm512_add_epi32(r007, r015);
        
        r000 = _mm512_add_epi32(r000, r004);
        r001 = _mm512_add_epi32(r001, r005);
        r002 = _mm512_add_epi32(r002, r006);
        r003 = _mm512_add_epi32(r003, r007);
        
        r000 = _mm512_add_epi32(r000, r002);
        r001 = _mm512_add_epi32(r001, r003);
        
        r000 = _mm512_add_epi32(r000, r001);

        initial += _mm512_reduce_add_epi32(r000) ;
        

        len -= 32 * 16 ;
        src += 32 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 16 * 16 ) {
        __m512i r000 = _mm512_loadu_epi32(src+0);
        __m512i r001 = _mm512_loadu_epi32(src+16);
        __m512i r002 = _mm512_loadu_epi32(src+32);
        __m512i r003 = _mm512_loadu_epi32(src+48);
        __m512i r004 = _mm512_loadu_epi32(src+64);
        __m512i r005 = _mm512_loadu_epi32(src+80);
        __m512i r006 = _mm512_loadu_epi32(src+96);
        __m512i r007 = _mm512_loadu_epi32(src+112);
        __m512i r008 = _mm512_loadu_epi32(src+128);
        __m512i r009 = _mm512_loadu_epi32(src+144);
        __m512i r010 = _mm512_loadu_epi32(src+160);
        __m512i r011 = _mm512_loadu_epi32(src+176);
        __m512i r012 = _mm512_loadu_epi32(src+192);
        __m512i r013 = _mm512_loadu_epi32(src+208);
        __m512i r014 = _mm512_loadu_epi32(src+224);
        __m512i r015 = _mm512_loadu_epi32(src+240);
        
        r000 = _mm512_add_epi32(r000, r008);
        r001 = _mm512_add_epi32(r001, r009);
        r002 = _mm512_add_epi32(r002, r010);
        r003 = _mm512_add_epi32(r003, r011);
        r004 = _mm512_add_epi32(r004, r012);
        r005 = _mm512_add_epi32(r005, r013);
        r006 = _mm512_add_epi32(r006, r014);
        r007 = _mm512_add_epi32(r007, r015);
        
        r000 = _mm512_add_epi32(r000, r004);
        r001 = _mm512_add_epi32(r001, r005);
        r002 = _mm512_add_epi32(r002, r006);
        r003 = _mm512_add_epi32(r003, r007);
        
        r000 = _mm512_add_epi32(r000, r002);
        r001 = _mm512_add_epi32(r001, r003);
        
        r000 = _mm512_add_epi32(r000, r001);

        initial += _mm512_reduce_add_epi32(r000) ;
        

        len -= 16 * 16 ;
        src += 16 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 8 * 16 ) {
        __m512i r000 = _mm512_loadu_epi32(src+0);
        __m512i r001 = _mm512_loadu_epi32(src+16);
        __m512i r002 = _mm512_loadu_epi32(src+32);
        __m512i r003 = _mm512_loadu_epi32(src+48);
        __m512i r004 = _mm512_loadu_epi32(src+64);
        __m512i r005 = _mm512_loadu_epi32(src+80);
        __m512i r006 = _mm512_loadu_epi32(src+96);
        __m512i r007 = _mm512_loadu_epi32(src+112);
        
        r000 = _mm512_add_epi32(r000, r004);
        r001 = _mm512_add_epi32(r001, r005);
        r002 = _mm512_add_epi32(r002, r006);
        r003 = _mm512_add_epi32(r003, r007);
        
        r000 = _mm512_add_epi32(r000, r002);
        r001 = _mm512_add_epi32(r001, r003);
        
        r000 = _mm512_add_epi32(r000, r001);

        initial += _mm512_reduce_add_epi32(r000) ;
        

        len -= 8 * 16 ;
        src += 8 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 4 * 16 ) {
        __m512i r000 = _mm512_loadu_epi32(src+0);
        __m512i r001 = _mm512_loadu_epi32(src+16);
        __m512i r002 = _mm512_loadu_epi32(src+32);
        __m512i r003 = _mm512_loadu_epi32(src+48);
        
        r000 = _mm512_add_epi32(r000, r002);
        r001 = _mm512_add_epi32(r001, r003);
        
        r000 = _mm512_add_epi32(r000, r001);

        initial += _mm512_reduce_add_epi32(r000) ;
        

        len -= 4 * 16 ;
        src += 4 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 2 * 16 ) {
        __m512i r000 = _mm512_loadu_epi32(src+0);
        __m512i r001 = _mm512_loadu_epi32(src+16);
        
        r000 = _mm512_add_epi32(r000, r001);

        initial += _mm512_reduce_add_epi32(r000) ;
        

        len -= 2 * 16 ;
        src += 2 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 1 * 16 ) {
        __m512i r000 = _mm512_loadu_epi32(src+0);

        initial += _mm512_reduce_add_epi32(r000) ;
        

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
        int32x4_t r000 = vld1q_s32(src+0);
        int32x4_t r001 = vld1q_s32(src+4);
        int32x4_t r002 = vld1q_s32(src+8);
        int32x4_t r003 = vld1q_s32(src+12);
        int32x4_t r004 = vld1q_s32(src+16);
        int32x4_t r005 = vld1q_s32(src+20);
        int32x4_t r006 = vld1q_s32(src+24);
        int32x4_t r007 = vld1q_s32(src+28);
        int32x4_t r008 = vld1q_s32(src+32);
        int32x4_t r009 = vld1q_s32(src+36);
        int32x4_t r010 = vld1q_s32(src+40);
        int32x4_t r011 = vld1q_s32(src+44);
        int32x4_t r012 = vld1q_s32(src+48);
        int32x4_t r013 = vld1q_s32(src+52);
        int32x4_t r014 = vld1q_s32(src+56);
        int32x4_t r015 = vld1q_s32(src+60);
        int32x4_t r016 = vld1q_s32(src+64);
        int32x4_t r017 = vld1q_s32(src+68);
        int32x4_t r018 = vld1q_s32(src+72);
        int32x4_t r019 = vld1q_s32(src+76);
        int32x4_t r020 = vld1q_s32(src+80);
        int32x4_t r021 = vld1q_s32(src+84);
        int32x4_t r022 = vld1q_s32(src+88);
        int32x4_t r023 = vld1q_s32(src+92);
        int32x4_t r024 = vld1q_s32(src+96);
        int32x4_t r025 = vld1q_s32(src+100);
        int32x4_t r026 = vld1q_s32(src+104);
        int32x4_t r027 = vld1q_s32(src+108);
        int32x4_t r028 = vld1q_s32(src+112);
        int32x4_t r029 = vld1q_s32(src+116);
        int32x4_t r030 = vld1q_s32(src+120);
        int32x4_t r031 = vld1q_s32(src+124);
        
        r000 = vaddq_s32(r000, r016);
        r001 = vaddq_s32(r001, r017);
        r002 = vaddq_s32(r002, r018);
        r003 = vaddq_s32(r003, r019);
        r004 = vaddq_s32(r004, r020);
        r005 = vaddq_s32(r005, r021);
        r006 = vaddq_s32(r006, r022);
        r007 = vaddq_s32(r007, r023);
        r008 = vaddq_s32(r008, r024);
        r009 = vaddq_s32(r009, r025);
        r010 = vaddq_s32(r010, r026);
        r011 = vaddq_s32(r011, r027);
        r012 = vaddq_s32(r012, r028);
        r013 = vaddq_s32(r013, r029);
        r014 = vaddq_s32(r014, r030);
        r015 = vaddq_s32(r015, r031);
        
        r000 = vaddq_s32(r000, r008);
        r001 = vaddq_s32(r001, r009);
        r002 = vaddq_s32(r002, r010);
        r003 = vaddq_s32(r003, r011);
        r004 = vaddq_s32(r004, r012);
        r005 = vaddq_s32(r005, r013);
        r006 = vaddq_s32(r006, r014);
        r007 = vaddq_s32(r007, r015);
        
        r000 = vaddq_s32(r000, r004);
        r001 = vaddq_s32(r001, r005);
        r002 = vaddq_s32(r002, r006);
        r003 = vaddq_s32(r003, r007);
        
        r000 = vaddq_s32(r000, r002);
        r001 = vaddq_s32(r001, r003);
        
        r000 = vaddq_s32(r000, r001);

        
        initial += vgetq_lane_s32(r000, 0) + vgetq_lane_s32(r000, 1) + vgetq_lane_s32(r000, 2) + vgetq_lane_s32(r000, 3) ;
        

        len -= 32 * 4 ;
        src += 32 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 16 * 4 ) {
        int32x4_t r000 = vld1q_s32(src+0);
        int32x4_t r001 = vld1q_s32(src+4);
        int32x4_t r002 = vld1q_s32(src+8);
        int32x4_t r003 = vld1q_s32(src+12);
        int32x4_t r004 = vld1q_s32(src+16);
        int32x4_t r005 = vld1q_s32(src+20);
        int32x4_t r006 = vld1q_s32(src+24);
        int32x4_t r007 = vld1q_s32(src+28);
        int32x4_t r008 = vld1q_s32(src+32);
        int32x4_t r009 = vld1q_s32(src+36);
        int32x4_t r010 = vld1q_s32(src+40);
        int32x4_t r011 = vld1q_s32(src+44);
        int32x4_t r012 = vld1q_s32(src+48);
        int32x4_t r013 = vld1q_s32(src+52);
        int32x4_t r014 = vld1q_s32(src+56);
        int32x4_t r015 = vld1q_s32(src+60);
        
        r000 = vaddq_s32(r000, r008);
        r001 = vaddq_s32(r001, r009);
        r002 = vaddq_s32(r002, r010);
        r003 = vaddq_s32(r003, r011);
        r004 = vaddq_s32(r004, r012);
        r005 = vaddq_s32(r005, r013);
        r006 = vaddq_s32(r006, r014);
        r007 = vaddq_s32(r007, r015);
        
        r000 = vaddq_s32(r000, r004);
        r001 = vaddq_s32(r001, r005);
        r002 = vaddq_s32(r002, r006);
        r003 = vaddq_s32(r003, r007);
        
        r000 = vaddq_s32(r000, r002);
        r001 = vaddq_s32(r001, r003);
        
        r000 = vaddq_s32(r000, r001);

        
        initial += vgetq_lane_s32(r000, 0) + vgetq_lane_s32(r000, 1) + vgetq_lane_s32(r000, 2) + vgetq_lane_s32(r000, 3) ;
        

        len -= 16 * 4 ;
        src += 16 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 8 * 4 ) {
        int32x4_t r000 = vld1q_s32(src+0);
        int32x4_t r001 = vld1q_s32(src+4);
        int32x4_t r002 = vld1q_s32(src+8);
        int32x4_t r003 = vld1q_s32(src+12);
        int32x4_t r004 = vld1q_s32(src+16);
        int32x4_t r005 = vld1q_s32(src+20);
        int32x4_t r006 = vld1q_s32(src+24);
        int32x4_t r007 = vld1q_s32(src+28);
        
        r000 = vaddq_s32(r000, r004);
        r001 = vaddq_s32(r001, r005);
        r002 = vaddq_s32(r002, r006);
        r003 = vaddq_s32(r003, r007);
        
        r000 = vaddq_s32(r000, r002);
        r001 = vaddq_s32(r001, r003);
        
        r000 = vaddq_s32(r000, r001);

        
        initial += vgetq_lane_s32(r000, 0) + vgetq_lane_s32(r000, 1) + vgetq_lane_s32(r000, 2) + vgetq_lane_s32(r000, 3) ;
        

        len -= 8 * 4 ;
        src += 8 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 4 * 4 ) {
        int32x4_t r000 = vld1q_s32(src+0);
        int32x4_t r001 = vld1q_s32(src+4);
        int32x4_t r002 = vld1q_s32(src+8);
        int32x4_t r003 = vld1q_s32(src+12);
        
        r000 = vaddq_s32(r000, r002);
        r001 = vaddq_s32(r001, r003);
        
        r000 = vaddq_s32(r000, r001);

        
        initial += vgetq_lane_s32(r000, 0) + vgetq_lane_s32(r000, 1) + vgetq_lane_s32(r000, 2) + vgetq_lane_s32(r000, 3) ;
        

        len -= 4 * 4 ;
        src += 4 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 2 * 4 ) {
        int32x4_t r000 = vld1q_s32(src+0);
        int32x4_t r001 = vld1q_s32(src+4);
        
        r000 = vaddq_s32(r000, r001);

        
        initial += vgetq_lane_s32(r000, 0) + vgetq_lane_s32(r000, 1) + vgetq_lane_s32(r000, 2) + vgetq_lane_s32(r000, 3) ;
        

        len -= 2 * 4 ;
        src += 2 * 4  ;
    } // while
    /*
     * 
     */
    while( len >= 1 * 4 ) {
        int32x4_t r000 = vld1q_s32(src+0);

        
        initial += vgetq_lane_s32(r000, 0) + vgetq_lane_s32(r000, 1) + vgetq_lane_s32(r000, 2) + vgetq_lane_s32(r000, 3) ;
        

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