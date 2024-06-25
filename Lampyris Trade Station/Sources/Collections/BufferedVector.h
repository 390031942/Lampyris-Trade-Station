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

template<typename T>
class BufferedVector {
public:
    void                    push_back(const T& value);
    void                    iterate(std::function<void(const T&)> func) const;
    void                    clear();
    void                    finish();
    const std::vector<T>&   getData() const;
    auto                    begin() const -> decltype(std::begin(getData()));
    auto                    end() const -> decltype(std::end(getData()));
private:
    std::vector<T>          m_data;
    std::vector<T>          m_buffer;
    std::mutex              m_mutex;
    std::condition_variable m_cv;
    bool                    m_finished = false;
};

template<typename T>
void BufferedVector<T>::push_back(const T& value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_buffer.push_back(value);
}

template<typename T>
void BufferedVector<T>::iterate(std::function<void(const T&)> func) const {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this] { return m_finished; }); // 等待数据填充完成

    // 复制数据以进行迭代，避免在迭代期间修改
    std::vector<T> copy = m_data;
    lock.unlock();
    m_cv.notify_all(); // 通知其他线程迭代完成

    for (const T& value : copy) {
        func(value);
    }
}

template<typename T>
void BufferedVector<T>::clear() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_data.clear();
    m_buffer.clear();
    m_finished = false;
}

template<typename T>
void BufferedVector<T>::finish() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::swap(m_data, m_buffer); // 交换两个vector
    m_finished = true;
    m_cv.notify_all(); // 通知所有等待的迭代器
}

// 返回指向data的常量迭代器
template<typename T>
const std::vector<T>& BufferedVector<T>::getData() const {
    return m_data;
}

template<typename T>
auto BufferedVector<T>::begin() const -> decltype(std::begin(getData())) {
    return std::begin(getData());
}

template<typename T>
auto BufferedVector<T>::end() const -> decltype(std::end(getData())) {
    return std::end(getData());
}
