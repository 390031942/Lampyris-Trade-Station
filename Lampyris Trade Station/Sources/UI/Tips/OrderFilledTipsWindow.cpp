/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include "OrderFilledTipsWindow.h"
#include <Utility/MemoryUtil.h>
#include <Core/Application.h>

OrderFilledTipsWindow::OrderFilledTipsWindow(QWidget* parent):QWidget(parent) {
	this->m_ui.setupUi(this);

    // 不要标题栏,也不要在任务栏显示
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

	// 初始化动画
	this->m_appearAnim = new QPropertyAnimation(this, "pos", this);

	this->m_moveDownAnim = new QPropertyAnimation(this, "pos", this);

	this->m_disappearAnim = new QPropertyAnimation(this, "windowOpacity", this);
    this->m_disappearAnim->setStartValue(1.0f);
    this->m_disappearAnim->setEndValue(1.0f);
    this->m_disappearAnim->setDuration(1.0f);

    // 信号
    QObject::connect(this->m_disappearAnim, &QPropertyAnimation::finished, [=]() {
        emit this->disappeared();
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
}

void OrderFilledTipsWindow::showMoveDown() {

}

void OrderFilledTipsWindow::showDisappear() {
    this->m_disappearAnim->start();
}

OrderFilledTips::OrderFilledTips() {
    m_stack = new WidgetStack(5);
    Application::addTickFunc([=]() {
        this->tick();
    });
}

OrderFilledTips::~OrderFilledTips() {
    while (!m_stack->isEmpty()) {
        OrderFilledTipsWindow* window = m_stack->front();
        LAMPYRIS_SAFE_DELETE(window);
        m_stack->dequeue();
    }

    LAMPYRIS_SAFE_DELETE(this->m_stack);
}

void OrderFilledTips::show(const QString& code, const QString& direction, float avgPrice, float count) {
    OrderFilledTipsWindow* window;
    if (!m_stack->isFull()) {
        window = new OrderFilledTipsWindow;
        QObject::connect(this, &OrderFilledTips::moveDown, window, &OrderFilledTipsWindow::moveDown);
        QObject::connect(window, &OrderFilledTipsWindow::disappeared, [=](OrderFilledTipsWindow* window) {
            m_stack->dequeue();
            window->blockSignals(true);
            {
                emit this->moveDown();
            }
            window->blockSignals(false);
            m_stack->enqueue(window);

            this->m_waitDisappeared = false;
        });
        m_stack->enqueue(window);
    }
    else {
        m_msgQueue.emplace(OrderFillTipsInfo{ code,direction,avgPrice,count });
    }
}

void OrderFilledTips::tick() {
    if (this->m_msgQueue.empty())
        return;

    if (this->m_waitDisappeared)
        return;

    if (m_stack->isFull()) {
        m_stack->front()->showDisappear();
        this->m_waitDisappeared = true;
        return;
    }

    OrderFillTipsInfo info = m_msgQueue.front();
    info.index = m_stack->size();
    m_msgQueue.pop();
    m_stack->front()->showAppear(info);
}
