import argparse
import os
import sys
from ctypes import sizeof, c_double, c_float, c_byte, c_int8, c_int16, c_int32, c_int64

from jinja2 import FileSystemLoader, Environment

class VectorProfile(object):
    def __init__(self, name, n_registers=32):
        self.name = name
        self._n_registers = n_registers
    n_registers = property(lambda self: self._n_registers)


class NEONProfileDouble(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("NEON", n_registers=n_registers)
        self.VTYPE = "float64x2_t"
        self.DTYPE = "double"
        self.LOAD = "vld1q_f64"
        self.ADD = "vaddq_f64"
        self.EXTRACT = "vst1q_f64"
        self.STRIDE = 2


class AVX512ProfileDouble(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512d"
        self.DTYPE = "double"
        self.LOAD = "_mm512_loadu_pd"
        self.ADD = "_mm512_add_pd"
        self.REDUCE = "_mm512_reduce_add_pd"
        self.STRIDE = 512//(sizeof(c_double)*8)
        self.filename = "vector_reduce_double.c"


class AVX512ProfileFloat(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512"
        self.DTYPE = "float"
        self.LOAD = "_mm512_loadu_ps"
        self.ADD = "_mm512_add_ps"
        self.REDUCE = "_mm512_reduce_add_ps"
        self.STRIDE = 512//(sizeof(c_float)*8)
        self.filename = "vector_reduce_float.c"


class AVX512ProfileInt8(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.DTYPE = "int8_t"
        self.LOAD = "_mm512_loadu_epi8"
        self.ADD = "_mm512_add_epi8"
        self.REDUCE = "_mm512_reduce_add_epi8"
        self.STRIDE = 512 // (sizeof(c_int8) * 8)
        self.filename = "vector_reduce_int8.c"

class AVX512ProfileInt16(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.DTYPE = "int16_t"
        self.LOAD = "_mm512_loadu_epi16"
        self.ADD = "_mm512_add_epi16"
        self.REDUCE = "_mm512_reduce_add_epi16"
        self.STRIDE = 512 // (sizeof(c_int16) * 8)
        self.filename = "vector_reduce_int16.c"

class AVX512ProfileInt32(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.DTYPE = "int32_t"
        self.LOAD = "_mm512_loadu_epi32"
        self.ADD = "_mm512_add_epi32"
        self.REDUCE = "_mm512_reduce_add_epi32"
        self.STRIDE = 512 // (sizeof(c_int32) * 8)
        self.filename = "vector_reduce_int32.c"

class AVX512ProfileInt64(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512 Double", n_registers=n_registers)
        self.VTYPE = "__m512i"
        self.DTYPE = "int64_t"
        self.LOAD = "_mm512_loadu_epi64"
        self.ADD = "_mm512_add_epi64"
        self.REDUCE = "_mm512_reduce_add_epi64"
        self.STRIDE = 512 // (sizeof(c_int64) * 8)
        self.filename = "vector_reduce_int64.c"

ROOT_TEMPLATE = """
#include <stddef.h>
#include "vector_reduce.h"

#if defined(__AVX512F__)
#include <immintrin.h>
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#else
#error "Unsupported CPU"
#endif

{{p.DTYPE}} vector_reduce_{{ p.DTYPE | replace("_t", "") }}(const {{p.DTYPE}} *src, size_t len, {{p.DTYPE}} initial /* = 0 */)
{
   {%- if avx512 -%}
   {%- include avx_template -%}
   {%- elif neon -%}
   {%- include neon_template -%}
   {%- else -%}
#error "No vectorization defined"
   {%- endif %}   
}
"""

NEONTypes = {
    "double": NEONProfileDouble,
}

AVX512Types = {
    "double": AVX512ProfileDouble,
    "float": AVX512ProfileFloat,
    # "int8_t": AVX512ProfileInt8,
    # "int16_t": AVX512ProfileInt16,
    "int32_t": AVX512ProfileInt32,
    "int64_t": AVX512ProfileInt64,
}

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output_dir", default=".", help="Output directory")
    parser.add_argument("-n", type=int, default=32)
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("--avx512", action="store_true")
    parser.add_argument("--neon", action="store_true")
    parser.add_argument("--vector-type", default="double", choices=["double", "float"], help="Vector type for AVX512 and NEON vectorization")
    parser.add_argument("--template-avx", default="avx512.jinja2", help="Template file for AVX512 vectorization")
    parser.add_argument("--template-neon", default="neon.jinja2", help="Template file for NEON vectorization")
    args = parser.parse_args()

    file_loader = FileSystemLoader('.')

    # 2. Initialize the Jinja environment
    env = Environment(loader=file_loader)

    if not args.avx512 and not args.neon:
        print("No vectorization defined", file=sys.stderr)
        sys.exit(1)

    template = env.from_string(ROOT_TEMPLATE)

    i = args.n
    steps = []
    while i >= 1:
        steps.append(i)
        i //= 2

    for key, clazz in AVX512Types.items():
        profile = clazz(args.n)
        path = os.path.join(args.output_dir, profile.filename)
        outs = open(path, "w")

        text = template.render(n=profile.n_registers,
                               p=profile,
                               avx_template=args.template_avx,
                               neon_template=args.template_neon,
                               steps=steps,
                               neon=args.neon,
                               avx512=args.avx512)
        if args.verbose:
            print(text)
        outs.write(text)

    return


if __name__ == "__main__":
    main()
