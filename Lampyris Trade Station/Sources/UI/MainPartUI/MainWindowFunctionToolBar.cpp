/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "MainWindowFunctionToolBar.h"
#include "ToolBar/MainWindowFunctionToolBarButton.h"

MainWindowFunctionToolBar::MainWindowFunctionToolBar(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    m_container = new QWidget();
    m_containerLayout = new QVBoxLayout(m_container);
    m_containerLayout->setContentsMargins(0, 0, 0, 0);
    m_containerLayout->setSpacing(0);

    for (int i = 0; i < 10; ++i) {
        MainWindowFunctionToolBarButton* button = new MainWindowFunctionToolBarButton(this);
        button->setText(QString("Button %1").arg(i + 1));
        button->setIcon(QIcon(":/path/to/icon.png")); // Replace with your icon path
        button->setIconSize(QSize(32, 32));
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setFixedSize(100, 100);
        connect(button, &QToolButton::clicked, this, [this, button]() {
            clearSelection();
            button->setSelected(true);
            });
        m_containerLayout->addWidget(button);
    }

    m_container->setLayout(m_containerLayout);
    m_scrollArea->setWidget(m_container);
    layout->addWidget(m_scrollArea);
    setLayout(layout);
}

void MainWindowFunctionToolBar::clearSelection() {
    QList<MainWindowFunctionToolBarButton*> buttons = findChildren<MainWindowFunctionToolBarButton*>();
    for (MainWindowFunctionToolBarButton* button : buttons) {
        button->setSelected(false);
    }
}
