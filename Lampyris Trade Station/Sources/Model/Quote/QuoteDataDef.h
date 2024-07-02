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
    // ����ʱ��,���������1day����ôdateTime��¼�������գ�������ᾫȷ�� �������ڵĿ�ʼʱ��
    QDateTime   dateTime;

    // K������(��λ:s)�����ֵΪ24*3600 = 86400,˵��k�ߵ���������k
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

    // �������е�������������ǰ���ͺ��
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

class RealTimeQuoteData {
private:
};

class HistoryTimeQuoteData:public ISerializable {
    LAMPYRIS_DECLARE_SERILIZATION(HistoryTimeQuoteData);
public:
    std::vector<KLineDataPtr> query(QuoteCycleEnum cycle, 
                                    const QDateTime& startDateTime, 
                                    const QDateTime& endDateTime = QDateTime()) {
        std::vector<KLineDataPtr> result;
        auto& scaleData = m_runtimeData[cycle];

        auto lower = std::lower_bound(scaleData.begin(), 
                                      scaleData.end(),
                                      KLineData(),
                                      /** comparator */[&startDateTime](const KLineDataPtr& k,
                                                                        const KLineDataPtr& ref) {
                                          return k->dateTime < startDateTime; 
                                      });

        auto upper = std::upper_bound(lower, 
                                      scaleData.end(), 
                                      KLineData(),
                                      /** comparator */[&endDateTime](const KLineDataPtr& k, 
                                                                      const KLineDataPtr ref) { 
                                        return k->dateTime <= endDateTime; 
                                      });

        result.assign(lower, upper);
        return result;
    }

    HistoryTimeQuoteData() {
        m_runtimeData.resize(QuoteCycleEnum::Count);
    }
private:
    std::vector<std::map<QDateTime, KLineDataPtr>> m_runtimeData;
    std::vector<std::vector<KLineDataPtr>> m_serializableData;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(KLineData)
{
    LAMPYRIS_SERIALIZATION_FIELD(m_serializableData);
}
LAMPYRIS_SERIALIZATION_IMPL_END

/*
 * һ����Ʊ������󣬰������²��֣���ʷ���� + ʵʱ����(����+Tick) + ������
*/
class QuoteBaseData {
private:
    QString code;
    QString name;
    // ����������
    QString exchange;
    // ��������
    QString currency;

    friend class QuoteDatabase;
};

typedef std::shared_ptr<QuoteBaseData> QuoteBaseDataPtr;

/*
 * ָ����Ҫ������Ϣ
*/
struct IndexBriefQuoteData {
    QString code;
    QString name;
    float   price;
    float   change;
    float   percentage;
};