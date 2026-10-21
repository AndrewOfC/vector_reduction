
#include <stddef.h>
#include "vector_reduce.h"

#if defined(__AVX512F__)
#include <immintrin.h>
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#else
#error "Unsupported CPU"
#endif

float vector_reduce_float(const float *src, size_t len, float initial /* = 0 */)
{
    /*
     * 
     */
    while( len >= 32 * 16 ) {
        __m512 r000 = _mm512_loadu_ps(src+0);
        __m512 r001 = _mm512_loadu_ps(src+16);
        __m512 r002 = _mm512_loadu_ps(src+32);
        __m512 r003 = _mm512_loadu_ps(src+48);
        __m512 r004 = _mm512_loadu_ps(src+64);
        __m512 r005 = _mm512_loadu_ps(src+80);
        __m512 r006 = _mm512_loadu_ps(src+96);
        __m512 r007 = _mm512_loadu_ps(src+112);
        __m512 r008 = _mm512_loadu_ps(src+128);
        __m512 r009 = _mm512_loadu_ps(src+144);
        __m512 r010 = _mm512_loadu_ps(src+160);
        __m512 r011 = _mm512_loadu_ps(src+176);
        __m512 r012 = _mm512_loadu_ps(src+192);
        __m512 r013 = _mm512_loadu_ps(src+208);
        __m512 r014 = _mm512_loadu_ps(src+224);
        __m512 r015 = _mm512_loadu_ps(src+240);
        __m512 r016 = _mm512_loadu_ps(src+256);
        __m512 r017 = _mm512_loadu_ps(src+272);
        __m512 r018 = _mm512_loadu_ps(src+288);
        __m512 r019 = _mm512_loadu_ps(src+304);
        __m512 r020 = _mm512_loadu_ps(src+320);
        __m512 r021 = _mm512_loadu_ps(src+336);
        __m512 r022 = _mm512_loadu_ps(src+352);
        __m512 r023 = _mm512_loadu_ps(src+368);
        __m512 r024 = _mm512_loadu_ps(src+384);
        __m512 r025 = _mm512_loadu_ps(src+400);
        __m512 r026 = _mm512_loadu_ps(src+416);
        __m512 r027 = _mm512_loadu_ps(src+432);
        __m512 r028 = _mm512_loadu_ps(src+448);
        __m512 r029 = _mm512_loadu_ps(src+464);
        __m512 r030 = _mm512_loadu_ps(src+480);
        __m512 r031 = _mm512_loadu_ps(src+496);
        
        r000 = _mm512_add_ps(r000, r016);
        r001 = _mm512_add_ps(r001, r017);
        r002 = _mm512_add_ps(r002, r018);
        r003 = _mm512_add_ps(r003, r019);
        r004 = _mm512_add_ps(r004, r020);
        r005 = _mm512_add_ps(r005, r021);
        r006 = _mm512_add_ps(r006, r022);
        r007 = _mm512_add_ps(r007, r023);
        r008 = _mm512_add_ps(r008, r024);
        r009 = _mm512_add_ps(r009, r025);
        r010 = _mm512_add_ps(r010, r026);
        r011 = _mm512_add_ps(r011, r027);
        r012 = _mm512_add_ps(r012, r028);
        r013 = _mm512_add_ps(r013, r029);
        r014 = _mm512_add_ps(r014, r030);
        r015 = _mm512_add_ps(r015, r031);
        
        r000 = _mm512_add_ps(r000, r008);
        r001 = _mm512_add_ps(r001, r009);
        r002 = _mm512_add_ps(r002, r010);
        r003 = _mm512_add_ps(r003, r011);
        r004 = _mm512_add_ps(r004, r012);
        r005 = _mm512_add_ps(r005, r013);
        r006 = _mm512_add_ps(r006, r014);
        r007 = _mm512_add_ps(r007, r015);
        
        r000 = _mm512_add_ps(r000, r004);
        r001 = _mm512_add_ps(r001, r005);
        r002 = _mm512_add_ps(r002, r006);
        r003 = _mm512_add_ps(r003, r007);
        
        r000 = _mm512_add_ps(r000, r002);
        r001 = _mm512_add_ps(r001, r003);
        
        r000 = _mm512_add_ps(r000, r001);

        initial += _mm512_reduce_add_ps(r000) ;
        len -= 32 * 16 ;
        src += 32 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 16 * 16 ) {
        __m512 r000 = _mm512_loadu_ps(src+0);
        __m512 r001 = _mm512_loadu_ps(src+16);
        __m512 r002 = _mm512_loadu_ps(src+32);
        __m512 r003 = _mm512_loadu_ps(src+48);
        __m512 r004 = _mm512_loadu_ps(src+64);
        __m512 r005 = _mm512_loadu_ps(src+80);
        __m512 r006 = _mm512_loadu_ps(src+96);
        __m512 r007 = _mm512_loadu_ps(src+112);
        __m512 r008 = _mm512_loadu_ps(src+128);
        __m512 r009 = _mm512_loadu_ps(src+144);
        __m512 r010 = _mm512_loadu_ps(src+160);
        __m512 r011 = _mm512_loadu_ps(src+176);
        __m512 r012 = _mm512_loadu_ps(src+192);
        __m512 r013 = _mm512_loadu_ps(src+208);
        __m512 r014 = _mm512_loadu_ps(src+224);
        __m512 r015 = _mm512_loadu_ps(src+240);
        
        r000 = _mm512_add_ps(r000, r008);
        r001 = _mm512_add_ps(r001, r009);
        r002 = _mm512_add_ps(r002, r010);
        r003 = _mm512_add_ps(r003, r011);
        r004 = _mm512_add_ps(r004, r012);
        r005 = _mm512_add_ps(r005, r013);
        r006 = _mm512_add_ps(r006, r014);
        r007 = _mm512_add_ps(r007, r015);
        
        r000 = _mm512_add_ps(r000, r004);
        r001 = _mm512_add_ps(r001, r005);
        r002 = _mm512_add_ps(r002, r006);
        r003 = _mm512_add_ps(r003, r007);
        
        r000 = _mm512_add_ps(r000, r002);
        r001 = _mm512_add_ps(r001, r003);
        
        r000 = _mm512_add_ps(r000, r001);

        initial += _mm512_reduce_add_ps(r000) ;
        len -= 16 * 16 ;
        src += 16 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 8 * 16 ) {
        __m512 r000 = _mm512_loadu_ps(src+0);
        __m512 r001 = _mm512_loadu_ps(src+16);
        __m512 r002 = _mm512_loadu_ps(src+32);
        __m512 r003 = _mm512_loadu_ps(src+48);
        __m512 r004 = _mm512_loadu_ps(src+64);
        __m512 r005 = _mm512_loadu_ps(src+80);
        __m512 r006 = _mm512_loadu_ps(src+96);
        __m512 r007 = _mm512_loadu_ps(src+112);
        
        r000 = _mm512_add_ps(r000, r004);
        r001 = _mm512_add_ps(r001, r005);
        r002 = _mm512_add_ps(r002, r006);
        r003 = _mm512_add_ps(r003, r007);
        
        r000 = _mm512_add_ps(r000, r002);
        r001 = _mm512_add_ps(r001, r003);
        
        r000 = _mm512_add_ps(r000, r001);

        initial += _mm512_reduce_add_ps(r000) ;
        len -= 8 * 16 ;
        src += 8 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 4 * 16 ) {
        __m512 r000 = _mm512_loadu_ps(src+0);
        __m512 r001 = _mm512_loadu_ps(src+16);
        __m512 r002 = _mm512_loadu_ps(src+32);
        __m512 r003 = _mm512_loadu_ps(src+48);
        
        r000 = _mm512_add_ps(r000, r002);
        r001 = _mm512_add_ps(r001, r003);
        
        r000 = _mm512_add_ps(r000, r001);

        initial += _mm512_reduce_add_ps(r000) ;
        len -= 4 * 16 ;
        src += 4 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 2 * 16 ) {
        __m512 r000 = _mm512_loadu_ps(src+0);
        __m512 r001 = _mm512_loadu_ps(src+16);
        
        r000 = _mm512_add_ps(r000, r001);

        initial += _mm512_reduce_add_ps(r000) ;
        len -= 2 * 16 ;
        src += 2 * 16  ;
    } // while
    /*
     * 
     */
    while( len >= 1 * 16 ) {
        __m512 r000 = _mm512_loadu_ps(src+0);

        initial += _mm512_reduce_add_ps(r000) ;
        len -= 1 * 16 ;
        src += 1 * 16  ;
    } // while

    // clean up on aisle 3
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }

    return initial ;   
}