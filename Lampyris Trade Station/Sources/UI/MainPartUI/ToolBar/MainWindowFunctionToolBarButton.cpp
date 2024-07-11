/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "MainWindowFunctionToolBarButton.h"

// QT Include(s)
#include <QStyleOption>
#include <QPainter>

MainWindowFunctionToolBarButton::MainWindowFunctionToolBarButton(QWidget* parent) : QToolButton(parent), m_isSelected(false) {
    setCheckable(true);
    setStyleSheet("QToolButton { border: none; }");
}

void MainWindowFunctionToolBarButton::setSelected(bool selected) {
    m_isSelected = selected;
    update();
}

void MainWindowFunctionToolBarButton::enterEvent(QEvent* event) {
    QToolButton::enterEvent(event);
    setStyleSheet("QToolButton { border: 2px solid orange; }");
}

void MainWindowFunctionToolBarButton::leaveEvent(QEvent* event) {
    QToolButton::leaveEvent(event);
    setStyleSheet("QToolButton { border: none; }");
}

void MainWindowFunctionToolBarButton::paintEvent(QPaintEvent* event) {
    QToolButton::paintEvent(event);
    if (m_isSelected) {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        p.fillRect(opt.rect, QColor(255, 165, 0)); // Orange color
    }
}
