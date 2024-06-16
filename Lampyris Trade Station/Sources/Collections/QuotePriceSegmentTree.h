/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <algorithm>
#include <utility>
#include <memory>

// Project Include(s)
#include <Model/Quote/QuoteDataDef.h>

struct QuotePriceSegmentTreeNode;
typedef std::shared_ptr<QuotePriceSegmentTreeNode> QuotePriceSegmentTreeNodePtr;

struct QuotePriceSegmentTreeNode {
    using Pointer = QuotePriceSegmentTreeNodePtr;

    // �������еĿ�ʼ���������
    int     startIndex;
    int     endIndex;

    // �ýڵ�����к��ӽڵ�(�����Լ�)����С/���ֵ �Լ���Ӧ������
    float   maxValue;
    int     maxIndex;
    float   minValue;
    int     minIndex;

    // ���Һ��ӽڵ�
    Pointer left;
    Pointer right;

    QuotePriceSegmentTreeNode(int start, int end) : 
        startIndex(start), endIndex(end), left(nullptr), right(nullptr) {}
};

class QuotePriceSegmentTree {
public:
                                 QuotePriceSegmentTree(QuoteData quoteData);
                                
    std::pair<float, int>        QueryMax(int left, int right);
                                
    std::pair<float, int>        QueryMin(int left, int right);
private:
    QuotePriceSegmentTreeNodePtr BuildSegmentTree(int start, int end);

    std::pair<float, int>        QueryHelperMax(QuotePriceSegmentTreeNodePtr node, int left, int right);
                                 
    std::pair<float, int>        QueryHelperMin(QuotePriceSegmentTreeNodePtr node, int left, int right);

    QuoteData m_quoteData;
    QuotePriceSegmentTreeNodePtr root;
};
