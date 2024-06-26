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

void OrderFilledTipsWindow::showAppear() {

}

void OrderFilledTipsWindow::showMoveDown() {

}

void OrderFilledTipsWindow::showDisappear() {

}

OrderFilledTips::OrderFilledTips() {
    m_stack = new WidgetStack(5);
    Application::addTickFunc();
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
        m_stack->enqueue(window);
    }
    else {
        m_msgQueue.emplace(OrderFillTipsInfo{ code,direction,avgPrice,count });
    }
}
