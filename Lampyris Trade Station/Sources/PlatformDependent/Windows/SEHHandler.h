/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <windows.h>
#include <QDebug>

class SEHHandler {
public:
    SEHHandler() {}

    // 执行受保护的代码块，并处理异常
    template <typename Func>
    void executeProtected(Func func);
private:
    /*
     * 异常处理函数，返回是否继续执行
    */ 
    static int handleSEHException(DWORD code);
};

// 执行受保护的代码块，并处理异常

template<typename Func>
inline void SEHHandler::executeProtected(Func func) {
    __try {
        func(); // 执行受保护的代码
    }
    __except (handleSEHException(GetExceptionCode())) {
        // 处理异常
        qDebug() << "An exception occurred with code:" << GetExceptionCode();
    }
}
