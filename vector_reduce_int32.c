
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
}