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
protected:
	virtual void paintEvent(QPaintEvent* event) override;
private:
	QHBoxLayout* m_layout;
};