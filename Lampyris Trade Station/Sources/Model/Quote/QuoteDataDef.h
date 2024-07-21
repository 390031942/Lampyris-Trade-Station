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
#include <array>

// Project Include(s)
#include <Base/SerializeMacro.h>
#include <Base/SerializableSingleton.h>
#include <Base/Delegate.h>
#include <Collections/CirculateVector.h>

// TWS Include(s)
#include <TWS/Contract.h>

#define LAMPYRIS_TICK_BY_TICK_DATA_LIST_SIZE 50 

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

struct TickByTickData {
    long  timestamp;
    float price;
    float count;
};

struct AskBidData {
    float price;
    float count;
};

class RealTimeQuoteData {
    using TickByTickDataList = CirculateVector<TickByTickData, LAMPYRIS_TICK_BY_TICK_DATA_LIST_SIZE>;
    using TickByTickListener = Delegate<const TickByTickData*>;
    using UpdateListener     = Delegate<RealTimeQuoteData*>;
    using AskBidArray        = std::array<AskBidData, 2>;
public:
    inline const TickByTickData* getLastTickByTick() const
    { return (m_tickByTickDataList.size() > 0) ? &m_tickByTickDataList.back() : nullptr; }

    inline KLineData*            realTimerBar()
    { return &this->m_realTimeBar; }

    inline const KLineData*      realTimerBar() const
    { return &this->m_realTimeBar; }

    inline void                  recordTickByTick(TickByTickData tickByTickData) { 
        m_tickByTickDataList.push_back(tickByTickData); 
        tickByTickListener(getLastTickByTick()); 
        updateListener(this);
    }

    inline void                  recordTickByTick(long timestamp, float price, float count) 
    { recordTickByTick(TickByTickData{ timestamp,price,count }); }

    // ���¼�
    inline void                  setPrice(float value) { this->m_realTimeBar.closePrice = value; }
    inline float                 getPrice() { return this->m_realTimeBar.closePrice; }

    // �ɽ���
    inline void                  setVolume(float volume) { this->m_realTimeBar.volume = volume; }
    inline float                 getVolume() const { return this->m_realTimeBar.volume; }

    // ���ӳɽ�����
    inline void                  setOneMinuteTradeCount(float count) { this->m_oneMinuteTradeCount = count; }
    inline float                 getOneMinuteTradeCount() const { return this->m_oneMinuteTradeCount; }

    // �ɽ�����
    inline void                  setTradeCount(float count) { this->m_tradeCount = count; }
    inline float                 getTradeCount() const { return this->m_tradeCount; }

    // �۶�״̬
    inline void                  setHalted(bool value) { this->m_halted = value; }
    inline bool                  isHalted() const{ return this->m_halted; }

    // ���̼�
    inline void                  setOpenPrice(float price) { this->m_realTimeBar.openPrice = price; }
    inline float                 getOpenPrice() const { return this->m_realTimeBar.openPrice; }

    // ����
    inline void                  setClosePrice(float price) { this->m_realTimeBar.lastClosePrice = price; }
    inline float                 getClosePrice() const { return this->m_realTimeBar.lastClosePrice; }

    // ���
    inline void                  setHighPrice(float price) { this->m_realTimeBar.highestPrice = price; }
    inline float                 getHighPrice() const { this->m_realTimeBar.highestPrice; }

    // ���
    inline void                  setLowPrice(float price) { this->m_realTimeBar.lowestPrice = price; }
    inline float                 getLowPrice() const { return this->m_realTimeBar.lowestPrice; }

    inline void                  setAskPrice(int level, float price) { this->m_asks[level].price = price;  }
    inline void                  setBidPrice(int size, float price) { this->m_bids[size].price = price; }

    inline void                  setAskSize(int level, float count) { this->m_asks[level].count = count; }
    inline void                  setBidSize(int size, float count) { this->m_bids[size].count = count; }

    // ���һ�ʳɽ�ʱ��
    inline void                  setTimestmap(long timestamp) { this->m_timestamp = timestamp; }
    inline long                  getTimestmap() const { return this->m_timestamp; }
                                 
    // �ɹ�����                  
    inline void                  setShortableShares(long shares) { this->m_shortableShares = shares; }
    inline float                 getShortableShares() const { return this->m_shortableShares; }

    // VWAP(�ɽ�����Ȩƽ����)
    inline void                  setVWAP(float value) { m_vwap = value; }
    inline float                 getVWAP() const { return m_vwap; }

	// �仯ֵ
	inline void                  setChange(float value) { this->m_realTimeBar.priceChange = value; }
	inline float                 getChange() const { return this->m_realTimeBar.priceChange; }

	// �仯(%)
	inline void                  setChangePercentage(float value) { this->m_realTimeBar.percentage = value; }
	inline float                 getChangePercentage() const { return this->m_realTimeBar.percentage; }

    // Listeners
    TickByTickListener           tickByTickListener;
    UpdateListener               updateListener;
private:                         
    TickByTickDataList           m_tickByTickDataList;
	KLineData                    m_realTimeBar;
    bool                         m_halted;
    AskBidArray                  m_asks;
    AskBidArray                  m_bids;
    float                        m_oneMinuteTradeCount;
    float                        m_tradeCount;
    float                        m_vwap;
    long                         m_timestamp;
    long                         m_shortableShares;
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

class StockInfoData {
    LAMPYRIS_DECLARE_SERILIZATION(StockInfoData);
public:
    inline void  setCode(const QString& code) { this->m_code = code; }
    inline const QString& getCode() const { return this->m_code; }

    inline void  setName(const QString& code) { this->m_code = code; }
    inline const QString& getName() const { return this->m_name; }

    inline void  setCurrency(const QString& code) { this->m_code = code; }
    inline const QString& getCurrency() const { return this->m_currency; }
private:
    QString m_code;
    QString m_name;
    QString m_currency;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(StockInfoData) {
    LAMPYRIS_SERIALIZATION_FIELD(m_code);
    LAMPYRIS_SERIALIZATION_FIELD(m_name);
}
LAMPYRIS_SERIALIZATION_IMPL_END

class StockFundamentalData {

};

/*
 * һ����Ʊ������󣬰������²��֣���ʷ���� + ʵʱ����(����+Tick) + ������
*/
class QuoteBaseData :public ISerializable {
    LAMPYRIS_DECLARE_SERILIZATION(QuoteBaseData);
public:
	const RealTimeQuoteData* realTimeData() const { return &this->m_realTimeData; }
	RealTimeQuoteData* realTimeData() { return &this->m_realTimeData; }

	const HistoryTimeQuoteData* historyData() const { return &this->m_historyData; }
    HistoryTimeQuoteData* historyData() { return &this->m_historyData; }

    const StockInfoData* infoData() const { return &this->m_infoData; }
    StockInfoData* infoData() { return &this->m_infoData; }

    const StockFundamentalData* fundamentalData() const { return &this->m_fundamentalData; }
    StockFundamentalData* fundamentalData() { return &this->m_fundamentalData; }

    void setTickerId(int tickerId) { this->m_tickerId = tickerId; }
    int  getTickerId() { return this->m_tickerId; }

    inline Contract toContract() const {
        Contract contract;
        contract.symbol   = m_infoData.getCode().toUtf8().constData();
        contract.secType  = "STK";
        contract.currency = m_infoData.getCurrency().toUtf8().constData();
        contract.exchange = "SMART";

        return contract;
    }

private:
    RealTimeQuoteData    m_realTimeData;
    HistoryTimeQuoteData m_historyData;
    StockInfoData        m_infoData;
    StockFundamentalData m_fundamentalData;
    
    int                  m_tickerId = 0;
    friend class QuoteDatabase;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(QuoteBaseData)
{
    LAMPYRIS_SERIALIZATION_FIELD(m_historyData);
    LAMPYRIS_SERIALIZATION_FIELD(m_infoData);
}
LAMPYRIS_SERIALIZATION_IMPL_END

typedef QuoteBaseData* QuoteBaseDataPtr;
class QuoteDataReader {
public:
    QuoteDataReader():m_data(nullptr) {}

    QuoteDataReader(const QuoteDataReader& other) {
        m_data = other.m_data;
    }

    QuoteDataReader& operator=(const QuoteDataReader& other) {
        m_data = other.m_data;
        return *this;
    }

    const QuoteBaseDataPtr operator->() const {
        return m_data;
    }
private:
    QuoteDataReader(QuoteBaseDataPtr data) {
        m_data = data;
    }
    QuoteBaseDataPtr m_data;
    friend class QuoteDatabase;
};


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

/*
 * ����������Ϣ
*/
struct SnapshotQuoteData {
	QString code;
	QString name;
    float   price;
    float   change;
    float   percentage;
};