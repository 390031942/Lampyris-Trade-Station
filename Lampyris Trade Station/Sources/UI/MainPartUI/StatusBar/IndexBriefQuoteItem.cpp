/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "IndexBriefQuoteItem.h"
#include <Utility/MemoryUtil.h>
#include <Model/App/AppUIStyle.h>
#include <Base/Localization.h>
#include <Model/Quote/QuoteDatabase.h>

// QT Include(s)
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

IndexBriefQuoteItem::IndexBriefQuoteItem(QWidget* parent):
	m_layout(LAMPYRIS_NEW(QHBoxLayout,this)),
	m_textCode(LAMPYRIS_NEW(QLabel, this)),
	m_textPrice(LAMPYRIS_NEW(QLabel, this)),
	m_textChange(LAMPYRIS_NEW(QLabel, this)),
	m_textPercentage(LAMPYRIS_NEW(QLabel, this)) {

	// 设置布局
	this->setLayout(this->m_layout);
	this->m_layout->setContentsMargins(0, 0, 0, 0);
	this->m_layout->setSpacing(3);
	this->m_layout->addWidget(m_textCode);
	this->m_layout->addWidget(m_textPrice);
	this->m_layout->addWidget(m_textChange);
	this->m_layout->addWidget(m_textPercentage);

	this->setMinimumWidth(250);

	// 添加更新监听
	this->m_callbackId = QuoteDatabase::getInstance()->onUpdatendexBriefQuote += [=]() {
		const auto& info = QuoteDatabase::getInstance()->queryIndexBriefQuote(this->m_code);
		m_textCode->setText(info.name);
		m_textPrice->setText(QString::number(info.price));
		m_textChange->setText(QString::number(info.change));
		m_textPercentage->setText(QString::number(info.percentage) + "%");
	};
}

IndexBriefQuoteItem::~IndexBriefQuoteItem() {
	QuoteDatabase::getInstance()->onUpdatendexBriefQuote -= this->m_callbackId;
}