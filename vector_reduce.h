//
// Created by andrew on 10/21/26.
//

#pragma once
#ifndef REDUX_VECTOR_REDUCE_H
#define REDUX_VECTOR_REDUCE_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

double vector_reduce_double(const double *src, size_t len, double initial);
float vector_reduce_float(const float *src, size_t len, float initial);
int8_t vector_reduce_int8(const int8_t *src, size_t len, int8_t initial);
int16_t vector_reduce_int16(const int16_t *src, size_t len, int16_t initial);
int32_t vector_reduce_int32(const int32_t *src, size_t len, int32_t initial);
int64_t vector_reduce_int64(const int64_t *src, size_t len, int64_t initial);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/*
 * C++ wrapper functions to leverage function overloading for different types
 */
inline double vector_reduce(const double *src, size_t len, double initial = 0.0 )
{
    return vector_reduce_double(src, len, initial);
}
inline float vector_reduce(const float *src, size_t len, float initial = 0.0 )
{
    return vector_reduce_float(src, len, initial);
}
inline int8_t vector_reduce(const int8_t *src, size_t len, int8_t initial = 0)
{
    return vector_reduce_int8(src, len, initial);
}
inline int16_t vector_reduce(const int16_t *src, size_t len, int16_t initial = 0)
{
    return vector_reduce_int16(src, len, initial);
}
inline int32_t vector_reduce(const int32_t *src, size_t len, int32_t initial = 0)
{
    return vector_reduce_int32(src, len, initial);
}
inline int64_t vector_reduce(const int64_t *src, size_t len, int64_t initial = 0)
{
    return vector_reduce_int64(src, len, initial);
}

#endif

#endif //REDUX_VECTOR_REDUCE_H
