/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

namespace StringUtil {
    /*
     * �ж� �����ַ����Ƿ����IPv4��ַ��ʽ
    */
    bool isValidIPV4(const QString& ip) {
        QRegularExpression regex("^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$");
        QRegularExpressionMatch match = regex.match(ip);

        // ���ƥ��ɹ����򷵻�true����ʾ����Ч��IP��ַ
        return match.hasMatch();
    }

    /*
     * �ж� �����ַ����Ƿ��������˿ںŸ�ʽ
    */
    bool isValidPort(const QString & portStr) {
        QRegularExpression regex("^([1-9][0-9]{0,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$");
        QRegularExpressionMatch match = regex.match(portStr);

        // ���ƥ��ɹ�������ת�����������1��65535֮�䣬�򷵻�true
        if (match.hasMatch()) {
            int port = portStr.toInt();
            return port >= 1 && port <= 65535;
        }
        return false;
    }

} // end of namespace 'StringUtil'