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

//
// Created by parallels on 10/29/26.
//

#include <fstream>
#include <iostream>
#include <boost/timer/timer.hpp>
#include <iomanip>
#include <random>
#include <boost/range/numeric.hpp>
#include <boost/program_options.hpp>
#include <boost/json.hpp>
#include <sys/mman.h>

#include "redux.hpp"
#include "vector_reduce.h"

using namespace std;
using boost::timer::cpu_timer;

template<typename T>
bool almostEqualAbsolute(T a, T b, T tolerance = 5e-7) {
    return std::fabs(a - b) <= tolerance;
}

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


void tag_invoke(boost::json::value_from_tag, boost::json::value& jv, const BenchmarkRecord& record) {
    jv = {
        {"type_name", record.type_name},
        {"sample_count", record.sample_count},
        {"iterations", record.iterations},
        {"std_reduce_speedup", record.std_reduce_speedup},
        {"intrinsic_speedup", record.intrinsic_speedup},
        {"std_simd_speedup", record.std_simd_speedup},
        {"std_simple_simd_speedup", record.std_simple_simd_speedup},
        {"std_vararg_speedup", record.std_vararg_speedup},
        {"std_vararg_speedup_simd", record.std_vararg_speedup_simd}
    };
}

BenchmarkRecord tag_invoke(boost::json::value_to_tag<BenchmarkRecord>, const boost::json::value& jv) {
    BenchmarkRecord record;
    record.type_name = boost::json::value_to<std::string>(jv.at("type_name"));
    record.sample_count = static_cast<size_t>(jv.at("sample_count").as_uint64());
    record.iterations = static_cast<size_t>(jv.at("iterations").as_uint64());
    record.std_reduce_speedup = boost::json::value_to<double>(jv.at("std_reduce_speedup"));
    record.intrinsic_speedup = boost::json::value_to<double>(jv.at("intrinsic_speedup"));
    record.std_simd_speedup = boost::json::value_to<double>(jv.at("std_simd_speedup"));
    record.std_simple_simd_speedup = boost::json::value_to<double>(jv.at("std_simple_simd_speedup"));
    record.std_vararg_speedup = boost::json::value_to<double>(jv.at("std_vararg_speedup"));
    record.std_vararg_speedup_simd = boost::json::value_to<double>(jv.at("std_vararg_speedup_simd"));
    return record;
}

void tag_invoke(boost::json::value_from_tag, boost::json::value& jv, const BenchmarkResults& results) {

    boost::json::array arr;

    for (const auto& record : results.records) {
        arr.push_back(boost::json::value_from(record));
    }

    jv = {
        {"cpu_name", results.cpu_name},
        {"time", results.time},
        {"records", std::move(arr)}
    };
}

template<typename T>
bool BenchmarkRun(size_t count, size_t iterations, double runTime, BenchmarkRecord& record, bool simple /*= false*/)
{
    vector_aligned64_t<T> data ;
    filldata(data, count, simple);
    mlock(data.data(), data.size() * sizeof(T));
    record.type_name = typeid(T).name();
    record.sample_count = count;
    record.iterations = iterations;
    size_t total_iterations = 0;

    cout << "##" << endl;
    cout << "## Performance run for type: " << typeid(T).name() << ", count: " << count << ", iterations: " << iterations << endl;
    cout << "##" << endl;

    string formatt = "%u" ;
    T result = 0, initial=0.0 ;
    T check_result = 0;
    boost::timer::nanosecond_type std_elapsed ;
    cpu_timer timer ;
    if ( runTime > 0.0 )
    {
        while ( timer.elapsed().user < runTime * 1e9 )
        {
            for (size_t i = 0; i < iterations; ++i)
            {
                result = vector_reduce_simple(data.data(), count, initial);
            }
            total_iterations += iterations ;
        }
        timer.stop();
        std_elapsed = timer.elapsed().user ;
        cout << "Total iterations: " << total_iterations << endl;
    }
    else {
       for (unsigned int i = 0; i < iterations; ++i)
        {
            result = vector_reduce_simple(data.data(), count, initial);
            //check_result = boost::accumulate(data, initial);
        }
        std_elapsed = timer.elapsed().user;
    }
    iterations = total_iterations;

    /*
     * vector_reduce_simple
     */
    cout << "standard Result: " << result << "  " << timer.format(5, formatt) << endl;

    /*
     * std::reduce
     */
    cpu_timer timer1;
    for (size_t i = 0; i < iterations; ++i)
    {
        check_result = std::reduce(data.begin(), data.end(), initial);
        //check_result = vector_reduce_simple(data.data(), count, initial);
        //check_result = boost::accumulate(data, initial);
    }
    timer1.stop();
    auto elapsed = timer1.elapsed().user;
    record.std_reduce_speedup = (double)std_elapsed / (double)elapsed;
    cout << "std::reduce speedup:        " << std::fixed << std::setprecision(2) << record.std_reduce_speedup << endl;
    /*
     * vector_reduce
     */
    cpu_timer timer2;
    for (size_t i = 0; i < iterations; ++i)
    {
        result = vector_reduce(data.data(), count);
    }
    timer2.stop();
    elapsed = timer2.elapsed().user;
    bool success = almostEqualAbsolute(result, check_result) ;
    record.intrinsic_speedup = (double)std_elapsed / (double)elapsed;
    cout << "intrinsics speedup:         " << std::fixed << std::setprecision(2) << record.intrinsic_speedup << endl;
    /*
     * vector_reduce_simd
     */
    cpu_timer timer3;
    for (size_t i = 0; i < iterations; ++i)
    {
        result = vector_reduce_simd(data.data(), count);
    }
    timer3.stop();
    success = success && almostEqualAbsolute(result, check_result) ;

    elapsed = timer3.elapsed().user;
    record.std_simd_speedup = (double)std_elapsed / (double)elapsed;
    cout << "vector_reduce_simd speedup: " << std::fixed << std::setprecision(2) << record.std_simd_speedup << endl;


    cpu_timer timer4;
    for (size_t i = 0; i < iterations; ++i)
    {
        result = vector_reduce_simple_simd(data.data(), count, initial);
    }
    timer4.stop();
    elapsed = timer4.elapsed().user ;
    record.std_simple_simd_speedup = (double)std_elapsed / (double)elapsed;
    cout << "simple simd  speedup:       " << std::fixed << std::setprecision(2) << record.std_simple_simd_speedup << endl;
    success = success && almostEqualAbsolute(result, check_result) ;
    if (!success)
    {
        cerr << "Error: Results do not match!  " << check_result - result << endl;

    }

    cpu_timer timer5 ;
    for (size_t i = 0; i < iterations; ++i)
    {
        result = va_reduce(data.data(), count, initial);
    }
    timer5.stop();
    elapsed = timer5.elapsed().user ;
    record.std_vararg_speedup = (double)std_elapsed / (double)elapsed;
    cout << "vararg speedup:             " << std::fixed << std::setprecision(2) << record.std_vararg_speedup << endl;

    cpu_timer timer6 ;
    for (size_t i = 0; i < iterations; ++i)
    {
        result = va_reduce_simd(data.data(), count, initial);
    }
    timer6.stop();
    elapsed = timer6.elapsed().user ;
    record.std_vararg_speedup_simd = (double)std_elapsed / (double)elapsed;
    cout << "vararg simd speedup:        " << std::fixed << std::setprecision(2) << record.std_vararg_speedup_simd << endl;

    munlock(data.data(), data.size() * sizeof(T));


    return success ;
}


int save_benchmark_results(BenchmarkResults& results, const string& filename)
{
    boost::json::value json = boost::json::value_from(results) ;

    if ( filename.empty() )
    {
        cout << "Benchmark Results:" << endl;
        cout << json << endl ;
        return 0 ;
    }

    ofstream s(filename) ;
    s << json ;
    return 0 ;
}

template bool BenchmarkRun<double>(size_t count, size_t iterations, double runTime, BenchmarkRecord& record, bool simple /*= false*/) ;
template bool BenchmarkRun<float>(size_t count, size_t iterations, double runTime, BenchmarkRecord& record, bool simple /*= false*/) ;
template bool BenchmarkRun<int64_t>(size_t count, size_t iterations, double runTime, BenchmarkRecord& record, bool simple /*= false*/) ;
template bool BenchmarkRun<int32_t>(size_t count, size_t iterations, double runTime, BenchmarkRecord& record, bool simple /*= false*/) ;