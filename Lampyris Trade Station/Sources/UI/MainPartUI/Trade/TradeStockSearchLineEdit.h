/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <UI/Common/AbstractSuggestionLineEdit.h>
#include <Model/Quote/QuoteDataDef.h>

// QT Include(s)
#include <QLabel>

struct TradeStockSearchSuggestionData :public AbstractSuggestionData {
public:
	                       TradeStockSearchSuggestionData(const QuoteBaseDataPtr quoteData);
	virtual QString        toString() override;
	const QuoteBaseDataPtr getQuoteData() const;
private:
	const QuoteBaseDataPtr m_quoteData;
};

class TradeStockSearchSuggestionItemWidget:public AbstractSuggestionItemWidget {
	Q_OBJECT
public:
	explicit     TradeStockSearchSuggestionItemWidget(QWidget* parent = nullptr);
	virtual void setSuggestionData(const AbstractSuggestionData& data);
private:
	QLabel*      m_textCode;
	QLabel*      m_textName;
};

class TradeStockSearchLineEdit:public AbstractSuggestionLineEdit {
	typedef std::vector<QuoteBaseDataPtr> SearchResultList;
	Q_OBJECT
public:
	explicit         TradeStockSearchLineEdit(QWidget* parent = nullptr);
	virtual void     getSuggestions(const QString& input) override;
private:
	SearchResultList m_searchResultlist;
};