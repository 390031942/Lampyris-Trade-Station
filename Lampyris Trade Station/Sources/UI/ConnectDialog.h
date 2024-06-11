/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QDialog>

// Project Include(s)
#include "ui_ConnectDialog.h"

class ConnectDialog : public QDialog {
	Q_OBJECT
public:
	explicit ConnectDialog(QWidget *parent = nullptr);

          	~ConnectDialog();
private:
	Ui::ConnectDialogClass ui;
};
