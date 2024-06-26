/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <xmemory>

template<typename T, typename Alloc = std::allocator<T>>
class CircularQueue {
public:
    explicit CircularQueue(size_t size);
            ~CircularQueue();
             CircularQueue(CircularQueue&& other) noexcept;
             CircularQueue& operator=(CircularQueue&& other) noexcept;

    void     enqueue(const T& item);
    void     dequeue();
    T&       front();
    bool     isEmpty() const;
    bool     isFull() const;
    size_t   size() const;
private:
    void     destroyQueue();

    T*       m_queue;   
    size_t   m_front;  
    size_t   m_rear;   
    size_t   m_capacity;
    size_t   m_count;   
    Alloc    m_alloc;   
};

template<typename T, typename Alloc>
CircularQueue<T, Alloc>::CircularQueue(size_t size) 
    : m_capacity(size), m_front(0), m_rear(-1), m_count(0) {
    m_queue = m_alloc.allocate(size);  // 使用分配器分配内存
}

template<typename T, typename Alloc>
CircularQueue<T, Alloc>::~CircularQueue() {
    for (size_t i = 0; i < m_count; ++i) {
        m_alloc.destroy(&m_queue[(m_front + i) % m_capacity]);  // 销毁元素
    }
    m_alloc.deallocate(m_queue, m_capacity);  // 释放内存
}

template<typename T, typename Alloc>
CircularQueue<T, Alloc>::CircularQueue(CircularQueue&& other) noexcept
    : m_queue(other.m_queue), m_front(other.m_front), m_rear(other.m_rear), m_capacity(other.m_capacity),
    m_count(other.m_count), m_alloc(std::move(other.m_alloc)) {
    other.m_queue = nullptr;
    other.m_front = 0;
    other.m_rear = -1;
    other.m_capacity = 0;
    other.m_count = 0;
}

template<typename T, typename Alloc>
CircularQueue<T,Alloc>& CircularQueue<T, Alloc>::operator=(CircularQueue&& other) noexcept {
    if (this != &other) {
        destroyQueue();
        m_queue = other.m_queue;
        m_front = other.m_front;
        m_rear = other.m_rear;
        m_capacity = other.m_capacity;
        m_count = other.m_count;
        m_alloc = std::move(other.m_alloc);
        other.m_queue = nullptr;
        other.m_front = 0;
        other.m_rear = -1;
        other.m_capacity = 0;
        other.m_count = 0;
    }
}

template<typename T, typename Alloc>
void CircularQueue<T, Alloc>::enqueue(const T& item) {
    if (isFull()) {
        throw std::runtime_error("Queue is full");
    }
    m_rear = (m_rear + 1) % m_capacity;
    m_alloc.construct(&m_queue[m_rear], item);  // 使用分配器构造元素
    ++m_count;
}

template<typename T, typename Alloc>
void CircularQueue<T, Alloc>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    m_alloc.destroy(&m_queue[m_front]);  // 销毁元素
    m_front = (m_front + 1) % m_capacity;
    --m_count;
}

template<typename T, typename Alloc>
T& CircularQueue<T, Alloc>::front() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return m_queue[m_front];
}

template<typename T, typename Alloc>
bool CircularQueue<T, Alloc>::isEmpty() const {
    return m_count == 0;
}

template<typename T, typename Alloc>
bool CircularQueue<T, Alloc>::isFull() const {
    return m_count == m_capacity;
}

template<typename T, typename Alloc>
size_t CircularQueue<T, Alloc>::size() const {
    return m_count;
}

template<typename T, typename Alloc>
void CircularQueue<T, Alloc>::destroyQueue() {
    for (size_t i = 0; i < m_count; ++i) {
        m_alloc.destroy(&m_queue[(m_front + i) % m_capacity]);
    }
}
