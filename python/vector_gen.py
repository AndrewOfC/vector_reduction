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
        filename = f"vector_reduce_{dtype.replace("_t","")}.c"
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

    return


if __name__ == "__main__":
    main()
