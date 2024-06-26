/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <vector>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <functional>

template<typename T, typename Alloc = std::allocator<T>>
class BufferedVector {
public:
    void                    push_back(const T& value);
    void                    iterate(std::function<void(const T&)> func) const;
    void                    clear();
    void                    finish();
    const std::vector<T,Alloc>&   getData() const;
    auto                    begin() const -> decltype(std::begin(getData()));
    auto                    end() const -> decltype(std::end(getData()));
private:
    std::vector<T,Alloc>    m_data;
    std::vector<T,Alloc>    m_buffer;
    std::mutex              m_mutex;
    std::condition_variable m_cv;
    bool                    m_finished = false;
};

template<typename T, typename Alloc>
void BufferedVector<T,Alloc>::push_back(const T& value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_buffer.push_back(value);
}

template<typename T, typename Alloc>
void BufferedVector<T,Alloc>::iterate(std::function<void(const T&)> func) const {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this] { return m_finished; }); // 等待数据填充完成

    // 复制数据以进行迭代，避免在迭代期间修改
    std::vector<T,Alloc> copy = m_data;
    lock.unlock();
    m_cv.notify_all(); // 通知其他线程迭代完成

    for (const T& value : copy) {
        func(value);
    }
}

template<typename T, typename Alloc>
void BufferedVector<T,Alloc>::clear() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_data.clear();
    m_buffer.clear();
    m_finished = false;
}

template<typename T, typename Alloc>
void BufferedVector<T,Alloc>::finish() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::swap(m_data, m_buffer); // 交换两个vector
    m_finished = true;
    m_cv.notify_all(); // 通知所有等待的迭代器
}

// 返回指向data的常量迭代器
template<typename T, typename Alloc>
const std::vector<T,Alloc>& BufferedVector<T,Alloc>::getData() const {
    return m_data;
}

template<typename T, typename Alloc>
auto BufferedVector<T,Alloc>::begin() const -> decltype(std::begin(getData())) {
    return std::begin(getData());
}

template<typename T, typename Alloc>
auto BufferedVector<T,Alloc>::end() const -> decltype(std::end(getData())) {
    return std::end(getData());
}
