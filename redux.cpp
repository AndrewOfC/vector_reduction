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

#include "redux.hpp"

#include <iomanip>
#include <iostream>
#include <random>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>
#include <boost/json.hpp>

#include "vector_reduce.h"

namespace po = boost::program_options;
using namespace std;
using boost::timer::cpu_timer;

extern vector<size_t> Sample_counts ;

int main(int argc, char *argv[])
{
    size_t count = 1, count256 = 0;
    unsigned int iterations = 1 ;
    bool simple = false;
    bool doDouble=false, doFloat=false, doInt32=false, doInt64=false;
    double runTime = 0.0;
    size_t step = 100 ;
    size_t upper = 10000 ;
    bool experiment = false ;
    std::string cpu_name = getCpuNameFromProc(), machine_name = "" ;
    try
    {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("step,s", po::value<size_t>(&step)->default_value(0), "json sample step size")
            ("upper,u", po::value<size_t>(&upper)->default_value(-1), "json sample upper limit")
            ("experiment,x", "run experiment")
            ("time,t",  po::value<double>(&runTime)->default_value(0.0), "run timing")
            ("COUNT,C", po::value<size_t>(&count256)->default_value(0), "number of 256x elements to reduce")
            ("count,c", po::value<size_t>(&count)->default_value(0), "number of elements to reduce")
            ("iterations,i", po::value<unsigned int>(&iterations)->default_value(1), "number of iterations to run")
            ("double,d", "run double precision")
            ("float,f", "run single precision")
            ("int32", "run int32_t")
            ("int64", "run int64_t")
        ("machine-name,m", po::value<std::string>(&machine_name)->default_value("unknown"), "machine name for json output")
        ("simple", "run simple data set (0,1,2,3...)");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        cout << "CPU: " << cpu_name << endl;
        cout << "sizeof(vector_t<double>) = " << sizeof(vector_t<double>) << " ";
        cout << "vector_t<double>::size() = " << vector_t<double>::size() << endl ;

        if (vm.count("help"))
        {
            cout << desc << "\n";
            return 0;
        }

        experiment = vm.count("experiment") != 0;

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
    count += count256 * 256 ;
    const vector sample_counts2 = { count };
    const vector<size_t>& sample_counts = count == 0 ? Sample_counts : sample_counts2;

    if (step == 0)
    {
        upper = count ;
        step = 1 ;
    }
    if (experiment)
    {
        // do experiments here
        exit(0);
    }

    BenchmarkResults results;
    results.time = runTime;
    results.cpu_name = cpu_name;
    results.machine = machine_name ;


    for ( size_t sample_count : sample_counts ) {
        BenchmarkRecord record;
        if ( doDouble)
        {
            BenchmarkRun<double>(sample_count, iterations, runTime, record, simple);
        }

        if ( doFloat)
        {
            BenchmarkRun<float>(sample_count, iterations, runTime, record, simple);
        }

        if ( doInt32)
        {
            BenchmarkRun<int32_t>(sample_count, iterations, runTime, record, simple);
        }

        if ( doInt64)
        {
            BenchmarkRun<int64_t>(sample_count, iterations, runTime, record, simple);
        }
        results.records.push_back(record);
    } // for
    save_benchmark_results(results, "tmp.json") ;
    return 0;
}
