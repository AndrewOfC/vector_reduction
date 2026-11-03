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

import matplotlib.pyplot as plt
import numpy as np
import json

def gatherSamples(data, sample_count_limit, keys):
    x = []
    ys = []
    for d in data['records']:
        entry = [d[key] for key in keys]
        x.append(d['sample_count'])
        ys.append(entry)
        if x[-1] > sample_count_limit:
            break
    return x,ys

def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("file", nargs="+", help="profile json file")
    parser.add_argument("-r", "--render", action="store_true", help="Render the plot")
    parser.add_argument("--sample-count-limit", type=int, default=7000, help="Sample count limit")
    args = parser.parse_args()

    for file in args.file:


        data = json.load(open(file))
        machine = data.get("machine", "Unknown Machine")

        keys = ("std_reduce_speedup", "std_simple_simd_speedup", "std_simd_speedup")
        labels = ("std::reduce", "Simple SIMD", "Unfolded SIMD")
        x,ys = gatherSamples(data, args.sample_count_limit, keys)

        speedup_std_reduce, ax = plt.subplots()

        for i, key in enumerate(labels):
            y = [ ys[j][i] for j in range(len(x)) ]
            plt.plot(x,y, label=key)

        ax.set(xlabel="Sample Count",
               ylabel="Speedup",
               title=f"Speedup vs Simple Implementation\n{machine}")

        plt.legend()
        if args.render:
            output_name = file.replace(".json", ".png")
            plt.savefig(output_name)
            print(f"rendered {output_name}")
        else:
            plt.show()

    return

if __name__ == "__main__":
    main()
#data = np.loadtxt("speedup.csv", delimiter=",")
#
# plt.plot(data[:,0], data[:,1])
# plt.xlabel("Vector Length")
# plt.ylabel("Speedup vs Scalar")
# plt.xscale("log")
# plt.show()
