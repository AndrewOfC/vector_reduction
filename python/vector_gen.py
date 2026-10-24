# MIT License
# 
# Copyright (c) 2026 Andrew Ellis Page
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# 
# SPDX short identifier: MIT
import argparse
import os
import sys

from jinja2 import FileSystemLoader, Environment

from profiles import NEONTypes, AVX512Types, RenderTypes

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output_dir", default="..", help="Output directory")
    parser.add_argument("-n", type=int, default=32)
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("--root-template", default="root.jinja2", help="Root template file")
    parser.add_argument("--intrinsics-template", default="intrinsics.jinja2", help="Template file for vectorization")
    args = parser.parse_args()

    file_loader = FileSystemLoader('.')

    # 2. Initialize the Jinja environment
    env = Environment(loader=file_loader)

    template = env.get_template(args.root_template)

    i = args.n
    steps = []
    while i >= 1:
        steps.append(i)
        i //= 2

    for dtype in RenderTypes:
        neon_profile = NEONTypes[dtype](args.n)
        avx_profile = AVX512Types[dtype](args.n)
        filename = f"vector_reduce_{dtype.replace('_t','')}.c"
        path = os.path.join(args.output_dir, filename)
        outs = open(path, "w")

        text = template.render(n=args.n,
                               DTYPE=dtype,
                               intrinsics_template=args.intrinsics_template,
                               steps=steps,
                               avx_profile=avx_profile,
                               neon_profile=neon_profile)
        if args.verbose:
            print(text)
        outs.write(text)

    #experimental simd
    path = os.path.join(args.output_dir, "vector_reduce_simd.cpp")

    template = env.get_template("gccsimd.jinja2")

    text = template.render(regs=args.n,steps=steps)
    if args.verbose:
        print(text)
    outs = open(path, "w")
    outs.write(text)
    return


if __name__ == "__main__":
    main()
