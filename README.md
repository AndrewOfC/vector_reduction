

# Overview

Experiments with leveraging AVX-512 and NEON for vectorized reduction operations.

# Notes

Using pure intrinsics in both AVX and NEON appears to produce better results
than using inline assembly.  This is probably due to compiler at higher optimization levels being able to better schedule instructions and manage registers than a human can.

The rendering code can use all 32 of the AVX registers, but the reduction code can only use 16 of them.  This is because the reduction code is compiled with `-mavx512f` and `-mavx512vl`, which enables the use of AVX-512 instructions, but also limits the number of registers available for use.