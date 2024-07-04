/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "ConnectionStatusItem.h"
#include <Core/Application.h>
#include <Base/CallTimer.h>
#include <Base/Localization.h>

// QT Include(s)
#include <QPainter>
#include <QRadialGradient>

ConnectionStatusItem::ConnectionStatusItem(QWidget* parent):QHoverableWidget(parent){
	this->m_timerId = CallTimer::getInstance()->setInterval([=]() {
        auto connectState = Application::connectState();
        if (connectState != this->m_connectState) {
            this->repaint();
            this->m_connectState = connectState;
        }

	},100);

	// 限制宽度高度
	this->setFixedSize(QSize(100, 30));
}

ConnectionStatusItem::~ConnectionStatusItem() {
	CallTimer::getInstance()->clearTimer(this->m_timerId);
}

void ConnectionStatusItem::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置圆圈的颜色和位置
    int circleDiameter = 20; // 圆圈直径
    int margin = (height() - circleDiameter) / 2; // 上下边距

    // 获取窗口的中心点
    QPoint center = rect().center();
    QRect circleRect(margin, margin, circleDiameter, circleDiameter);

    // 设置文本和颜色
    QString text;
    QColor color;
    switch (this->m_connectState) {
        case ConnectState::Connected:
            text = Localization->get("ConnectionStatusItem_1"); color = QColor(Qt::green); break;
        case ConnectState::Disconnected:
            text = Localization->get("ConnectionStatusItem_2"); color = QColor(Qt::red); break;
        case ConnectState::Reconnecting:
            text = Localization->get("ConnectionStatusItem_3"); color = QColor(Qt::yellow); break;
    }

    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(circleRect);

    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(text);
    int textHeight = fm.height();

    // 计算文本的位置
    int textX = circleRect.right() + 20;
    int textY = (height() + textHeight) / 2 - fm.descent();

    painter.setPen(Qt::black);
    painter.drawText(textX, textY, text);

    // 边框
    if (this->m_hovered) {
        QPen pen(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        QRect thisRect = rect();
        painter.drawRect(thisRect);
    }

    painter.restore();
}