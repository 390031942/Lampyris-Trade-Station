/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "TradeStockSearchLineEdit.h"
#include <Model/Quote/QuoteDatabase.h>

TradeStockSearchLineEdit::TradeStockSearchLineEdit(QWidget* parent)
	: AbstractSuggestionLineEdit(parent) {
	this->registerItemWidgetType<TradeStockSearchSuggestionItemWidget>();
}

void TradeStockSearchLineEdit::getSuggestions(const QString& input) {
	QuoteDatabase::getInstance()->searchNoAlloc(input, m_searchResultlist);
	m_suggestionList.clear();
}

TradeStockSearchSuggestionItemWidget::TradeStockSearchSuggestionItemWidget(QWidget* parent)
	:AbstractSuggestionItemWidget(parent),
	m_textCode(new QLabel(this)),
	m_textName(new QLabel(this)) {
	m_textCode->setFixedWidth(70);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_textCode);
	layout->addWidget(m_textName);
}

void TradeStockSearchSuggestionItemWidget::setSuggestionData(const AbstractSuggestionData& data) {
	const TradeStockSearchSuggestionData& suggestionData =
		static_cast<const TradeStockSearchSuggestionData&>(data);
	auto quoteData = suggestionData.getQuoteData();
	if (quoteData != nullptr) {
		m_textCode->setText(quoteData->infoData()->getCode());
		m_textName->setText(quoteData->infoData()->getName());
	}
	else {
		m_textCode->setText(QString());
		m_textName->setText(QString());
	}
}

TradeStockSearchSuggestionData::TradeStockSearchSuggestionData(const QuoteBaseDataPtr quoteData)
	:m_quoteData(quoteData) {}

QString TradeStockSearchSuggestionData::toString() {
	if (m_quoteData != nullptr) {
		return m_quoteData->infoData()->getCode();
	}

	return QString();
}

const QuoteBaseDataPtr TradeStockSearchSuggestionData::getQuoteData() const {
	return this->m_quoteData;
}
