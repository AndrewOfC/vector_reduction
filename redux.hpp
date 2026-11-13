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
// Created by andrew on 10/29/26.
//

#pragma once
#ifndef REDUX_REDUX_HPP
#define REDUX_REDUX_HPP
#include <string>
#include <vector>
#include <experimental/simd>
#include <boost/align/aligned_allocator.hpp>


struct BenchmarkRecord {
    BenchmarkRecord() = default;
    BenchmarkRecord(const BenchmarkRecord& record) : type_name(record.type_name), sample_count(record.sample_count), iterations(record.iterations),
                                                      std_reduce_speedup(record.std_reduce_speedup), intrinsic_speedup(record.intrinsic_speedup),
                                                      std_simd_speedup(record.std_simd_speedup), std_simple_simd_speedup(record.std_simple_simd_speedup),
                                                      std_vararg_speedup(record.std_vararg_speedup), std_vararg_speedup_simd(record.std_vararg_speedup_simd) {}

    std::string type_name ;
    size_t sample_count ;
    size_t iterations;

    double std_reduce_speedup ;
    double intrinsic_speedup ;
    double std_simd_speedup ;
    double std_simple_simd_speedup ;
    double std_vararg_speedup ;
    double std_vararg_speedup_simd ;
    double sve_speedup ;
};

struct BenchmarkResults {
    BenchmarkResults() = default;

    double time ;
    std::string cpu_name ;
    std::string machine ;
    std::vector<BenchmarkRecord> records ;
};

int save_benchmark_results(BenchmarkResults& results, const std::string& filename) ;


std::string getCpuNameFromProc();

template<typename T>
using vector_aligned64_t = std::vector<T, boost::alignment::aligned_allocator<T, 64>> ;

template<typename T>
void filldata(vector_aligned64_t<T>& data, size_t size, bool simple) ;

template<typename T>
bool BenchmarkRun(size_t count, size_t iterations, double runTime, BenchmarkRecord& record, bool simple = false) ;

#endif //REDUX_REDUX_HPP
