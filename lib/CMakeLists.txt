cmake_minimum_required(VERSION 3.20)

set(LIB_FILES
    vector_reduce.h
    vector_reduce_double.c
    vector_reduce_float.c
    vector_reduce_int32.c
    vector_reduce_int64.c
    vector_reduce_simple.cpp
    vector_reduce_simd.cpp
    vector_reduce_varargs.cpp
    vector_reduce_varargs_simd.cpp
)

if(IS_SVE2)
set(LIB_FILES ${LIB_FILES}
        sve_reduce_double.c
        sve_reduce_float.c
        sve_reduce_int32.c
        sve_reduce_int32.c
        sve_support.h
)
endif ()

add_library(vector_reduce ${LIB_FILES})

install(TARGETS vector_reduce LIBRARY DESTINATION lib)
install(FILES vector_reduce.h DESTINATION include)
