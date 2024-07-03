/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>

/*
 * 需要处理鼠标覆盖/离开 事件的QWidget
*/
class QHoverableWidget:public QWidget {
	Q_OBJECT
public:
	explicit     QHoverableWidget(QWidget* widget = nullptr);
	virtual     ~QHoverableWidget();

	inline bool  hovered() const { return this->m_hovered; }
protected:
	virtual void enterEvent(QEvent* event) override;
	virtual void leaveEvent(QEvent* event) override;
	bool         m_hovered;
};