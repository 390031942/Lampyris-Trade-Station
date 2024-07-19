/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QTimer>
#include <QWidget>
#include <QPropertyAnimation>

// Project Include(s)
#include "ui_OrderFilledTipsWindow.h"
#include <Base/Singleton.h>
#include <Collections/CirculateQueue.h>

// STD Include(s)
#include <queue>

struct OrderFillTipsInfo {
	QString code;
	QString direction;
	float   avgPrice;
	float   count;
	int     index;
};

class OrderFilledTipsWindow:public QWidget {
	Q_OBJECT
public:
	                              ~OrderFilledTipsWindow();
Q_SIGNALS:
	void                           disappeared(OrderFilledTipsWindow* window);
public Q_SLOTS:
	void                           moveDown();
private:
	explicit                       OrderFilledTipsWindow(QWidget* parent = nullptr);
	void                           showAppear(const OrderFillTipsInfo& info);
	void                           showMoveDown();
	void                           showDisappear();
	int                            m_index;
	QPropertyAnimation*            m_appearAnim;
	QPropertyAnimation*            m_moveDownAnim;
	QPropertyAnimation*            m_disappearAnim;
	QTimer                         m_autoDisappearTimer;
	Ui::OrderFilledTipsWindowClass m_ui;

	friend class OrderFilledTips;
};