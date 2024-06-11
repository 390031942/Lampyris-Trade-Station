/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <vector>
#include <algorithm>

template<typename... Args>
class Delegate {
    /*
     * ����ָ�������
    */ 
    using Func = void(*)(Args...);
public:
    /*
     * ��Ӽ�������
     * ����{func}����ӵĺ����ĵ�ַ
     */ 
    Delegate& operator+=(Func func) {
        m_funcList.push_back(func);
        return *this;
    }

    /*
     * �Ƴ���������
     * ����{func}����ӵĺ����ĵ�ַ
     */
    Delegate& operator-=(Func func) {
        m_funcList.erase(std::remove_if(funcs.begin(), funcs.end(), [func](Func f) { return f == func; }), funcs.end());
        return *this;
    }

    /* 
     * ��������ע��ĺ���
     */ 
    void operator()(Args... args) {
        for (auto& func : m_funcList) {
            func(args...);
        }
    }
private:
    std::vector<Func> m_funcList;
};