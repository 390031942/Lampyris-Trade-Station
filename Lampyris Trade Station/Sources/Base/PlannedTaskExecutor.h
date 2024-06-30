/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "Singleton.h"
#include <Model/PlannedTask/PlannedTaskInfo.h>

// Qt Include(s)
#include <QDateTime>

// STD Include(s)
#include <unordered_map>

class PlannedTaskExecutor : public SingletonQObject<PlannedTaskExecutor> {
    Q_OBJECT
private:
    struct OnTimeTaskInfo {
        QList<QTime>          executeTimeList;
        std::function<void()> action;
    };

    struct DuringTimeTaskInfo {
        QTime                 startTime;
        QTime                 endTime;
        int                   intervalMs;
        std::function<void()> action;
        qint64                timeAccumulateMs;
    };
public:
    void checkAndExecuteTasks() {
        QDateTime nowDateTime = QDateTime::currentDateTime();
        QTime nowTime = nowDateTime.time();

        // 执行onLaunch任务
        for (auto& action : m_onLaunchActionList) {
            action();
        }
        m_onLaunchActionList.clear();

        // 执行onTime任务
        for (auto& onTimeTaskInfo : m_onTimeTaskInfoList) {
            for (auto& time : onTimeTaskInfo.executeTimeList) {
                if (nowTime > time) {
                    onTimeTaskInfo.action();
                    break;
                }
            }
        }

        // 执行duringTime任务
        for (auto& duringTimeTaskInfo : m_duringTimeTaskInfoList) {
            if (nowTime > duringTimeTaskInfo.startTime && duringTimeTaskInfo.endTime > nowTime) {
                if (!duringTimeTaskInfo.timeAccumulateMs) {
                    duringTimeTaskInfo.timeAccumulateMs = 0;
                }
                duringTimeTaskInfo.timeAccumulateMs += 1000; // 假设dTime为1秒
                if (duringTimeTaskInfo.timeAccumulateMs >= duringTimeTaskInfo.intervalMs) {
                    duringTimeTaskInfo.action();
                    duringTimeTaskInfo.timeAccumulateMs = 0;
                }
            }
        }
    }

    // 注册任务
    void registerTask(std::function<void()> action, const PlannedTaskInfo& attr) {
        if (attr.m_executeMode & ExecuteOnLaunch) {
            m_onLaunchActionList.append(action);
        }

        if (attr.m_executeMode & ExecuteDuringTime) {
            auto strs = attr.m_executeTime.split("-");
            if (strs.size() >= 2) {
                DuringTimeTaskInfo info;
                info.action = action;
                info.startTime = QTime::fromString(strs[0],"HH:mm");
                info.endTime = QTime::fromString(strs[1], "HH:mm");;
                info.intervalMs = attr.m_intervalMs;
                m_duringTimeTaskInfoList.append(info);
            }
        }

        if (attr.m_executeMode & ExecuteOnlyOnTime) {
            auto strs = attr.m_executeTime.split("&");
            OnTimeTaskInfo info;
            for(int i = 0; i < strs.size(); i++) {
                info.action = action;
                info.executeTimeList.append(QTime::fromString(strs[i], "HH:mm"));
            }
        }
    }

private:
    QList<OnTimeTaskInfo>                         m_onTimeTaskInfoList;
    QList<DuringTimeTaskInfo>                     m_duringTimeTaskInfoList;
    QList<std::function<void()>>                  m_onLaunchActionList;
    std::unordered_map<QObject*, PlannedTaskInfo> m_tasks;
};