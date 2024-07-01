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
    // ����
    QDateTime   date;

    // K�߷�������(��λ:s)�����ֵΪ24*3600 = 86400,˵��k�ߵ���������k
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

    // �������е�������������ǰ���ͺ��
    int         indexInList;

    // ���л�����
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
    }
};

class SecurityData {
private:
    QString code;
    QString name;
    // ����������
    QString exchange;
    // ��������
    QString currency;

    friend class QuoteDatabase;
};

typedef std::shared_ptr<SecurityData> SecurityDataPtr;

class QuoteDataProvider {

};

/*
 * �������ͣ���ͬ���������� ��Ҫʵ�ֶ�Ӧ�� QuoteDataProvider
*/
enum class QuoteDataType {

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