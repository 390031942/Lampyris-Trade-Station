/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QTimer>
#include <QElapsedTimer>

// STD Include(s)
#include <functional>
#include <algorithm>
#include <vector>
#include <unordered_map>

// Project Include(s)
#include "Singleton.h"

class CallTimer:public Singleton<CallTimer> {
private:
    class DelayHandler {
        typedef std::function<void()> Callback;
    public:
        enum class Type {
            // 间隔时间触发
            Interval = 0,

            // 间隔Tick次数触发
            Tick = 1,
        } type;

        Callback      action;
        int           repeatTime;
        int           tickCounter;
        QElapsedTimer timer;
        union {
            int delayMs;
            int delayTick;
        };
    };

    typedef std::unordered_map<int, DelayHandler> DelayHandlerMap;
public:
                     CallTimer();
    int              setInterval(std::function<void()> action, int delayMs, int repeatTime = -1);
    void             clearTimer(int id);
    void             tick();
private:
    int              m_increaseKey = 0;
    DelayHandlerMap  m_id2DelayHandlerMap;
    QMutex           m_mutex;
};