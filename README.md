# Overview

Experiments with leveraging AVX-512 and NEON for vectorized reduction operations.

The more intesting part could be the python code.  Here we use a common web tool to render the code.
The compiler intrinsics for both AVX and NEON are 
nearly identical in function, allowing us to recycle
the template.

# Applications

Numeric algorithms that need a reduction operation, where
this can be used to accelerate the computation without the 
need for a dedicated GPU.   

The threshold for the need of a GPU
can be raised here since the upload/download penalty to GPU
memory can be avoided.  

# Benchmarking

With Double precision floating point(64-bit)

| Platform                  | approx Speedup |
|---------------------------|----------------|
| i9-11950H                 | 5-8x           |
| Apple M4                  | 5-8x           |
| Raspberry Pi 4 Model B    | 1.04x          |
| Raspberry Pi 5 Model B    | 2-3x           |
| GitHub Action linux-arm64 | 3.75x          |                                |           |

The performance of the M4 was something of a surprise.
The NEON vector registers only hold 2 double, where as
the AVX2 vector registers hold 8 doubles.

# Setup

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
sudo apt install libboost-all-dev
```

## Python

```bash
cd python
virtualenv -p python3 .venv
source .venv/bin/activate
pip install -r requirements.txt
python vector_gen.py -v
```


# Notes

Using pure intrinsics in both AVX and NEON appears to produce better results
than using inline assembly.  This is probably due to compiler at higher optimization levels being able to better schedule instructions and manage registers than a human can.

The rendering code can use all 32 of the AVX registers, but the reduction code can only use 16 of them.  This is because the reduction code is compiled with `-mavx512f` and `-mavx512vl`, which enables the use of AVX-512 instructions, but also limits the number of registers available for use.


## reduce int16(courtesy of gemini)

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
