
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
