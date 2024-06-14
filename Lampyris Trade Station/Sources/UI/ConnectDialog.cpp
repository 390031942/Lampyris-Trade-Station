/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "ConnectDialog.h"
#include <Utility/StringUtil.h>
#include <Core/Application.h>

// QT Include(s)
#include <QMouseEvent>
#include <QDateTime>
#include <QIntValidator>
#include <QMessageBox>

ConnectDialog::ConnectDialog(QWidget *parent)
	: QDialog(parent),m_retryCount(0) {
	m_ui.setupUi(this);

	// Gif 表情
	m_ui.loginGif->setGifImagePath(":/Resources/Gif/Gif_0005.gif");

	// 输入框占位
	m_ui.textIP->setPlaceholderText("IP Address");
	m_ui.textPort->setPlaceholderText("Port");
	m_ui.textClientId->setPlaceholderText("Client ID");

	// 隐藏窗口标题栏
	setWindowFlags(Qt::FramelessWindowHint);

	// Tab顺序
	QWidget::setTabOrder(m_ui.textIP, m_ui.textPort);
	QWidget::setTabOrder(m_ui.textPort, m_ui.textClientId);
	QWidget::setTabOrder(m_ui.textClientId, m_ui.toggleSaveIP);
	QWidget::setTabOrder(m_ui.toggleSaveIP, m_ui.toggleAutoConnect);
	QWidget::setTabOrder(m_ui.toggleAutoConnect, m_ui.buttonEnter);
	QWidget::setTabOrder(m_ui.buttonEnter, m_ui.textIP);

	// 初始化一个ClientId,就用时间戳就行
	m_ui.textClientId->setText(QString("%1").arg((int)QDateTime::currentSecsSinceEpoch()));

	// 初始化信号
	QObject::connect(m_ui.buttonEnter, &QPushButton::clicked, this, &ConnectDialog::OnClickButtonConnect);
	QObject::connect(&m_connectTimer, &QTimer::timeout, this, &ConnectDialog::TryConnect);

	// 验证器
	QIntValidator* portValidator = new QIntValidator(1, 65535, m_ui.textPort);
	m_ui.textPort->setValidator(portValidator);

	// 设置 需要被设置为disable的控件列表
	m_needDisableWidgetList.push_back(m_ui.textIP);
	m_needDisableWidgetList.push_back(m_ui.textPort);
	m_needDisableWidgetList.push_back(m_ui.textClientId);
	m_needDisableWidgetList.push_back(m_ui.toggleSaveIP);
	m_needDisableWidgetList.push_back(m_ui.toggleAutoConnect);
	m_needDisableWidgetList.push_back(m_ui.buttonEnter);
}

ConnectDialog::~ConnectDialog() {
}

void ConnectDialog::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		// 记录鼠标按下时的全局坐标和窗口的偏移量
		m_dragPosition = event->globalPos() - frameGeometry().topLeft();
	}
	event->accept();
}

void ConnectDialog::mouseMoveEvent(QMouseEvent* event) {
	if (event->buttons() & Qt::LeftButton) {
		// 移动窗口到鼠标当前的全局坐标减去偏移量
		move(event->globalPos() - m_dragPosition);
	}
	event->accept();
}

void ConnectDialog::OnClickButtonConnect() {
	QString ip = m_ui.textIP->text();

	if (!StringUtil::isValidIPV4(ip)) {
		QMessageBox::information(NULL, "Lampyris Trade Station", "Invalid string format for ip address");
		return;
	}

	int port = m_ui.textPort->text().toInt();
	int clientId = m_ui.textClientId->text().toInt();
}

void ConnectDialog::TryConnect() {
	// if (!Application::getInstance()->connect(ip, port, clientId)) {
	// 
	// }
}

void ConnectDialog::SetControlEditable(bool value) {
	for (int i = 0; i < m_needDisableWidgetList.size(); i++) {
		m_needDisableWidgetList[i]->setDisabled(!value);
	}
}

