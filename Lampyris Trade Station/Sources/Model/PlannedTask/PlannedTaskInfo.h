/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Const/PlannedTaskExecuteMode.h>

// QT Include(s)
#include <QString>

class PlannedTaskInfo {
public:
    PlannedTaskInfo(PlannedTaskExecuteMode mode,
                    const QString& time = "",
                    int interval = 0): 
        m_executeTime(time), m_intervalMs(interval), m_executeMode(mode) {}

private:
    QString                m_executeTime;
    int                    m_intervalMs;
    PlannedTaskExecuteMode m_executeMode;

    friend class PlannedTaskExecutor;
};