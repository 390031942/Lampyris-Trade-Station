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
	this->setFixedSize(QSize(150, 30));

    this->setMouseTracking(true);
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

    // ����һ��Բ׶����
    QConicalGradient gradient(center, 0);
    gradient.setColorAt(0.0, Qt::red);    // ��ʼ��ɫ
    gradient.setColorAt(0.5, Qt::green);  // �м���ɫ
    gradient.setColorAt(1.0, Qt::blue);   // ������ɫ

    QRect circleRect(margin, margin, circleDiameter, circleDiameter);

    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(circleRect);

    // �����ı�
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

    // �����ı���λ��
    int textX = circleRect.right() + 10;
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
}