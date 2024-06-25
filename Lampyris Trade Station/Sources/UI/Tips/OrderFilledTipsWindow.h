/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <QPropertyAnimation>

class OrderFilledTipsWindow:public QWidget {
	Q_OBJECT
public:
	
private:
	QPropertyAnimation* m_anim;
};