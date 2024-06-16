/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QDialog>
#include <QTimer>

// Project Include(s)
#include "ui_ConnectDialog.h"
#include <Model/Login/ConnectionHistoryData.h>

class ConnectDialog : public QDialog {
	typedef IBGatewayHistoryConnectionInfo ConnectInfo;
	Q_OBJECT
public:
	explicit               ConnectDialog(QWidget *parent = nullptr);
          	              ~ConnectDialog();
protected:	             
    void                   mousePressEvent(QMouseEvent* event) override;
    void                   mouseMoveEvent(QMouseEvent* event) override;
private:                   
	void                   onClickButtonConnect();
	void                   tryConnect();
	void                   setControlEditable(bool value);

	Ui::ConnectDialogClass m_ui;
	QPoint                 m_dragPosition; 
	std::vector<QWidget*>  m_needDisableWidgetList;

	/*********** 连接相关 ***********/
	QTimer                 m_connectTimer;
	int                    m_retryCount;
	int                    m_maxRetryCount = 5;
	ConnectInfo            m_connectInfo;
};
