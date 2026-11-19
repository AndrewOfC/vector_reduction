//
// Created by andrew on 11/19/26.
//

#include "vectorthreading.hpp"

template<typename T>
VectorThreading<T>::VectorThreading(int num_threads, ReductionFunction reduction)
: num_threads(num_threads), reduction(reduction) {
    results = new T[num_threads];
    lengths = new size_t[num_threads];
    data_ptrs = new const T*[num_threads];
}

template<typename T>
VectorThreading<T>::~VectorThreading()
{
    {
        std::lock_guard<std::mutex> lock(ready_mutex);
        stop = true;
        ready_cv.notify_all();
    }
    if ( threads)
    {
        for (int i = 0; i < num_threads; ++i) {
            threads[i].join();
        }
    }

    delete[] threads;
    delete[] lengths;
    delete[] results;
    delete[] data_ptrs;
}

template<typename T>
void VectorThreading<T>::start() {
    delete [] threads ;
    threads = new std::thread[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(&VectorThreading::threadFunction, this, i);
    }
}

template<typename T>
void VectorThreading<T>::threadFunction(VectorThreading<T>* threading, int index)
{
    // Thread work goes here
    for ( ;; ) {
        {
            std::unique_lock<std::mutex> lock(threading->ready_mutex);
            while (!threading->ready) {
                threading->ready_cv.wait(lock);
            }
            threading->busies += 1  ;
            if ( threading->stop )
                return ;
        }
        /*
         * the work
         */
        threading->results[index] = threading->reduction(threading->data_ptrs[index], threading->lengths[index], 0);

        threading->busies -= 1 ;
        threading->busy_cv.notify_all();
    }
}

template<typename T>
T VectorThreading<T>::reduce(const T* data, size_t len, T initial)
{
    while ( busies != 0 ) {
        std::unique_lock<std::mutex> lock(busy_mutex);
        busy_cv.wait(lock);
    }

    size_t chunk_size = len / num_threads;
    int i = 0 ;
    for(  i = 0 ; i < num_threads ; i++ ) {
        data_ptrs[i] = nullptr;
        lengths[i] = 0;
    }
    i = 0 ;
    auto nptr = data ;
    while ( len ) {
        if ( len >= chunk_size )
            lengths[i] = chunk_size;
        else
            lengths[i] = len;

        data_ptrs[i] = nptr ;

        len -= lengths[i] ;
        nptr += lengths[i] ;
        i++;
    }

    {
        std::lock_guard<std::mutex> lock(ready_mutex);
        ready = true;
        ready_cv.notify_all();
    }

    // Wait for all threads to finish
    {
        std::unique_lock<std::mutex> lock(busy_mutex);
        while (busies) {
            busy_cv.wait(lock);
        }
    }

    // Combine results from all threads
    for ( i = 0; i < num_threads; ++i) {
        initial += results[i];
    }

    return initial;
}

template class VectorThreading<double> ;