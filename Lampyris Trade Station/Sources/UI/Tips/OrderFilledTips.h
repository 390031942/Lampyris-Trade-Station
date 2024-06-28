/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "OrderFilledTipsWindow.h"
#include <Base/Singleton.h>
#include <Collections/CircularQueue.h>

class OrderFilledTips :public SingletonQObject<OrderFilledTips> {
	Q_OBJECT
	using WidgetStack = CircularQueue<OrderFilledTipsWindow*>;
	using MessageQueue = std::queue<OrderFillTipsInfo>;
Q_SIGNALS:
	void         moveDown();
public:
	             OrderFilledTips();
	            ~OrderFilledTips();
	void         show(const QString& code, const QString& direction, float avgPrice, float count);
private:
	void         tick();
	WidgetStack* m_stack;
	MessageQueue m_msgQueue;
	bool         m_waitDisappeared = false;
};