/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <windows.h>
#include <QDebug>

class SEHHandler {
public:
    SEHHandler() {}

    // ִ���ܱ����Ĵ���飬�������쳣
    template <typename Func>
    void executeProtected(Func func);
private:
    /*
     * �쳣�������������Ƿ����ִ��
    */ 
    static int handleSEHException(DWORD code);
};

// ִ���ܱ����Ĵ���飬�������쳣

template<typename Func>
inline void SEHHandler::executeProtected(Func func) {
    __try {
        func(); // ִ���ܱ����Ĵ���
    }
    __except (handleSEHException(GetExceptionCode())) {
        // �����쳣
        qDebug() << "An exception occurred with code:" << GetExceptionCode();
    }
}
