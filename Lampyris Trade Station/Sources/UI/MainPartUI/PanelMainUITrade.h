/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>

// Project Include(s)
#include <ui_PanelMainUITrade.h>

class PanelMainUITrade : public QWidget {
    Q_OBJECT
public:
    explicit             PanelMainUITrade(QWidget* parent = nullptr);
private:
    Ui::PanelMainUITrade m_ui;
};