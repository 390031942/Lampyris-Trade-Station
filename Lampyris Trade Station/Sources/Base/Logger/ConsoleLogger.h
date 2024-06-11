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
    void     LogInfo(const char* message);
             
    void     LogWarning(const char* message);
             
    void     LogError(const char* message);
             
    void     LogException(const std::exception& exception);
             
    void     LogInfoFormat(const char* format, ...);
             
    void     LogWarningFormat(const char* format, ...);
             
    void     LogErrorFormat(const char* format, ...);
private:
             ConsoleLogger();

    virtual ~ConsoleLogger();

    void     LogMessage(LogLevel logLevel, const char* message);

    HANDLE   m_handle;
};