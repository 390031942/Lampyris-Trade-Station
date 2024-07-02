/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "IndexBriefQuoteItem.h"
#include <Utility/MemoryUtil.h>

// QT Include(s)
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

IndexBriefQuoteItem::IndexBriefQuoteItem(QWidget* parent):
	m_layout(LAMPYRIS_NEW(QHBoxLayout,this)){
	this->setLayout(this->m_layout);

	QLabel* textName   = LAMPYRIS_NEW(QLabel, this);
	QLabel* textPrice  = LAMPYRIS_NEW(QLabel, this);
	QLabel* textChange = LAMPYRIS_NEW(QLabel, this);

	this->m_layout->addWidget(textName);
	this->m_layout->addWidget(textPrice);
	this->m_layout->addWidget(textChange);
}

IndexBriefQuoteItem::~IndexBriefQuoteItem() {
}

void IndexBriefQuoteItem::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

}
