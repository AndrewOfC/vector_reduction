cmake_minimum_required(VERSION 4.3)
project(redux)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -mavx512f")



add_executable(redux main.cpp
        redux.cpp)
