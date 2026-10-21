
#include <cstdint>
#include <iostream>

#if defined(__AVX512F__)
#include <immintrin.h>
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#else
#error "Unsupported CPU"
#endif

double vector_reduce(double *src, size_t len, double initial /* = 0 */)
{
    /*
     * 
     */
    while( len >= 256 ) {
        __m512d r000 = _mm512_loadu_pd(src+0);
        __m512d r001 = _mm512_loadu_pd(src+8);
        __m512d r002 = _mm512_loadu_pd(src+16);
        __m512d r003 = _mm512_loadu_pd(src+24);
        __m512d r004 = _mm512_loadu_pd(src+32);
        __m512d r005 = _mm512_loadu_pd(src+40);
        __m512d r006 = _mm512_loadu_pd(src+48);
        __m512d r007 = _mm512_loadu_pd(src+56);
        __m512d r008 = _mm512_loadu_pd(src+64);
        __m512d r009 = _mm512_loadu_pd(src+72);
        __m512d r010 = _mm512_loadu_pd(src+80);
        __m512d r011 = _mm512_loadu_pd(src+88);
        __m512d r012 = _mm512_loadu_pd(src+96);
        __m512d r013 = _mm512_loadu_pd(src+104);
        __m512d r014 = _mm512_loadu_pd(src+112);
        __m512d r015 = _mm512_loadu_pd(src+120);
        __m512d r016 = _mm512_loadu_pd(src+128);
        __m512d r017 = _mm512_loadu_pd(src+136);
        __m512d r018 = _mm512_loadu_pd(src+144);
        __m512d r019 = _mm512_loadu_pd(src+152);
        __m512d r020 = _mm512_loadu_pd(src+160);
        __m512d r021 = _mm512_loadu_pd(src+168);
        __m512d r022 = _mm512_loadu_pd(src+176);
        __m512d r023 = _mm512_loadu_pd(src+184);
        __m512d r024 = _mm512_loadu_pd(src+192);
        __m512d r025 = _mm512_loadu_pd(src+200);
        __m512d r026 = _mm512_loadu_pd(src+208);
        __m512d r027 = _mm512_loadu_pd(src+216);
        __m512d r028 = _mm512_loadu_pd(src+224);
        __m512d r029 = _mm512_loadu_pd(src+232);
        __m512d r030 = _mm512_loadu_pd(src+240);
        __m512d r031 = _mm512_loadu_pd(src+248);
        
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
        len -= 256 ;
        src += 256  ;
    } // while
    /*
     * 
     */
    while( len >= 128 ) {
        __m512d r000 = _mm512_loadu_pd(src+0);
        __m512d r001 = _mm512_loadu_pd(src+8);
        __m512d r002 = _mm512_loadu_pd(src+16);
        __m512d r003 = _mm512_loadu_pd(src+24);
        __m512d r004 = _mm512_loadu_pd(src+32);
        __m512d r005 = _mm512_loadu_pd(src+40);
        __m512d r006 = _mm512_loadu_pd(src+48);
        __m512d r007 = _mm512_loadu_pd(src+56);
        __m512d r008 = _mm512_loadu_pd(src+64);
        __m512d r009 = _mm512_loadu_pd(src+72);
        __m512d r010 = _mm512_loadu_pd(src+80);
        __m512d r011 = _mm512_loadu_pd(src+88);
        __m512d r012 = _mm512_loadu_pd(src+96);
        __m512d r013 = _mm512_loadu_pd(src+104);
        __m512d r014 = _mm512_loadu_pd(src+112);
        __m512d r015 = _mm512_loadu_pd(src+120);
        
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
        len -= 128 ;
        src += 128  ;
    } // while
    /*
     * 
     */
    while( len >= 64 ) {
        __m512d r000 = _mm512_loadu_pd(src+0);
        __m512d r001 = _mm512_loadu_pd(src+8);
        __m512d r002 = _mm512_loadu_pd(src+16);
        __m512d r003 = _mm512_loadu_pd(src+24);
        __m512d r004 = _mm512_loadu_pd(src+32);
        __m512d r005 = _mm512_loadu_pd(src+40);
        __m512d r006 = _mm512_loadu_pd(src+48);
        __m512d r007 = _mm512_loadu_pd(src+56);
        
        r000 = _mm512_add_pd(r000, r004);
        r001 = _mm512_add_pd(r001, r005);
        r002 = _mm512_add_pd(r002, r006);
        r003 = _mm512_add_pd(r003, r007);
        
        r000 = _mm512_add_pd(r000, r002);
        r001 = _mm512_add_pd(r001, r003);
        
        r000 = _mm512_add_pd(r000, r001);

        initial += _mm512_reduce_add_pd(r000) ;
        len -= 64 ;
        src += 64  ;
    } // while
    /*
     * 
     */
    while( len >= 32 ) {
        __m512d r000 = _mm512_loadu_pd(src+0);
        __m512d r001 = _mm512_loadu_pd(src+8);
        __m512d r002 = _mm512_loadu_pd(src+16);
        __m512d r003 = _mm512_loadu_pd(src+24);
        
        r000 = _mm512_add_pd(r000, r002);
        r001 = _mm512_add_pd(r001, r003);
        
        r000 = _mm512_add_pd(r000, r001);

        initial += _mm512_reduce_add_pd(r000) ;
        len -= 32 ;
        src += 32  ;
    } // while
    /*
     * 
     */
    while( len >= 16 ) {
        __m512d r000 = _mm512_loadu_pd(src+0);
        __m512d r001 = _mm512_loadu_pd(src+8);
        
        r000 = _mm512_add_pd(r000, r001);

        initial += _mm512_reduce_add_pd(r000) ;
        len -= 16 ;
        src += 16  ;
    } // while
    /*
     * 
     */
    while( len >= 8 ) {
        __m512d r000 = _mm512_loadu_pd(src+0);

        initial += _mm512_reduce_add_pd(r000) ;
        len -= 8 ;
        src += 8  ;
    } // while

    // clean up on aisle 3
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }

    return initial ;   
}
