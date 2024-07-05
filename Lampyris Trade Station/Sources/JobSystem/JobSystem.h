/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include()
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <atomic>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <coroutine>

template<typename T>
struct Generator {
    struct promise_type;
    using Handle = std::coroutine_handle <promise_type>;

    struct promise_type {
        T                   m_value;
        std::exception_ptr  m_exception;
        Generator           get_return_object();
        std::suspend_always initial_suspend();
        std::suspend_always final_suspend() noexcept;
        void                unhandled_exception();
        std::suspend_always yield_value(T value);
        void                return_void();
    };
           Generator(std::coroutine_handle<promise_type> handle);
          ~Generator();
    bool   move_next();
    T      current_value();
    Handle m_handle;
};

class JobHandle {
public:
                                   JobHandle(std::vector<std::future<void>>&& futures);
    bool                           isDone() const;
    void                           wait();
    void                           setProgress(float progress);
    float                          getProgress() const;
private:
    std::vector<std::future<void>> m_futures;
    std::atomic<float>             m_progress;
};

class JobSystem {
public:
                                      JobSystem(size_t numThreads);
                                     ~JobSystem();
    JobHandle                         createJob(std::function<Generator<float>(JobHandle&)> job);
    JobHandle                         createLoopJob(std::function<Generator<float>(int, JobHandle&)> job, int start, int end);
private:
    std::vector<std::thread>          m_workers;
    std::queue<std::function<void()>> m_jobs;
    std::mutex                        m_queueMutex;
    std::condition_variable           m_condition;
    bool                              m_stop;
};


template<typename T>
Generator<T> Generator<T>::promise_type::get_return_object() {
    return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
}

template<typename T>
std::suspend_always Generator<T>::promise_type::initial_suspend() { return {}; }

template<typename T>
std::suspend_always Generator<T>::promise_type::final_suspend() noexcept { return {}; }

template<typename T>
void Generator<T>::promise_type::unhandled_exception() {
    m_exception = std::current_exception();
}

template<typename T>
std::suspend_always Generator<T>::promise_type::yield_value(T value) {
    m_value = value;
    return {};
}

template<typename T>
void Generator<T>::promise_type::return_void() {}

template<typename T>
Generator<T>::Generator(std::coroutine_handle<promise_type> handle) : m_handle(handle) {}

template<typename T>
Generator<T>::~Generator() {
    if (m_handle) m_handle.destroy();
}

template<typename T>
bool Generator<T>::move_next() {
    m_handle.resume();
    if (m_handle.done()) {
        if (m_handle.promise().exception_) {
            std::rethrow_exception(m_handle.promise().exception_);
        }
        return false;
    }
    return true;
}

template<typename T>
T Generator<T>::current_value() {
    return m_handle.promise().value_;
}

/* Example: 
 * Generator<float> exampleJob(JobHandle& handle) {
 *     for (int i = 0; i < 5; ++i) {
 *         co_yield i * 20.0f;
 *     }
 * }
 * 
 * Generator<float> exampleLoopJob(int index, JobHandle& handle) {
 *     for (int i = 0; i < 3; ++i) {
 *         co_yield index * 10.0f + i * 5.0f;
 *     }
 * }
 * int main() {
 *     JobSystem jobSystem(4);
 * 
 *     JobHandle handle1 = jobSystem.createJob(exampleJob);
 *     JobHandle handle2 = jobSystem.createLoopJob(exampleLoopJob, 0, 10);
 *
 *     handle1.wait();
 *     handle2.wait();
 *
 *     std::cout << "all completed" << std::endl;
 *
 *     return 0;
 * }
*/