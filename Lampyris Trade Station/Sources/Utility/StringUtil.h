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
     * 正则表达式匹配IPv4地址
    */
    bool isValidIPV4(const QString& ip) {
        QRegularExpression regex("^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$");
        QRegularExpressionMatch match = regex.match(ip);

        // 如果匹配成功，则返回true，表示是有效的IP地址
        return match.hasMatch();
    }
} // end of namespace 'StringUtil'