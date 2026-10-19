import argparse
import sys

import jinja2 as j2
from jinja2 import FileSystemLoader, Environment

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

double reduce{{"%03d"|format(n*8)}}(double *src, size_t len, double initial /* = 0 */)
{
   {%if avx512 %}
   {% include "avx512.jinja2" %}
   {% elif neon %}
   {% include "neon.jinja2" %}
   {% else %}
#error "No vectorization defined"
   {% endif %}   
}
"""

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output")
    parser.add_argument("-n", type=int, default=32)
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("--avx512", action="store_true")
    parser.add_argument("--neon", action="store_true")
    args = parser.parse_args()

    file_loader = FileSystemLoader('.')

    # 2. Initialize the Jinja environment
    env = Environment(loader=file_loader)

    template = env.from_string(ROOT_TEMPLATE)

    i = args.n
    steps = []
    while i >= 1:
        i //= 2
        steps.append(i)

    if args.output is None:
        outs = sys.stdout
    else:
        outs = open(args.output, "w")

    text = template.render(n=args.n,
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
