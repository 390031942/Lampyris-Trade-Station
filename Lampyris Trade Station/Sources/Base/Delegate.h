/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <vector>
#include <algorithm>
#include <functional>

template<typename... Args>
class Delegate {
    /*
     * ����ָ�������
    */ 
    using Func = std::function<void(Args...)>;
    /*
     * ����һ���������ڱ�ʶ����
    */ 
    using Identifier = int; 

    struct FuncEntry {
        Func       func;
        Identifier id;
    };

public:
    /*
     * ��Ӽ�������
     * ����{func}:����ӵĺ����ĵ�ַ
     * ����ֵ:����Ψһ��ʶ��
     */ 
    Identifier operator+=(Func func) {
        Identifier newId = m_increment++;
        m_funcList.push_back(FuncEntry{ std::move(func), newId});
        return newId;
    }
    /*
     * �Ƴ���������
     * ����{Identifier}:����Ψһ��ʶ��
     */
    bool operator-=(Identifier id) {
        auto it = std::remove_if(m_funcList.begin(), m_funcList.end(), [id](const FuncEntry& entry) { return entry.id == id; });
        if (it != m_funcList.end()) {
            m_funcList.erase(it, m_funcList.end());
            return true;
        }
        return false;
    }
    /* 
     * ��������ע��ĺ���
     */ 
    void operator()(Args... args) {
        for (auto& funcEntry : m_funcList) {
            funcEntry.func(args...);
        }
    }
private:
    std::vector<FuncEntry> m_funcList;
    int                    m_increment = 0;
};