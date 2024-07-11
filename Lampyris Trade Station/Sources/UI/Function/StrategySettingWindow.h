/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QButtonGroup>
#include <QWidget>
#include <QTimer>
#include <QStandardItemModel>
#include <QItemDelegate>

// Project Include(s)
#include "ui_StrategySettingWindow.h"

class StrategySettingWindow :public QWidget {
	Q_OBJECT
public:
	explicit  StrategySettingWindow(QWidget* parent = NULL);
	         ~StrategySettingWindow();
private:
	Ui::StrategySettingWindow m_ui;
};