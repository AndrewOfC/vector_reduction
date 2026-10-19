
#include <cstdint>
#include <iostream>

#if defined(__AVX512F__)
#include <immintrin.h>
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#else
#error "Unsupported CPU"
#endif

double reduce256(double *src, size_t len, double initial /* = 0 */)
{
   
      register double *srcPtr asm("r8") = src ;
   asm volatile (
       "movq %1, %0"
       : "=r" (srcPtr)  // Output: write to the register bound to srcPtr
       : "m" (src)     // Input: the pointer address
   );

   while( len > 0 ) {

        /*
         * load
         */
       asm volatile(
       "vmovapd 0(%%r8), %%zmm0\n\t" : : : "zmm0"
       ) ;
       asm volatile(
       "vmovapd 64(%%r8), %%zmm1\n\t" : : : "zmm1"
       ) ;
       asm volatile(
       "vmovapd 128(%%r8), %%zmm2\n\t" : : : "zmm2"
       ) ;
       asm volatile(
       "vmovapd 192(%%r8), %%zmm3\n\t" : : : "zmm3"
       ) ;
       asm volatile(
       "vmovapd 256(%%r8), %%zmm4\n\t" : : : "zmm4"
       ) ;
       asm volatile(
       "vmovapd 320(%%r8), %%zmm5\n\t" : : : "zmm5"
       ) ;
       asm volatile(
       "vmovapd 384(%%r8), %%zmm6\n\t" : : : "zmm6"
       ) ;
       asm volatile(
       "vmovapd 448(%%r8), %%zmm7\n\t" : : : "zmm7"
       ) ;
       asm volatile(
       "vmovapd 512(%%r8), %%zmm8\n\t" : : : "zmm8"
       ) ;
       asm volatile(
       "vmovapd 576(%%r8), %%zmm9\n\t" : : : "zmm9"
       ) ;
       asm volatile(
       "vmovapd 640(%%r8), %%zmm10\n\t" : : : "zmm10"
       ) ;
       asm volatile(
       "vmovapd 704(%%r8), %%zmm11\n\t" : : : "zmm11"
       ) ;
       asm volatile(
       "vmovapd 768(%%r8), %%zmm12\n\t" : : : "zmm12"
       ) ;
       asm volatile(
       "vmovapd 832(%%r8), %%zmm13\n\t" : : : "zmm13"
       ) ;
       asm volatile(
       "vmovapd 896(%%r8), %%zmm14\n\t" : : : "zmm14"
       ) ;
       asm volatile(
       "vmovapd 960(%%r8), %%zmm15\n\t" : : : "zmm15"
       ) ;
       asm volatile(
       "vmovapd 1024(%%r8), %%zmm16\n\t" : : : "zmm16"
       ) ;
       asm volatile(
       "vmovapd 1088(%%r8), %%zmm17\n\t" : : : "zmm17"
       ) ;
       asm volatile(
       "vmovapd 1152(%%r8), %%zmm18\n\t" : : : "zmm18"
       ) ;
       asm volatile(
       "vmovapd 1216(%%r8), %%zmm19\n\t" : : : "zmm19"
       ) ;
       asm volatile(
       "vmovapd 1280(%%r8), %%zmm20\n\t" : : : "zmm20"
       ) ;
       asm volatile(
       "vmovapd 1344(%%r8), %%zmm21\n\t" : : : "zmm21"
       ) ;
       asm volatile(
       "vmovapd 1408(%%r8), %%zmm22\n\t" : : : "zmm22"
       ) ;
       asm volatile(
       "vmovapd 1472(%%r8), %%zmm23\n\t" : : : "zmm23"
       ) ;
       asm volatile(
       "vmovapd 1536(%%r8), %%zmm24\n\t" : : : "zmm24"
       ) ;
       asm volatile(
       "vmovapd 1600(%%r8), %%zmm25\n\t" : : : "zmm25"
       ) ;
       asm volatile(
       "vmovapd 1664(%%r8), %%zmm26\n\t" : : : "zmm26"
       ) ;
       asm volatile(
       "vmovapd 1728(%%r8), %%zmm27\n\t" : : : "zmm27"
       ) ;
       asm volatile(
       "vmovapd 1792(%%r8), %%zmm28\n\t" : : : "zmm28"
       ) ;
       asm volatile(
       "vmovapd 1856(%%r8), %%zmm29\n\t" : : : "zmm29"
       ) ;
       asm volatile(
       "vmovapd 1920(%%r8), %%zmm30\n\t" : : : "zmm30"
       ) ;
       asm volatile(
       "vmovapd 1984(%%r8), %%zmm31\n\t" : : : "zmm31"
       ) ;
    
         asm volatile(
            "vaddpd %%zmm0, %%zmm16, %%zmm0" : "=r" (src) : : "zmm0"
         ) ;
         asm volatile(
            "vaddpd %%zmm1, %%zmm17, %%zmm1" : "=r" (src) : : "zmm1"
         ) ;
         asm volatile(
            "vaddpd %%zmm2, %%zmm18, %%zmm2" : "=r" (src) : : "zmm2"
         ) ;
         asm volatile(
            "vaddpd %%zmm3, %%zmm19, %%zmm3" : "=r" (src) : : "zmm3"
         ) ;
         asm volatile(
            "vaddpd %%zmm4, %%zmm20, %%zmm4" : "=r" (src) : : "zmm4"
         ) ;
         asm volatile(
            "vaddpd %%zmm5, %%zmm21, %%zmm5" : "=r" (src) : : "zmm5"
         ) ;
         asm volatile(
            "vaddpd %%zmm6, %%zmm22, %%zmm6" : "=r" (src) : : "zmm6"
         ) ;
         asm volatile(
            "vaddpd %%zmm7, %%zmm23, %%zmm7" : "=r" (src) : : "zmm7"
         ) ;
         asm volatile(
            "vaddpd %%zmm8, %%zmm24, %%zmm8" : "=r" (src) : : "zmm8"
         ) ;
         asm volatile(
            "vaddpd %%zmm9, %%zmm25, %%zmm9" : "=r" (src) : : "zmm9"
         ) ;
         asm volatile(
            "vaddpd %%zmm10, %%zmm26, %%zmm10" : "=r" (src) : : "zmm10"
         ) ;
         asm volatile(
            "vaddpd %%zmm11, %%zmm27, %%zmm11" : "=r" (src) : : "zmm11"
         ) ;
         asm volatile(
            "vaddpd %%zmm12, %%zmm28, %%zmm12" : "=r" (src) : : "zmm12"
         ) ;
         asm volatile(
            "vaddpd %%zmm13, %%zmm29, %%zmm13" : "=r" (src) : : "zmm13"
         ) ;
         asm volatile(
            "vaddpd %%zmm14, %%zmm30, %%zmm14" : "=r" (src) : : "zmm14"
         ) ;
         asm volatile(
            "vaddpd %%zmm15, %%zmm31, %%zmm15" : "=r" (src) : : "zmm15"
         ) ;
    
         asm volatile(
            "vaddpd %%zmm0, %%zmm8, %%zmm0" : "=r" (src) : : "zmm0"
         ) ;
         asm volatile(
            "vaddpd %%zmm1, %%zmm9, %%zmm1" : "=r" (src) : : "zmm1"
         ) ;
         asm volatile(
            "vaddpd %%zmm2, %%zmm10, %%zmm2" : "=r" (src) : : "zmm2"
         ) ;
         asm volatile(
            "vaddpd %%zmm3, %%zmm11, %%zmm3" : "=r" (src) : : "zmm3"
         ) ;
         asm volatile(
            "vaddpd %%zmm4, %%zmm12, %%zmm4" : "=r" (src) : : "zmm4"
         ) ;
         asm volatile(
            "vaddpd %%zmm5, %%zmm13, %%zmm5" : "=r" (src) : : "zmm5"
         ) ;
         asm volatile(
            "vaddpd %%zmm6, %%zmm14, %%zmm6" : "=r" (src) : : "zmm6"
         ) ;
         asm volatile(
            "vaddpd %%zmm7, %%zmm15, %%zmm7" : "=r" (src) : : "zmm7"
         ) ;
    
         asm volatile(
            "vaddpd %%zmm0, %%zmm4, %%zmm0" : "=r" (src) : : "zmm0"
         ) ;
         asm volatile(
            "vaddpd %%zmm1, %%zmm5, %%zmm1" : "=r" (src) : : "zmm1"
         ) ;
         asm volatile(
            "vaddpd %%zmm2, %%zmm6, %%zmm2" : "=r" (src) : : "zmm2"
         ) ;
         asm volatile(
            "vaddpd %%zmm3, %%zmm7, %%zmm3" : "=r" (src) : : "zmm3"
         ) ;
    
         asm volatile(
            "vaddpd %%zmm0, %%zmm2, %%zmm0" : "=r" (src) : : "zmm0"
         ) ;
         asm volatile(
            "vaddpd %%zmm1, %%zmm3, %%zmm1" : "=r" (src) : : "zmm1"
         ) ;
    
         asm volatile(
            "vaddpd %%zmm0, %%zmm1, %%zmm0" : "=r" (src) : : "zmm0"
         ) ;
    

        __m512d temp ;
        asm volatile(
            "vmovapd %%zmm0, %0\n\t" : "=m" (temp)
       ) ;
      initial += _mm512_reduce_add_pd(temp) ;
      srcPtr += 256  ;
      asm volatile("" : "+r" (srcPtr));  // keeps srcPtr from being optimized away

      len -= 256 ;

    }

    return initial ;
      
}
