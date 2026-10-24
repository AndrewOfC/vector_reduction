

import argparse
import os
import re
import sys
from pathlib import Path

line_start_re = re.compile(r"^", re.MULTILINE)

def script_sharp_handler(content):
    content = line_start_re.sub("# ", content)
    return content

def c_style_handler(content):
    ncontent = "/*\n"

    ncontent += line_start_re.sub(" * ", content)
    ncontent += "\n */\n"

    return ncontent 

def jinja2_handler(content):
    ncontent = "{#\n"
    ncontent += line_start_re.sub(" # ", content)
    ncontent += "\n-#}\n"

    return ncontent

Handlers = {".py": script_sharp_handler,
            ".c": c_style_handler,
            ".cpp": c_style_handler,
            ".h": c_style_handler,
            ".hpp": c_style_handler,
            ".jinja2": jinja2_handler,
}

def check_for_existing_license(content):
    return "SPDX-License-Identifier" in content \
        or "SPDX short identifier" in content

Skips = {".git", ".venv", ".env", "cmake-build-debug", "cmake-build-release", "cmake-build-relwithdebinfo", "build"}

def DoSkip(path):
    for e in str(path).split('/'):
        if e in Skips:
            return True
    return False

def main():
    base = os.path.abspath(os.path.dirname(__file__))

    parser = argparse.ArgumentParser(description="Inject license into a file.")
    parser.add_argument("--directory", default=os.path.join(base, "..", ".."), help="The directory with files to inject the license into.")
    parser.add_argument("--license", default=os.path.join(base, "..", "..", "LICENSE"), help="The license text to inject.")
    parser.add_argument("--verbose", "-v", action="store_true", help="Enable verbose output.")
    args = parser.parse_args()

    license_text = open(args.license, "r").read()

    extensions = set(Handlers.keys())

    for file_path in Path(args.directory).rglob("*"):
        if DoSkip(file_path):
            # if args.verbose:
            #     print(f"INFO: Skipping {file_path}")
            continue
        if os.path.islink(file_path):
            if args.verbose:
                print(f"INFO: File {os.path.basename(file_path)} is a symbolic link.")
            continue

        (_, ext) = os.path.splitext(file_path)
        if ext not in extensions:
            continue
        handler = Handlers.get(ext)
        if handler is None:
            print(f"ERROR: No handler found for file {os.path.basename(file_path)}:", file=sys.stderr)
            sys.exit(1)

        with open(file_path, "r") as f:
            content = f.read()

        if check_for_existing_license(content):
            if args.verbose:
                print(f"INFO: File {os.path.basename(file_path)} already contains a license.")
            continue

        license_content = handler(license_text)
        
        with open(file_path, "w") as f:
            f.write(license_content)
            f.write("\n")
            f.write(content)
        if args.verbose:
            print(f"INFO: License injected into file {os.path.basename(file_path)}.")


if __name__ == "__main__":
    main()