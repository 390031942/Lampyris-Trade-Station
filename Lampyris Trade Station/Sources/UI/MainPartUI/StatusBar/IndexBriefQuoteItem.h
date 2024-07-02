/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <Qlayout>

class QPaintEvent;

class IndexBriefQuoteItem :public QWidget {
	Q_OBJECT
public:
	explicit     IndexBriefQuoteItem(QWidget* parent = nullptr);
	            ~IndexBriefQuoteItem();

	inline void  subscribe(const QString& code) { this->m_code = code;}
protected:
	virtual void paintEvent(QPaintEvent* event) override;
private:
	QString      m_code;
	QHBoxLayout* m_layout;
};