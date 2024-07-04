/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <Qlayout>
#include <QLabel>

class QPaintEvent;

class IndexBriefQuoteItem :public QWidget {
	typedef std::function<void()> UpdateCallback;
	Q_OBJECT
public:
	explicit       IndexBriefQuoteItem(QWidget* parent = nullptr);
	              ~IndexBriefQuoteItem();
 
	inline void    subscribe(const QString& code) { this->m_code = code;}
private:
	QString        m_code;
	QHBoxLayout*   m_layout;
	QLabel*        m_textCode;
	QLabel*        m_textPrice;
	QLabel*        m_textChange;
	QLabel*        m_textPercentage;
	int            m_callbackId;
};