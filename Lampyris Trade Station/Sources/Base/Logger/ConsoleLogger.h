/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <exception>
#include <iostream>

// QT Include(s)
#include <QTextStream>
#include <QColor>
#include <QMutex>
#include <QMutexLocker>

// Project Include(s)
#include <Const/LogLevel.h>
#include <Interface/ILogger.h>

// Windows Include(s)
#include <Windows.h>

// Boost Include(s)
#include <boost/stacktrace.hpp>

class ConsoleLogger:public ILogger {
public:
    void     logInfo(const char* message);
    void     logWarning(const char* message);
    void     logError(const char* message);
    void     logException(const std::exception& exception);
    void     logInfoFormat(const char* format, ...);
    void     logWarningFormat(const char* format, ...);
    void     logErrorFormat(const char* format, ...);
private:
             ConsoleLogger();
    virtual ~ConsoleLogger();
    void     logMessage(LogLevel logLevel, const char* message);
    HANDLE   m_handle;
};