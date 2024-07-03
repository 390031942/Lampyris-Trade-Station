/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "CallTimer.h"
#include <Core/Application.h>

CallTimer::CallTimer() {
    Application::addTickFunc([=]() {
        this->tick();
    });
}

int CallTimer::setInterval(std::function<void()> action, int delayMs, int repeatTime) {
    QMutexLocker locker(&m_mutex);

    int id = m_increaseKey++;
    m_id2DelayHandlerMap[id] = DelayHandler{ DelayHandler::Type::Interval, action, delayMs, repeatTime };
    return id;
}

void CallTimer::clearTimer(int id) {
    QMutexLocker locker(&m_mutex);
    m_id2DelayHandlerMap.erase(id);
}

void CallTimer::tick() {
    QMutexLocker locker(&m_mutex);
    for (auto it = m_id2DelayHandlerMap.begin(); it != m_id2DelayHandlerMap.end();) {
        DelayHandler& handler = (*it).second;

        if (handler.type == DelayHandler::Type::Interval) {
            if (!handler.timer.elapsed() >= handler.delayMs) {
                handler.action();
                handler.timer.restart();

                if (handler.repeatTime != -1) {
                    if (--handler.repeatTime == 0) {
                        it = m_id2DelayHandlerMap.erase(it);
                        continue;
                    }
                }
            }
        }
        else {
            if (handler.tickCounter >= handler.delayTick) {
                handler.action();
                handler.tickCounter = 0;

                if (handler.repeatTime != -1) {
                    if (--handler.repeatTime == 0) {
                        it = m_id2DelayHandlerMap.erase(it);
                        continue;
                    }
                }
            }
            else {
                handler.tickCounter++;
            }
        }
        ++it;
    }
}
