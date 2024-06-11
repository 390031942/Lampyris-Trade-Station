/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <vector>
#include <algorithm>

template<typename... Args>
class Delegate {
    /*
     * 函数指针的类型
    */ 
    using Func = void(*)(Args...);
public:
    /*
     * 添加监听函数
     * 参数{func}待添加的函数的地址
     */ 
    Delegate& operator+=(Func func) {
        m_funcList.push_back(func);
        return *this;
    }

    /*
     * 移除监听函数
     * 参数{func}待添加的函数的地址
     */
    Delegate& operator-=(Func func) {
        m_funcList.erase(std::remove_if(funcs.begin(), funcs.end(), [func](Func f) { return f == func; }), funcs.end());
        return *this;
    }

    /* 
     * 调用所有注册的函数
     */ 
    void operator()(Args... args) {
        for (auto& func : m_funcList) {
            func(args...);
        }
    }
private:
    std::vector<Func> m_funcList;
};