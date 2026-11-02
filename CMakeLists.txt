cmake_minimum_required(VERSION 3.20)
project(redux LANGUAGES CXX C)
include(CheckCXXSourceCompiles)

set(CMAKE_CXX_STANDARD 26)

find_package(Boost REQUIRED COMPONENTS program_options timer json)
find_package(GTest REQUIRED)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86|X86|amd64|AMD64)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
endif()

check_cxx_source_compiles("
    #if defined(__AVX512F__)
    int main() { return 0; }
    #else
    #error No avx512 support
    #endif
" IS_AVX)

check_cxx_source_compiles("
    #if defined(__ARM_NEON__) || defined(__ARM_NEON)
    int main() { return 0; }
    #else
    #error no neon support
    #endif
" IS_NEON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
if( IS_AVX )
    set(AVX_FLAGS "-mavx512f -mavx512vl -mavx512bw -mavx512dq -mavx512cd -funroll-loops --param max-unrolled-insns=500")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native ${AVX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native ${AVX_FLAGS}")
elseif (IS_NEON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else ()
    message(FATAL_ERROR "unsupported architecture (platforms available AVX-512, NEON")
endif ()

add_library(vector_reduce vector_reduce_double.c
         vector_reduce_float.c
         vector_reduce_int32.c
         vector_reduce_int64.c
         vector_reduce_simd.cpp
         vector_reduce_varargs.cpp
        vector_reduce_varargs_simd.cpp
)
##
##
##
add_executable(redux redux.cpp
        vector_simple.cpp
        vector_simple.hpp
        redux.cpp
        redux.hpp
        cpuname.cpp
        vector_reduce.h
        benchmark.cpp
        samplecounts.cpp
)


target_link_libraries(redux PRIVATE vector_reduce Boost::program_options Boost::timer Boost::json)

add_executable(unittests unittests.cpp)
target_link_libraries(unittests PRIVATE vector_reduce Boost::timer GTest::GTest GTest::Main)
