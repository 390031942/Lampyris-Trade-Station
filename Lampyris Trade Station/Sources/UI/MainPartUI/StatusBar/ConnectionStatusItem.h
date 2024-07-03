/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>

// Project Include(s)
#include <UI/Common/QHoverableWidget.h>
#include <Const/ConnectState.h>

class ConnectionStatusItem :public QHoverableWidget {
	Q_OBJECT
public:
	explicit     ConnectionStatusItem(QWidget* parent = nullptr);
	            ~ConnectionStatusItem();
protected:
	virtual void paintEvent(QPaintEvent* event) override;
private:
	int          m_timerId;
	ConnectState m_connectState;
};