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