/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <QPropertyAnimation>

// Project Include(s)
#include "ui_OrderFilledTipsWindow.h"
#include <Base/Singleton.h>
#include <Collections/CircularQueue.h>

// STD Include(s)
#include <queue>

class OrderFilledTipsWindow:public QWidget {
	Q_OBJECT
public:
	                              ~OrderFilledTipsWindow();
Q_SIGNALS:
	void                           disappeared();
public Q_SLOTS:
	void                           moveDown();
private:
	explicit                       OrderFilledTipsWindow(QWidget* parent = nullptr);
	void                           showAppear();
	void                           showMoveDown();
	void                           showDisappear();
	QPropertyAnimation*            m_appearAnim;
	QPropertyAnimation*            m_moveDownAnim;
	QPropertyAnimation*            m_disappearAnim;
	Ui::OrderFilledTipsWindowClass m_ui;

	friend class OrderFilledTips;
};

struct OrderFillTipsInfo {
	QString code;
	QString direction;
	float   avgPrice;
	float   count;
};

class OrderFilledTips:public Singleton<OrderFilledTips> {
	using WidgetStack = CircularQueue<OrderFilledTipsWindow*>;
	using MessageQueue = std::queue<OrderFillTipsInfo*>;
public:
	             OrderFilledTips();
	            ~OrderFilledTips();
	void         show(const QString& code, const QString& direction, float avgPrice, float count);
private:
	WidgetStack* m_stack;
	MessageQueue m_msgQueue;
};