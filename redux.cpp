/*
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

#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <boost/range/numeric.hpp>
#include <boost/align/aligned_allocator.hpp>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>

#include "vector_reduce.h"

#include "genericsum.hpp"

namespace po = boost::program_options;
using namespace std;
using boost::timer::cpu_timer;

template<typename T>
bool almostEqualAbsolute(T a, T b, T tolerance = 5e-7) {
    return std::fabs(a - b) <= tolerance;
}

template<typename T>
using vector_aligned64_t = std::vector<T, boost::alignment::aligned_allocator<T, 64>> ;

template<typename T>
void filldata(vector_aligned64_t<T>& data, size_t size, bool simple)
{
    data.resize(size);
    if (!simple)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(-1000, 1000);
        for (size_t i = 0; i < data.size(); i++)
        {
            data[i] = (T)(dist(gen));
        }
    }
    else
    {
        for (size_t i = 0; i < data.size(); i++)
        {
            data[i] = i;
        }
    }
}

template<typename T>
bool PerformanceRun(size_t count, unsigned int iterations, bool simple)
{
    vector_aligned64_t<T> data ;
    filldata(data, count, simple);

    cout << "##" << endl;
    cout << "## Performance run for type: " << typeid(T).name() << ", count: " << count << ", iterations: " << iterations << endl;
    cout << "##" << endl;

    string formatt = "%u" ;
    T result = 0, initial=0.0 ;
    T check_result = 0;
    /*
     * std::reduce
     */
    cpu_timer timer1;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        check_result = std::reduce(data.begin(), data.end(), initial);
        //check_result = genericSum(data.data(), count, initial);
        //check_result = boost::accumulate(data, initial);
    }
    timer1.stop();
    auto std_elapsed = timer1.elapsed().user;
    cout << "standard Result: " << check_result << "  " << timer1.format(5, formatt) << endl;
    /*
     * vector_reduce
     */
    cpu_timer timer2;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        result = vector_reduce(data.data(), count);
    }
    timer2.stop();
    auto elapsed = timer2.elapsed().user;
    cout << "intrinsics Result: " << result << "  " << timer2.format(5, formatt) << endl;
    cout << "intrinsics speedup: " << std::fixed << std::setprecision(2) << (double)std_elapsed / (double)elapsed << endl;
    /*
     * vector_reduce_simd
     */
    cpu_timer timer3;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        result = vector_reduce_simd(data.data(), count);
    }
    timer3.stop();
    cout << "vector_reduce_simd Result: " << result << "  " << timer3.format(5, formatt) << endl;
    elapsed = timer3.elapsed().user;
    cout << "simd speedup: " << std::fixed << std::setprecision(2) << (double)std_elapsed / (double)elapsed << endl;

    bool success = almostEqualAbsolute(result, check_result) ;

    cpu_timer timer4;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        result = genericSumSimd(data.data(), count, initial);
    }
    timer4.stop();
    elapsed = timer4.elapsed().user ;
    cout << "gsimd Result: " << result << "  " << timer4.format(5, formatt) << endl;
    cout << "gvec  speedup: " << std::fixed << std::setprecision(2) << (double)std_elapsed / (double)elapsed << endl;

    if (!success)
    {
        cerr << "Error: Results do not match!  " << check_result - result << endl;

    }
    return success ;
}

int main(int argc, char *argv[])
{
    size_t count = 1;
    unsigned int iterations = 1 ;
    bool simple = false;
    bool doDouble=false, doFloat=false, doInt32=false, doInt64=false;
    try
    {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("simple,s", "run simple test")
            ("experiment,x", "run experiment")
            ("count,c", po::value<size_t>(&count)->default_value(1), "number of 256x elements to reduce")
            ("iterations,i", po::value<unsigned int>(&iterations)->default_value(1), "number of iterations to run")
            ("double,d", "run double precision")
            ("float,f", "run single precision")
            ("int32", "run int32_t")
            ("int64", "run int64_t");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("experiment"))
        {
            vector_aligned64_t<double> data ;
            filldata(data, 16, true);
            //SIMDReduce(data.data(), data.size(), 0.0) ;
            exit(0);
        }

        if (vm.count("help"))
        {
            cout << desc << "\n";
            return 0;
        }
        simple = vm.count("simple") != 0;

        doDouble = vm.count("double") != 0;
        doFloat = vm.count("float") != 0;
        doInt32 = vm.count("int32") != 0;
        doInt64 = vm.count("int64") != 0;

        if (!doDouble && !doFloat && !doInt32 && !doInt64)
        {
            doDouble = true;
            doFloat = true;
            doInt32 = true;
            doInt64 = true;
        }

    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    count *= 256 ;

    if ( doDouble)
    {
        PerformanceRun<double>(count, iterations, simple);
    }

    if ( doFloat)
    {
        PerformanceRun<float>(count, iterations, simple);
    }

    if ( doInt32)
    {
        PerformanceRun<int32_t>(count, iterations, simple);
    }

    if ( doInt64)
    {
        PerformanceRun<int64_t>(count, iterations, simple);
    }

    return 0;
}