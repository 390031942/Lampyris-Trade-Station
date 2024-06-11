/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <QDialog>
#include "ui_ConnectDialog.h"

class ConnectDialog : public QDialog {
	Q_OBJECT

public:
	ConnectDialog(QWidget *parent = nullptr);

	~ConnectDialog();
private:
	Ui::ConnectDialogClass ui;
};
