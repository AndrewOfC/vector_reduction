cmake_minimum_required(VERSION 3.20)
project(redux)
include(CheckCXXSourceCompiles)

set(CMAKE_CXX_STANDARD 26)

find_package(Boost REQUIRED COMPONENTS program_options timer)
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
if( IS_AVX )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx512f")
elseif (IS_NEON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # todo support for rpi/linux platforms
else ()
    message(FATAL_ERROR "unsupported architecture (platforms available AVX-512, NEON")
endif ()


add_executable(redux main.cpp
        redux.cpp
        genericsum.cpp
        genericsum.hpp)

target_link_libraries(redux PRIVATE Boost::program_options Boost::timer)
