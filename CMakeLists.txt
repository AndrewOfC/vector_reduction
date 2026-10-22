cmake_minimum_required(VERSION 3.20)
project(redux LANGUAGES CXX C)
include(CheckCXXSourceCompiles)

set(CMAKE_CXX_STANDARD 26)

find_package(Boost REQUIRED COMPONENTS program_options timer)
find_package(GTest REQUIRED)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86|X86|amd64|AMD64)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx512f")
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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx512f -mavx512vl")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}     -mavx512f -mavx512vl")
elseif (IS_NEON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else ()
    message(FATAL_ERROR "unsupported architecture (platforms available AVX-512, NEON")
endif ()

add_library(vector_reduce vector_reduce_double.c
         vector_reduce_float.c
         vector_reduce_int32.c
         vector_reduce_int64.c
)
##
##
##
add_executable(redux main.cpp
        genericsum.cpp
        genericsum.hpp
        vector_reduce.h)


target_link_libraries(redux PRIVATE vector_reduce Boost::program_options Boost::timer)

add_executable(unittests unittests.cpp)
target_link_libraries(unittests PRIVATE vector_reduce Boost::timer GTest::GTest GTest::Main)