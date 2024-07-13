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
#include <map>

// Project Include(s)
#include <Base/SerializeMacro.h>
#include <Base/SerializableSingleton.h>

class KLineData {
    LAMPYRIS_DECLARE_SERILIZATION(KLineData);
public:
    // 日期时间,如果周期是1day，那么dateTime记录了年月日，否则则会精确到 具体周期的开始时间
    QDateTime   dateTime;

    // K线周期(单位:s)，如果值为24*3600 = 86400,说明k线的周期是日k
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
    float       lastClosePrice;

    // 在数组中的索引，方便求前驱和后继
    int         indexInList;
};
typedef std::shared_ptr<KLineData> KLineDataPtr;

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(KLineData)
{
    LAMPYRIS_SERIALIZATION_FIELD(dateTime);
    LAMPYRIS_SERIALIZATION_FIELD(openPrice);
    LAMPYRIS_SERIALIZATION_FIELD(closePrice);
    LAMPYRIS_SERIALIZATION_FIELD(highestPrice);
    LAMPYRIS_SERIALIZATION_FIELD(lowestPrice);
    LAMPYRIS_SERIALIZATION_FIELD(volume);
    LAMPYRIS_SERIALIZATION_FIELD(money);
    LAMPYRIS_SERIALIZATION_FIELD(amplitude);
    LAMPYRIS_SERIALIZATION_FIELD(percentage);
    LAMPYRIS_SERIALIZATION_FIELD(priceChange);
    LAMPYRIS_SERIALIZATION_FIELD(lastClosePrice);
}
 LAMPYRIS_SERIALIZATION_IMPL_END

enum QuoteCycleEnum {
    OneMinute = 0,
    FiveMinute = 1,
    FifteenMinute = 2,
    HalfHour = 3,
    Hour = 4,
    Day = 5,
    Week = 6,
    Month = 7,
    Year = 8,
    Count = Year,
};

struct TickByTickData {
    long  timestamp;
    float price;
    float count;
};

class RealTimeQuoteData {
public:
	TickByTickData getLastTickByTick() const { return TickByTickData(); }

	KLineData* realTimerBar() { return &this->m_realTimeBar; }

	const KLineData* realTimerBar() const { return &this->m_realTimeBar; }
private:
	KLineData m_realTimeBar;
};

class HistoryTimeQuoteData:public ISerializable {
    LAMPYRIS_DECLARE_SERILIZATION(HistoryTimeQuoteData);
public:
    std::vector<KLineDataPtr> query(QuoteCycleEnum cycle, 
                                    const QDateTime& startDateTime, 
                                    const QDateTime& endDateTime = QDateTime()) {
        typedef std::pair<const QDateTime, KLineDataPtr> Pair;
        std::vector<KLineDataPtr> result;
        auto& scaleData = m_runtimeData[cycle];

        // auto lower = std::lower_bound(scaleData.begin(), 
        //                               scaleData.end(),
        //                               nullptr,
        //                               /** comparator */[&startDateTime](const Pair& k,
        //                                                                 const Pair& ref) {
        //                                   return k.second->dateTime < startDateTime; 
        //                               });
        // 
        // auto upper = std::upper_bound(lower, 
        //                               scaleData.end(), 
        //                               nullptr,
        //                               /** comparator */[&endDateTime](const Pair& k,
        //                                                               const Pair& ref) {
        //                                 return k.second->dateTime <= endDateTime; 
        //                               });

        // result.assign(lower, upper);
        return result;
    }

    HistoryTimeQuoteData() {
        m_runtimeData.resize(QuoteCycleEnum::Count);
    }
private:
    std::vector<std::map<QDateTime, KLineDataPtr>> m_runtimeData;
    std::vector<std::vector<KLineDataPtr>> m_serializableData;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(HistoryTimeQuoteData)
{
    // LAMPYRIS_SERIALIZATION_FIELD(m_serializableData);
}
LAMPYRIS_SERIALIZATION_IMPL_END

/*
 * 一个股票行情对象，包含以下部分：历史数据 + 实时数据(快照+Tick) + 基本面
*/
class QuoteBaseData :public ISerializable {
    LAMPYRIS_DECLARE_SERILIZATION(QuoteBaseData);
private:
    QString              m_code;
    QString              m_name;

    // 交易所名称
    QString              m_exchange;
    // 货币类型
    QString              m_currency;

    RealTimeQuoteData    m_realTimeData;
    HistoryTimeQuoteData m_historyData;

public:
	const RealTimeQuoteData* realTimeData() const { return &this->m_realTimeData; }
	RealTimeQuoteData* realTimeData() { return &this->m_realTimeData; }

	const HistoryTimeQuoteData* historyData() const { return &this->m_historyData; }
    HistoryTimeQuoteData* historyData() { return &this->m_historyData; }

    friend class QuoteDatabase;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(QuoteBaseData)
{
    LAMPYRIS_SERIALIZATION_FIELD(m_code);
    LAMPYRIS_SERIALIZATION_FIELD(m_name);
    LAMPYRIS_SERIALIZATION_FIELD(m_exchange);
    LAMPYRIS_SERIALIZATION_FIELD(m_currency);
    LAMPYRIS_SERIALIZATION_FIELD(m_historyData);
}
LAMPYRIS_SERIALIZATION_IMPL_END


typedef std::shared_ptr<QuoteBaseData> QuoteBaseDataPtr;

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