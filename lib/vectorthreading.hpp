//
// Created by andrew on 11/19/26.
//

#pragma once
#ifndef REDUX_VECTORTHREADING_HPP
#define REDUX_VECTORTHREADING_HPP
#include <condition_variable>
#include <thread>

template<typename T>
class VectorThreading {
public:
    using ReductionFunction = T (*)(const T*, size_t, T);
    VectorThreading(int num_threads, ReductionFunction reduction) ;
    ~VectorThreading() ;

    void start();
    T reduce(const T*, size_t len, T initial = 0) ;

private:

    static void threadFunction(VectorThreading<T>* threading, int index);
    int busies = 0;
    bool ready = false ;
    bool stop = false ;
    T result ;
    int const num_threads;
    std::thread* threads = nullptr;
    std::mutex busy_mutex, ready_mutex;
    std::condition_variable busy_cv, ready_cv;
    ReductionFunction const reduction;

    const T **data_ptrs ;// one per thread
    size_t *lengths ;// one per thread
    T *results ;

};

#endif //REDUX_VECTORTHREADING_HPP
