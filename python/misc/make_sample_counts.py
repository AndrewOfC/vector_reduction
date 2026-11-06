
TEMPLATE="""/*
 * MIT License
 * 
 * Copyright (c) 2026 Andrew Ellis Page
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * SPDX short identifier: MIT
 */

#include <vector>
std::vector<size_t> Sample_counts = {
        {%-for line in lines%}
        {{line}},
        {%-endfor%}
} ; 
 """

import argparse
import jinja2

def main():

    # spec start:stop:step
    # example 100:9000:100  100,200,300,400,... 9000
    parser = argparse.ArgumentParser(description='Generate sample counts for a given file.')
    parser.add_argument('specs', nargs='*', default=["100:9000:100", "10000:300000:1000"])
    parser.add_argument('--width', default=10)
    args = parser.parse_args()

    counts = []

    for spec in args.specs:
        start, stop, step = map(int, spec.split(':'))
        counts.extend(range(start, stop+step, step))

    lines = []
    while counts:
        ncounts = counts[0:args.width]
        counts = counts[args.width:]
        line = ", ".join(str(c) for c in ncounts)
        lines.append(line)

    template = jinja2.Template(TEMPLATE)
    print(template.render(lines=lines))

    return

if __name__ == "__main__":
    main()