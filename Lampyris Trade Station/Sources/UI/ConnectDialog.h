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
	explicit               ConnectDialog(QWidget *parent = nullptr);
			             
          	              ~ConnectDialog();
protected:	             
    void                   mousePressEvent(QMouseEvent* event) override;
		                   
    void                   mouseMoveEvent(QMouseEvent* event) override;
private:                   
	void                   OnClickButtonConnect();

	Ui::ConnectDialogClass m_ui;

	QPoint                 m_dragPosition; 
};
