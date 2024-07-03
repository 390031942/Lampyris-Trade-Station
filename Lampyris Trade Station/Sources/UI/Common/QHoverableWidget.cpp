/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "QHoverableWidget.h"

QHoverableWidget::QHoverableWidget(QWidget* widget):QWidget(widget), m_hovered(false) {
	this->setMouseTracking(true);
}

QHoverableWidget::~QHoverableWidget() {
}

void QHoverableWidget::enterEvent(QEvent* event) {
	QWidget::enterEvent(event);
	this->m_hovered = true;
	this->repaint();
}

void QHoverableWidget::leaveEvent(QEvent* event) {
	QWidget::leaveEvent(event);
	this->m_hovered = false;
	this->repaint();
}
