/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// 定义枚举类型
enum PlannedTaskExecuteMode {
    // 只在规定的时间到了的时候执行
    ExecuteOnlyOnTime = 1,

    // 启动程序时自动执行一次
    ExecuteOnLaunch = 2,

    // 在时间范围内根据一定的间隔执行
    ExecuteDuringTime = 4,
};