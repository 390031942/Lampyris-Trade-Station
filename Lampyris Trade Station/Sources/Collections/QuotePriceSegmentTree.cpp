/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "QuotePriceSegmentTree.h"

QuotePriceSegmentTree::QuotePriceSegmentTree(const QuoteBaseDataPtr quoteData) :
    m_quoteData(quoteData), root(nullptr) {
    if (!quoteData.perDayKLineList.empty()) {
        root = BuildSegmentTree(0, m_quoteData.perDayKLineList.size() - 1);
    }
}

std::pair<float, int> QuotePriceSegmentTree::QueryMax(int left, int right) {
    return QueryHelperMax(root, left, right);
}

std::pair<float, int> QuotePriceSegmentTree::QueryMin(int left, int right) {
    return QueryHelperMin(root, left, right);
}

QuotePriceSegmentTreeNodePtr QuotePriceSegmentTree::BuildSegmentTree(int start, int end) {
    if (start > end)
        return nullptr;

    QuotePriceSegmentTreeNodePtr node = std::make_shared<QuotePriceSegmentTreeNode>(start, end);
    if (start == end) {
        node->maxValue = m_quoteData.perDayKLineList[start].highestPrice;
        node->maxIndex = start;
        node->minValue = m_quoteData.perDayKLineList[start].lowestPrice;
        node->minIndex = start;
        return node;
    }

    int mid = (start + end) / 2;
    node->left = BuildSegmentTree(start, mid);
    node->right = BuildSegmentTree(mid + 1, end);

    node->maxValue = std::max(node->left->maxValue, node->right->maxValue);
    node->maxIndex = (node->left->maxValue >= node->right->maxValue) ? node->left->maxIndex : node->right->maxIndex;

    node->minValue = std::min(node->left->minValue, node->right->minValue);
    node->minIndex = (node->left->minValue <= node->right->minValue) ? node->left->minIndex : node->right->minIndex;

    return node;
}

std::pair<float, int> QuotePriceSegmentTree::QueryHelperMax(QuotePriceSegmentTreeNodePtr node, int left, int right) {
    if (node->startIndex > right || node->endIndex < left)
        return std::make_pair(std::numeric_limits<float>::max(), -1);

    if (node->startIndex >= left && node->endIndex <= right)
        return std::make_pair(node->maxValue, node->maxIndex);

    auto leftResult = QueryHelperMax(node->left, left, right);
    auto rightResult = QueryHelperMax(node->right, left, right);

    float maxValue = std::max(leftResult.first, rightResult.first);
    int maxIndex = (leftResult.first >= rightResult.first) ? leftResult.second : rightResult.second;

    return std::make_pair(maxValue, maxIndex);
}

std::pair<float, int> QuotePriceSegmentTree::QueryHelperMin(QuotePriceSegmentTreeNodePtr node, int left, int right) {
    if (node->startIndex > right || node->endIndex < left)
        return std::make_pair(std::numeric_limits<float>::min(), -1);

    if (node->startIndex >= left && node->endIndex <= right)
        return std::make_pair(node->minValue, node->minIndex);

    auto leftResult = QueryHelperMin(node->left, left, right);
    auto rightResult = QueryHelperMin(node->right, left, right);

    float minValue = std::min(leftResult.first, rightResult.first);
    int minIndex = (leftResult.first <= rightResult.first) ? leftResult.second : rightResult.second;

    return std::make_pair(minValue, minIndex);
}
