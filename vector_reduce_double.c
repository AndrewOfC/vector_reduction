
#include <stddef.h>
#include "vector_reduce.h"

#if defined(__AVX512F__)
#include <immintrin.h>
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#else
#error "Unsupported CPU"
#endif

double vector_reduce_double(const double *src, size_t len, double initial /* = 0 */)
{
    /*
     * 
     */
    while( len >= 32 * 2 ) {
        float64x2_t r000 = vld1q_f64(src+0);
        float64x2_t r001 = vld1q_f64(src+2);
        float64x2_t r002 = vld1q_f64(src+4);
        float64x2_t r003 = vld1q_f64(src+6);
        float64x2_t r004 = vld1q_f64(src+8);
        float64x2_t r005 = vld1q_f64(src+10);
        float64x2_t r006 = vld1q_f64(src+12);
        float64x2_t r007 = vld1q_f64(src+14);
        float64x2_t r008 = vld1q_f64(src+16);
        float64x2_t r009 = vld1q_f64(src+18);
        float64x2_t r010 = vld1q_f64(src+20);
        float64x2_t r011 = vld1q_f64(src+22);
        float64x2_t r012 = vld1q_f64(src+24);
        float64x2_t r013 = vld1q_f64(src+26);
        float64x2_t r014 = vld1q_f64(src+28);
        float64x2_t r015 = vld1q_f64(src+30);
        float64x2_t r016 = vld1q_f64(src+32);
        float64x2_t r017 = vld1q_f64(src+34);
        float64x2_t r018 = vld1q_f64(src+36);
        float64x2_t r019 = vld1q_f64(src+38);
        float64x2_t r020 = vld1q_f64(src+40);
        float64x2_t r021 = vld1q_f64(src+42);
        float64x2_t r022 = vld1q_f64(src+44);
        float64x2_t r023 = vld1q_f64(src+46);
        float64x2_t r024 = vld1q_f64(src+48);
        float64x2_t r025 = vld1q_f64(src+50);
        float64x2_t r026 = vld1q_f64(src+52);
        float64x2_t r027 = vld1q_f64(src+54);
        float64x2_t r028 = vld1q_f64(src+56);
        float64x2_t r029 = vld1q_f64(src+58);
        float64x2_t r030 = vld1q_f64(src+60);
        float64x2_t r031 = vld1q_f64(src+62);
        
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
        float64x2_t r000 = vld1q_f64(src+0);
        float64x2_t r001 = vld1q_f64(src+2);
        float64x2_t r002 = vld1q_f64(src+4);
        float64x2_t r003 = vld1q_f64(src+6);
        float64x2_t r004 = vld1q_f64(src+8);
        float64x2_t r005 = vld1q_f64(src+10);
        float64x2_t r006 = vld1q_f64(src+12);
        float64x2_t r007 = vld1q_f64(src+14);
        float64x2_t r008 = vld1q_f64(src+16);
        float64x2_t r009 = vld1q_f64(src+18);
        float64x2_t r010 = vld1q_f64(src+20);
        float64x2_t r011 = vld1q_f64(src+22);
        float64x2_t r012 = vld1q_f64(src+24);
        float64x2_t r013 = vld1q_f64(src+26);
        float64x2_t r014 = vld1q_f64(src+28);
        float64x2_t r015 = vld1q_f64(src+30);
        
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
        float64x2_t r000 = vld1q_f64(src+0);
        float64x2_t r001 = vld1q_f64(src+2);
        float64x2_t r002 = vld1q_f64(src+4);
        float64x2_t r003 = vld1q_f64(src+6);
        float64x2_t r004 = vld1q_f64(src+8);
        float64x2_t r005 = vld1q_f64(src+10);
        float64x2_t r006 = vld1q_f64(src+12);
        float64x2_t r007 = vld1q_f64(src+14);
        
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
        float64x2_t r000 = vld1q_f64(src+0);
        float64x2_t r001 = vld1q_f64(src+2);
        float64x2_t r002 = vld1q_f64(src+4);
        float64x2_t r003 = vld1q_f64(src+6);
        
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
        float64x2_t r000 = vld1q_f64(src+0);
        float64x2_t r001 = vld1q_f64(src+2);
        
        r000 = vaddq_f64(r000, r001);

        
        initial += vgetq_lane_f64(r000, 0) + vgetq_lane_f64(r000, 1) ;
        

        len -= 2 * 2 ;
        src += 2 * 2  ;
    } // while
    /*
     * 
     */
    while( len >= 1 * 2 ) {
        float64x2_t r000 = vld1q_f64(src+0);

        
        initial += vgetq_lane_f64(r000, 0) + vgetq_lane_f64(r000, 1) ;
        

        len -= 1 * 2 ;
        src += 1 * 2  ;
    } // while

    // clean up on aisle 3
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }

    return initial ;   
}