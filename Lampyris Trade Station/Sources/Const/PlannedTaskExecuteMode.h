/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// ����ö������
enum PlannedTaskExecuteMode {
    // ֻ�ڹ涨��ʱ�䵽�˵�ʱ��ִ��
    ExecuteOnlyOnTime = 1,

    // ��������ʱ�Զ�ִ��һ��
    ExecuteOnLaunch = 2,

    // ��ʱ�䷶Χ�ڸ���һ���ļ��ִ��
    ExecuteDuringTime = 4,
};