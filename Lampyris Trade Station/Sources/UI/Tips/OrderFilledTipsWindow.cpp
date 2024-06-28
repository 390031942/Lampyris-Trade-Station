/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "OrderFilledTipsWindow.h"
#include <Utility/MemoryUtil.h>
#include <Core/Application.h>

// QT Include(s)
#include <QScreen>

OrderFilledTipsWindow::OrderFilledTipsWindow(QWidget* parent):QWidget(parent) {
	this->m_ui.setupUi(this);

    // 不要标题栏,也不要在任务栏显示,并且要置顶
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);

	// 初始化动画
	this->m_appearAnim = new QPropertyAnimation(this, "pos", this);

	this->m_moveDownAnim = new QPropertyAnimation(this, "pos", this);

	this->m_disappearAnim = new QPropertyAnimation(this, "windowOpacity", this);
    this->m_disappearAnim->setStartValue(1.0f);
    this->m_disappearAnim->setEndValue(1.0f);
    this->m_disappearAnim->setDuration(1000);

    // 信号
    QObject::connect(this->m_disappearAnim, &QPropertyAnimation::finished, [=]() {
        this->m_autoDisappearTimer.stop();
        emit this->disappeared(this);
    });

    QObject::connect(&this->m_autoDisappearTimer, &QTimer::timeout, [=]() {
        this->showDisappear();
    });

	// 初始化图标与样式
	this->m_ui.iconApp->setPixmap(QPixmap(":/Resources/Image/Comm/Comm_0001.png").scaled(23,23));
	this->m_ui.buttonClose->setStyleSheet(
        "QPushButton { "
        "   background-image: url(:/Resources/Image/Comm/Comm_0002.png); "
        "   border: none; "
        "   background-size: cover; " 
        "} "
        "QPushButton:hover { "
        "   background-color: gray; "
        "} "
        "QPushButton:pressed { "
        "   background-color: rgb(108, 108, 108); "
        "}"
    );
}


OrderFilledTipsWindow::~OrderFilledTipsWindow() {

}

void OrderFilledTipsWindow::moveDown() {
    this->showMoveDown();
}

void OrderFilledTipsWindow::showAppear(const OrderFillTipsInfo& info) {
    auto availableGeometry = QApplication::primaryScreen()->availableGeometry();

    float y = availableGeometry.height() - this->height() * info.index;
    float x1 = availableGeometry.width();
    float x2 = x1 - this->width();

    this->m_appearAnim->setStartValue(QPoint(x1,y));
    this->m_appearAnim->setEndValue(QPoint(x2,y));
    this->m_appearAnim->setDuration(2000);
    this->m_appearAnim->start();

    this->m_ui.textStockName->setText(info.code);
    this->m_ui.textDirection->setText(info.direction);
    this->m_ui.textFilledAvgPrice->setText(QString::number(info.avgPrice));
    this->m_ui.textFilledCount->setText(QString::number(info.count));

    this->m_index = info.index;
    this->show();
}

void OrderFilledTipsWindow::showMoveDown() {
    float x = this->geometry().x();
    float y1 = this->geometry().y();
    float y2 = y1 - this->height();

    this->m_moveDownAnim->setStartValue(QPoint(x, y1));
    this->m_moveDownAnim->setEndValue(QPoint(x, y2));
    this->m_moveDownAnim->setDuration(1000);
    this->m_moveDownAnim->start();

    this->m_index--;
    if (this->m_index == 1) {
        this->m_autoDisappearTimer.setInterval(30000);
        this->m_autoDisappearTimer.start();
    }
}

void OrderFilledTipsWindow::showDisappear() {
    this->m_disappearAnim->start();
}