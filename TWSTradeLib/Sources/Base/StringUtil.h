/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>

// STD Include(s)
#include <vector>
#include <string>

namespace TWSStringUtil {
static QString PrintVectorToQString(const std::vector<std::string>& vec) {
    QString result = "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        // 将std::string转换为QString
        QString item = QString::fromStdString(vec[i]);
        result += item;
        if (i < vec.size() - 1) {
            result += ",";
        }
    }
    result += "}";
    return result;
}

template<typename T>
requires std::is_base_of_v<TWSObject,T>
static QString PrintVectorToQString(const std::vector<T>& vec) {
    QString result = "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        QString item = vec[i].ToString();
        result += item;
        if (i < vec.size() - 1) {
            result += ",";
        }
    }
    result += "}";
    return result;
}

template<typename T>
static QString ToString(const T & t) {
    return QString();
}

template<typename T>
requires std::is_integral_v<T> || std::is_floating_point_v<T>
static QString ToString(const T& t) {
    return QString::number(t);
}

template<typename T1,typename T2>
static QString TupleToString(const std::tuple<T1, T2>& t);

template<>
static QString ToString<std::map<int, std::tuple<std::string, char>>>(const std::map<int, std::tuple<std::string, char>>& map) {
    QString result = "{";
    for (const auto& pair : map) {
        result += QString("[%1] = (%2);")
            .arg(pair.first)
            .arg(TupleToString(pair.second));
    }
    result += "}";
    return result;
}

template<typename T1, typename T2>
static QString TupleToString(const std::tuple<T1, T2>& t) {
    T1 t1;
    T2 t2;
    std::tie(t1, t2) = t;

    return QString("(%1,%2)").arg(ToString(t1)).arg(ToString(t2));
}
} // end of namespace "StringUtil"