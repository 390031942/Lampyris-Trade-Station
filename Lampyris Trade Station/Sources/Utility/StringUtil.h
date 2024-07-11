/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
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
    static bool isValidIPV4(const QString& ip) {
        QRegularExpression regex("^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$");
        QRegularExpressionMatch match = regex.match(ip);

        // ���ƥ��ɹ����򷵻�true����ʾ����Ч��IP��ַ
        return match.hasMatch();
    }
} // end of namespace 'StringUtil'