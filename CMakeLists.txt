cmake_minimum_required(VERSION 3.20)
project(redux LANGUAGES CXX C)
include(CheckCXXSourceCompiles)

set(CMAKE_CXX_STANDARD 26)

find_package(Boost REQUIRED COMPONENTS program_options timer json)
find_package(GTest REQUIRED)

set(SVE2_FLAGS "-march=armv8.5-a+sve -msve-vector-bits=256")

set(__SAVE_C_FLAGS "${CMAKE_C_FLAGS}")
set(__SAVE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86|X86|amd64|AMD64)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SVE2_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SVE2_FLAGS}")
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

check_cxx_source_compiles("
    #if defined(__ARM_FEATURE_SVE)
    int main() { return 0; }
    #else
    #error no sve2 support
    #endif
" IS_SVE2)

set(CMAKE_C_FLAGS "${__SAVE_C_FLAGS}" )
set(CMAKE_CXX_FLAGS "${__SAVE_CXX_FLAGS}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
if( IS_AVX )
    set(AVX_FLAGS "-mavx512f -mavx512vl -mavx512bw -mavx512dq -mavx512cd -funroll-loops --param max-unrolled-insns=500")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native ${AVX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native ${AVX_FLAGS}")
elseif( IS_SVE2 )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SVE2_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${SVE2_FLAGS}")
elseif (IS_NEON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else ()
    message(FATAL_ERROR "unsupported architecture (platforms available AVX-512, NEON")
endif ()

add_subdirectory(lib)

# add_executable(sve2 sve2.cpp)

##
##
##
add_executable(redux redux.cpp
        redux.cpp
        redux.hpp
        cpuname.cpp
        benchmark.cpp
        samplecounts.cpp
)
target_include_directories(redux PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(redux PRIVATE vector_reduce Boost::program_options Boost::timer Boost::json)


add_executable(unittests unittests.cpp)
target_include_directories(unittests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(unittests PRIVATE vector_reduce Boost::timer GTest::GTest GTest::Main)
