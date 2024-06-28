/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "OrderFilledTips.h"
#include <Utility/MemoryUtil.h>
#include <Core/Application.h>

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
    OrderFillTipsInfo info = OrderFillTipsInfo{ code,direction,avgPrice,count };

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
        info.index = m_stack->size();
        window->showAppear(info);
    }
    else {
        m_msgQueue.emplace(info);
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
    info.index = m_stack->size() - 1;
    m_msgQueue.pop();
    m_stack->front()->showAppear(info);
}
 