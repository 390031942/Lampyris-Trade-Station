/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "SEHHandler.h"

// 异常处理函数，返回是否继续执行
int SEHHandler::handleSEHException(DWORD code) {
    // 根据异常代码决定是否处理异常
    // 例如，可以在这里返回 EXCEPTION_EXECUTE_HANDLER 来继续执行
    // 或者返回 EXCEPTION_CONTINUE_SEARCH 来让系统处理异常
    switch (code) {
    case EXCEPTION_ACCESS_VIOLATION:
        // 处理访问违规异常
        break;
        // 可以添加更多的异常类型处理
    default:
        break;
    }
    return EXCEPTION_EXECUTE_HANDLER; // 通常返回这个值来继续执行
}
