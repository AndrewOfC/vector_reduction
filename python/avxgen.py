import argparse
import sys

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
        self.step = n_registers * 2


class AVX512ProfileDouble(VectorProfile):
    def __init__(self, n_registers):
        super().__init__("AVX512", n_registers=n_registers)
        self.DTYPE = "double"
        self.LOAD = "vmovapd"
        self.ADD = "vaddpd"
        self.REDUCE = "_mm512_reduce_add_pd"
        self.step = n_registers * 8


ROOT_TEMPLATE = """
#include <cstdint>
#include <iostream>

#if defined(__AVX512F__)
#include <immintrin.h>
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#else
#error "Unsupported CPU"
#endif

{{p.DTYPE}} vector_reduce(double *src, size_t len, double initial /* = 0 */)
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

NEONTTypes = {
    "double": NEONProfileDouble,
    "float": None
}

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output")
    parser.add_argument("-n", type=int, default=32)
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("--avx512", action="store_true")
    parser.add_argument("--neon", action="store_true")
    parser.add_argument("--template-avx", default="avx512.jinja2", help="Template file for AVX512 vectorization")
    parser.add_argument("--template-neon", default="neon.jinja2", help="Template file for NEON vectorization")
    parser.add_argument("--interleave", action="store_true", help="Manually interleave AVX512 steps")
    args = parser.parse_args()

    file_loader = FileSystemLoader('.')

    # 2. Initialize the Jinja environment
    env = Environment(loader=file_loader)

    if args.neon:
        vector_profile = NEONTTypes["double"](args.n)
    elif args.avx512:
        vector_profile = AVX512ProfileDouble(args.n)
    else:
        print("No vectorization defined", file=sys.stderr)
        sys.exit(1)

    template = env.from_string(ROOT_TEMPLATE)

    i = args.n
    steps = []
    if args.avx512 and args.interleave:
        i //= 2 # we're going to handle the first 'step' differently
    while i >= 1:
        steps.append(i)
        i //= 2

    if args.output is None:
        outs = sys.stdout
    else:
        outs = open(args.output, "w")

    text = template.render(n=args.n,
                           p=vector_profile,
                           avx_template=args.template_avx,
                           neon_template=args.template_neon,
                           steps=steps,
                           neon=args.neon,
                           avx512=args.avx512)
    if args.verbose:
        print(text)
    if args.output:
        print(text, file=outs)

    return


if __name__ == "__main__":
    main()
