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
#include "ui_StrategySettingItem.h"

struct StrategyDescription;

class StrategySettingItem :public QWidget {
	Q_OBJECT
public:
	explicit  StrategySettingItem(QWidget* parent = NULL);
	         ~StrategySettingItem();

	void      setStrategyDescription(const StrategyDescription& info);
private:
	Ui::StrategySettingItem m_ui;
};