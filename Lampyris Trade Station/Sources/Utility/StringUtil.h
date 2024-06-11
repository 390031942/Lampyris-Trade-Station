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
     * 判断 输入字符串是否符合IPv4地址格式
    */
    bool isValidIPV4(const QString& ip) {
        QRegularExpression regex("^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$");
        QRegularExpressionMatch match = regex.match(ip);

        // 如果匹配成功，则返回true，表示是有效的IP地址
        return match.hasMatch();
    }

    /*
     * 判断 输入字符串是否符合网络端口号格式
    */
    bool isValidPort(const QString & portStr) {
        QRegularExpression regex("^([1-9][0-9]{0,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$");
        QRegularExpressionMatch match = regex.match(portStr);

        // 如果匹配成功，并且转换后的数字在1到65535之间，则返回true
        if (match.hasMatch()) {
            int port = portStr.toInt();
            return port >= 1 && port <= 65535;
        }
        return false;
    }

} // end of namespace 'StringUtil'