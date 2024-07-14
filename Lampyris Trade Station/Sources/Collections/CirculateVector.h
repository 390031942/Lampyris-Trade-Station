/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <vector>
#include <iterator>
#include <iostream>
#include <cassert>

template <typename T, size_t defaultSize = 16>
class CirculateVector {
private:
    std::vector<T> data;
    size_t capacity;
    size_t start;
    size_t currentSize;
public:
    CirculateVector() {
        data.resize(defaultSize);
    }

    // 构造函数，初始化容量
    explicit CirculateVector(size_t cap) : capacity(cap), start(0), currentSize(0) {
        assert(cap > 0 && "Capacity must be greater than 0");
        data.resize(capacity);
    }

    // 添加元素到尾部
    void push_back(const T& value) {
        if (currentSize < capacity) {
            data[currentSize++] = value;
        }
        else {
            data[start] = value;
            start = (start + 1) % capacity;
        }
    }

    // 返回容器的大小
    size_t size() const {
        return currentSize < capacity ? currentSize : capacity;
    }

    // 返回容器的容量
    size_t max_size() const {
        return capacity;
    }

    // 返回容器的前元素
    T& front() {
        assert(currentSize > 0 && "Container is empty");
        return data[start];
    }

    const T& front() const {
        assert(currentSize > 0 && "Container is empty");
        return data[start];
    }

    // 返回容器的后元素
    T& back() {
        assert(currentSize > 0 && "Container is empty");
        size_t index = (start + currentSize - 1) % capacity;
        return data[index];
    }

    const T& back() const {
        assert(currentSize > 0 && "Container is empty");
        size_t index = (start + currentSize - 1) % capacity;
        return data[index];
    }

    // operator[] 操作符
    T& operator[](size_t index) {
        assert(index < size() && "Index out of bounds");
        return data[(start + index) % capacity];
    }

    const T& operator[](size_t index) const {
        assert(index < size() && "Index out of bounds");
        return data[(start + index) % capacity];
    }

    // 迭代器类
    class Iterator {
    private:
        CirculateVector* vec;
        size_t index;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(CirculateVector* v, size_t idx) : vec(v), index(idx) {}

        reference operator*() {
            return vec->data[(vec->start + index) % vec->capacity];
        }

        pointer operator->() {
            return &vec->data[(vec->start + index) % vec->capacity];
        }

        Iterator& operator++() {
            ++index;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return vec == other.vec && index == other.index;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin() {
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this, size());
    }

    // 常量迭代器类
    class ConstIterator {
    private:
        const CirculateVector* vec;
        size_t index;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;

        ConstIterator(const CirculateVector* v, size_t idx) : vec(v), index(idx) {}

        reference operator*() const {
            return vec->data[(vec->start + index) % vec->capacity];
        }

        pointer operator->() const {
            return &vec->data[(vec->start + index) % vec->capacity];
        }

        ConstIterator& operator++() {
            ++index;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const ConstIterator& other) const {
            return vec == other.vec && index == other.index;
        }

        bool operator!=(const ConstIterator& other) const {
            return !(*this == other);
        }
    };

    ConstIterator begin() const {
        return ConstIterator(this, 0);
    }

    ConstIterator end() const {
        return ConstIterator(this, size());
    }

    // 逆向迭代器类
    class ReverseIterator {
    private:
        CirculateVector* vec;
        size_t index;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        ReverseIterator(CirculateVector* v, size_t idx) : vec(v), index(idx) {}

        reference operator*() {
            size_t actualIndex = (vec->start + vec->capacity - index - 1) % vec->capacity;
            return vec->data[actualIndex];
        }

        pointer operator->() {
            size_t actualIndex = (vec->start + vec->capacity - index - 1) % vec->capacity;
            return &vec->data[actualIndex];
        }

        ReverseIterator& operator++() {
            ++index;
            return *this;
        }

        ReverseIterator operator++(int) {
            ReverseIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const ReverseIterator& other) const {
            return vec == other.vec && index == other.index;
        }

        bool operator!=(const ReverseIterator& other) const {
            return !(*this == other);
        }
    };

    ReverseIterator rbegin() {
        return ReverseIterator(this, 0);
    }

    ReverseIterator rend() {
        return ReverseIterator(this, size());
    }

    // 常量逆向迭代器类
    class ConstReverseIterator {
    private:
        const CirculateVector* vec;
        size_t index;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;

        ConstReverseIterator(const CirculateVector* v, size_t idx) : vec(v), index(idx) {}

        reference operator*() const {
            size_t actualIndex = (vec->start + vec->capacity - index - 1) % vec->capacity;
            return vec->data[actualIndex];
        }

        pointer operator->() const {
            size_t actualIndex = (vec->start + vec->capacity - index - 1) % vec->capacity;
            return &vec->data[actualIndex];
        }

        ConstReverseIterator& operator++() {
            ++index;
            return *this;
        }

        ConstReverseIterator operator++(int) {
            ConstReverseIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const ConstReverseIterator& other) const {
            return vec == other.vec && index == other.index;
        }

        bool operator!=(const ConstReverseIterator& other) const {
            return !(*this == other);
        }
    };

    ConstReverseIterator rbegin() const {
        return ConstReverseIterator(this, 0);
    }

    ConstReverseIterator rend() const {
        return ConstReverseIterator(this, size());
    }
};