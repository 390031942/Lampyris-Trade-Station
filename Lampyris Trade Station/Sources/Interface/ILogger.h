/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

/*
 * 日志打印基类：
*/
class ILogger {
public:
    virtual void logInfo(const QString& message) = 0;

    virtual void logWarning(const QString& message) = 0;

    virtual void logError(const QString& message) = 0;

    virtual void logException(const QString& message) = 0;
};