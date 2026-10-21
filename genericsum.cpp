//
// Created by ANDREW PAGE on 10/19/26.
//

#include "genericsum.hpp"

template<typename T>
T genericSum(T *src, size_t len, T initial)
{
    for(size_t i = 0; i < len; i++)
    {
        initial += src[i];
    }
    return initial;
}

template double genericSum<double>(double *src, size_t len, double initial);
template float genericSum<float>(float *src, size_t len, float initial);
template int8_t genericSum<int8_t>(int8_t *src, size_t len, int8_t initial);
template int16_t genericSum<int16_t>(int16_t *src, size_t len, int16_t initial);
template int32_t genericSum<int32_t>(int32_t *src, size_t len, int32_t initial);
template int64_t genericSum<int64_t>(int64_t *src, size_t len, int64_t initial);
