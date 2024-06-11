/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

/*
 * ��־��ӡ���ࣺ
*/
class ILogger {
public:
    virtual void LogInfo(const QString& message) = 0;

    virtual void LogWarning(const QString& message) = 0;

    virtual void LogError(const QString& message) = 0;

    virtual void LogException(const QString& message) = 0;
};