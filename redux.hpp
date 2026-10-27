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
};

struct BenchmarkResults {
    BenchmarkResults() = default;

    double time ;
    std::string cpu_name ;
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
