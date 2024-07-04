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

	// ���ƿ�ȸ߶�
	this->setFixedSize(QSize(100, 30));
}

ConnectionStatusItem::~ConnectionStatusItem() {
	CallTimer::getInstance()->clearTimer(this->m_timerId);
}

void ConnectionStatusItem::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // ����ԲȦ����ɫ��λ��
    int circleDiameter = 20; // ԲȦֱ��
    int margin = (height() - circleDiameter) / 2; // ���±߾�

    // ��ȡ���ڵ����ĵ�
    QPoint center = rect().center();
    QRect circleRect(margin, margin, circleDiameter, circleDiameter);

    // �����ı�����ɫ
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

    // �����ı���λ��
    int textX = circleRect.right() + 20;
    int textY = (height() + textHeight) / 2 - fm.descent();

    painter.setPen(Qt::black);
    painter.drawText(textX, textY, text);

    // �߿�
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