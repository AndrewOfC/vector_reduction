# Overview

Experiments with leveraging AVX-512 and NEON for vectorized
reduction operations, using python for code generation.

In this example we produce a vector reduction function that can be used with AVX-512 and NEON.

![](imgs/reduce.svg)

(Graphic courtesy of https://grok.com)

In the case of AVX-512, each register is 64 bytes in size. So each
add is adding 8 doubles at once or 16 floats. By using multiple
registers, we can take advantage of the parallelism of the CPU
where available.

Care has been taken to ensure that lengths that are not multiples
of 8 or 16 are handled correctly.

## Python

The more interesting part could be the Python code. Here we use a [jinja2](https://jinja.palletsprojects.com/en/stable/)
to render the code.
The compiler intrinsics for both AVX and NEON are
nearly identical in function, allowing us to recycle
the template.

This is especially useful when an algorithm appears as a pattern,
albeit a lengthy one. Using templates to render the code,
the conversion from AVX intrinsics to NEON is almost trivial.

# Usage

```c++
type vector_reduce(const type *data, size_t size) ;
```

Where type may be an int32_t, int64_, float, or double.

# Experimental gcc simd support

GCC has some experimental support for SIMD vectorization. Interesting just
a simple reduction loop:

```c++
template<typename T>
T genericSumSimd(T *src, size_t len, T initial)
{
    typedef stdx::native_simd<T> vector_t ;
    vector_t r ;
    while ( len >= vector_t::size() )
    {
        r.copy_from(src, stdx::vector_aligned);
        initial += stdx::reduce(r);
        len -= vector_t::size();
        src += vector_t::size();
    }
    for( size_t i = 0 ; i < len ; i++, src++ ) {
        initial += *src ;
    }
    return initial;
}

```

Consistently under performs the intrinsics 32x unfolded version by about 50%.
This is probably due to the stdx::reduction expanding out to fairly large
block if instructions.

When we apply the same pattern of using multiple variables (registers) to the
experimental simd code we recover the performance on par with the
intrinsics version.

## 32 Variables unfolded.

32 was chosen (though it can be rendered to more or less with the option supplied in
the python code). Since both AVX and NEON have 32 registers. However, in both
the intrinsics implementation and the experimental simd implementation, we are only using 16 registers. This is because
the reduction code is compiled with `-mavx512f` and `-mavx512vl`, which enables the use of AVX-512 instructions,
The compiler only uses 5 when we look at the compiled assembly code at the -O3 level.

```asm
.L3:
	vmovupd	(%rax), %zmm1
	addq	$2048, %rax
	vaddpd	-1024(%rax), %zmm1, %zmm1
	subq	$256, %rdx
	vmovupd	-1536(%rax), %zmm2
	vaddpd	-512(%rax), %zmm2, %zmm2
	vmovupd	-1792(%rax), %zmm3
	vaddpd	-768(%rax), %zmm3, %zmm3
	vmovupd	-1664(%rax), %zmm4
	vaddpd	-640(%rax), %zmm4, %zmm4
	vmovupd	-1600(%rax), %zmm5
	vaddpd	%zmm2, %zmm1, %zmm1
	vmovupd	-256(%rax), %zmm2
	vaddpd	-1280(%rax), %zmm2, %zmm2
	vaddpd	-576(%rax), %zmm5, %zmm5
	vaddpd	%zmm3, %zmm2, %zmm2
	vmovupd	-1408(%rax), %zmm3
	vaddpd	-384(%rax), %zmm3, %zmm3
	vaddpd	%zmm2, %zmm1, %zmm1
	vmovupd	-1920(%rax), %zmm2
	vaddpd	-896(%rax), %zmm2, %zmm2
	vaddpd	%zmm3, %zmm2, %zmm2
	vmovupd	-128(%rax), %zmm3
	vaddpd	-1152(%rax), %zmm3, %zmm3
	vaddpd	%zmm4, %zmm3, %zmm3
	vmovupd	-1728(%rax), %zmm4
	vaddpd	-704(%rax), %zmm4, %zmm4
	vaddpd	%zmm3, %zmm2, %zmm2
	vmovupd	-1472(%rax), %zmm3
	vaddpd	-448(%rax), %zmm3, %zmm3
	vaddpd	%zmm2, %zmm1, %zmm1
	vmovupd	-1984(%rax), %zmm2
	vaddpd	-960(%rax), %zmm2, %zmm2
	vaddpd	%zmm3, %zmm2, %zmm2
	vmovupd	-192(%rax), %zmm3
	vaddpd	-1216(%rax), %zmm3, %zmm3
	vaddpd	%zmm4, %zmm3, %zmm3
	vmovupd	-1344(%rax), %zmm4
	vaddpd	-320(%rax), %zmm4, %zmm4
	vaddpd	%zmm3, %zmm2, %zmm2
	vmovupd	-1856(%rax), %zmm3
	vaddpd	-832(%rax), %zmm3, %zmm3
	vaddpd	%zmm4, %zmm3, %zmm3
	vmovupd	-64(%rax), %zmm4
	vaddpd	-1088(%rax), %zmm4, %zmm4
	vaddpd	%zmm5, %zmm4, %zmm4
	vaddpd	%zmm4, %zmm3, %zmm3
	vaddpd	%zmm3, %zmm2, %zmm2
	vaddpd	%zmm2, %zmm1, %zmm1
	vextractf64x4	$0x1, %zmm1, %ymm2
	vaddpd	%ymm1, %ymm2, %ymm2
	vextractf32x4	$0x1, %ymm2, %xmm1
	vaddpd	%xmm2, %xmm1, %xmm1
	vunpckhpd	%xmm1, %xmm1, %xmm2
	vaddsd	%xmm1, %xmm2, %xmm1
	vaddsd	%xmm1, %xmm0, %xmm0
	cmpq	$255, %rdx
	ja	.L3


```

## _CAUTION_ Byte Alignment

In order to use this code with AVX-512, the input data must be byte aligned to a 64 byte
boundary. This means that the address of the data must be a multiple of 64 bytes. This is because AVX-512 uses 512-bit
registers, which are 64 bytes in size. If the data is not byte aligned, the code will not work correctly.

16-byte boundaries are highly recommended for NEON.

### With C++ and Boost [Aligned Allocator](https://www.boost.org/doc/libs/latest/doc/html/align/reference.html#align.reference.classes.aligned_allocator)

```c++
#include <boost/align/aligned_allocator.hpp>
typedef double target_type ;
typedef std::vector<target_type, boost::alignment::aligned_allocator<target_type, 64>> vector_aligned64_t;
```

### With POSIX

```C
#include <stdlib.h>
int posix_memalign(void **memptr, size_t alignment, size_t size);
```

# Applications

Numeric algorithms that need a reduction operation, where
this can be used to accelerate the computation without the
need for a dedicated GPU.

The threshold for the need of a GPU
can be raised here since the upload/download penalty to GPU
memory can be avoided.

# Benchmarking

With Double precision floating point (64-bit)

| Platform                  | approx Speedup vs std::reduce |
|---------------------------|-------------------------------|
| i9-11950H                 | 5-8x                          |
| Apple M4                  | 5-8x                          |
| Raspberry Pi 4 Model B    | 1.04x                         |
| Raspberry Pi 5 Model B    | 2-3x                          |
| GitHub Action linux-arm64 | 3.75x                         |                                |           |
| Xeon(R) 6975P-C(EC2 c8i)  | 9-10x                         |

The performance of the M4 was something of a surprise.
The NEON vector registers only hold 2 double, where as
the AVX2 vector registers hold 8 doubles.

# Setup Ubuntu

## Gtest

```bash
git clone https://github.com/google/googletest.git
cd googletest
git checkout v1.18.0
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j `nproc`
sudo make install
```

## Boost

```bash
sudo apt install libboost-program-options-dev libboost-timer-dev
```

## gcc-16

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install gcc-16 g++-16
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 13 
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-16 16
# Select GCC 16 as the default
sudo update-alternatives --config gcc
```

## Python

# Setup amazon Linux

```bash
sudo dnf groupinstall "Desktop" -y
sudo dnf install python3.14 gcc-c++ git cmake boost-devel gtest-devel
sudo python3.14 -m pip install jinja2
```

# Setup Ubuntu

```bash
cd python
virtualenv -p python3 .venv
source .venv/bin/activate
pip install -r requirements.txt
python vector_gen.py -v
```

# Notes

Using pure intrinsics in both AVX and NEON appears to produce better results
than using inline assembly. This is probably due to compilers at higher optimization levels being able to better
schedule instructions and manage registers than a human can.

The rendering code can use all 32 of the AVX registers, but the reduction code can only use 16 of them. This is because
the reduction code is compiled with `-mavx512f` and `-mavx512vl`, which enables the use of AVX-512 instructions, but
also limits the number of registers available for use.

## reduce int16 (courtesy of gemini)

```C
#include <immintrin.h>

int16_t reduce_add_epi16_tree(__m512i v) {
    // 512-bit to 256-bit
    __m256i low256  = _mm512_castsi512_si256(v);
    __m256i high256 = _mm512_extracti64x4_epi64(v, 1);
    __m256i sum256  = _mm256_add_epi16(low256, high256);

    // 256-bit to 128-bit
    __m128i low128  = _mm256_castsi256_si128(sum256);
    __m128i high128 = _mm256_extracti128_si128(sum256, 1);
    __m128i sum128  = _mm128_add_epi16(low128, high128);

    // 128-bit shift-and-add tree
    sum128 = _mm_add_epi16(sum128, _mm_srli_si128(sum128, 8)); // shift 64 bits
    sum128 = _mm_add_epi16(sum128, _mm_srli_si128(sum128, 4)); // shift 32 bits
    sum128 = _mm_add_epi16(sum128, _mm_srli_si128(sum128, 2)); // shift 16 bits

    return (int16_t)_mm_cvtsi128_si32(sum128);
}
```
