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
	this->setFixedSize(QSize(150, 30));

    this->setMouseTracking(true);
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

    // 创建一个圆锥渐变
    QConicalGradient gradient(center, 0);
    gradient.setColorAt(0.0, Qt::red);    // 起始颜色
    gradient.setColorAt(0.5, Qt::green);  // 中间颜色
    gradient.setColorAt(1.0, Qt::blue);   // 结束颜色

    QRect circleRect(margin, margin, circleDiameter, circleDiameter);

    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(circleRect);

    // 设置文本
    QString text;
    switch (this->m_connectState) {
        case ConnectState::Connected:
            text = Localization->get("ConnectionStatusItem_1"); break;
        case ConnectState::Disconnected:
            text = Localization->get("ConnectionStatusItem_2"); break;
        case ConnectState::Reconnecting:
            text = Localization->get("ConnectionStatusItem_3"); break;
    }

    QFont font = painter.font();
    font.setPointSize(10);
    font.setUnderline(true);
    painter.setFont(font);

    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(text);
    int textHeight = fm.height();

    // 计算文本的位置
    int textX = circleRect.right() + 10;
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
}