/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QDateTime>
#include <QString>

// Boost Include(s)
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/access.hpp>

// STD Include(s)
#include <memory>

class KLineData {
public:
    // 日期
    QDateTime   date;

    // K线分析周期(单位:s)，如果值为24*3600 = 86400,说明k线的周期是日k
    int         cycle;

    float       openPrice;
    float       closePrice;
    float       highestPrice;
    float       lowestPrice;
    float       volume;
    float       money;
    float       amplitude;
    float       percentage;
    float       priceChange;
    float       turnOverRate;
    float       lastClosePrice;

    // 在数组中的索引，方便求前驱和后继
    int         indexInList;

    // 序列化函数
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
    }
};

class SecurityData {
private:
    QString code;
    QString name;
    // 交易所名称
    QString exchange;
    // 货币类型
    QString currency;

    friend class QuoteDatabase;
};

typedef std::shared_ptr<SecurityData> SecurityDataPtr;

class QuoteDataProvider {

};

/*
 * 行情类型，不同的行情类型 需要实现对应的 QuoteDataProvider
*/
enum class QuoteDataType {

};

/*
 * 指数简要行情信息
*/
struct IndexBriefQuoteData {
    QString code;
    QString name;
    float   price;
    float   change;
    float   percentage;
};