/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "SEHHandler.h"

// �쳣�������������Ƿ����ִ��
int SEHHandler::handleSEHException(DWORD code) {
    // �����쳣��������Ƿ����쳣
    // ���磬���������ﷵ�� EXCEPTION_EXECUTE_HANDLER ������ִ��
    // ���߷��� EXCEPTION_CONTINUE_SEARCH ����ϵͳ�����쳣
    switch (code) {
    case EXCEPTION_ACCESS_VIOLATION:
        // �������Υ���쳣
        break;
        // ������Ӹ�����쳣���ʹ���
    default:
        break;
    }
    return EXCEPTION_EXECUTE_HANDLER; // ͨ���������ֵ������ִ��
}
