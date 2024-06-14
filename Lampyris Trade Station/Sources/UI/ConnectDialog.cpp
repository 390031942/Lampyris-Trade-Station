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

	// Gif ����
	m_ui.loginGif->setGifImagePath(":/Resources/Gif/Gif_0005.gif");

	// �����ռλ
	m_ui.textIP->setPlaceholderText("IP Address");
	m_ui.textPort->setPlaceholderText("Port");
	m_ui.textClientId->setPlaceholderText("Client ID");

	// ���ش��ڱ�����
	setWindowFlags(Qt::FramelessWindowHint);

	// Tab˳��
	QWidget::setTabOrder(m_ui.textIP, m_ui.textPort);
	QWidget::setTabOrder(m_ui.textPort, m_ui.textClientId);
	QWidget::setTabOrder(m_ui.textClientId, m_ui.toggleSaveIP);
	QWidget::setTabOrder(m_ui.toggleSaveIP, m_ui.toggleAutoConnect);
	QWidget::setTabOrder(m_ui.toggleAutoConnect, m_ui.buttonEnter);
	QWidget::setTabOrder(m_ui.buttonEnter, m_ui.textIP);

	// ��ʼ��һ��ClientId,����ʱ�������
	m_ui.textClientId->setText(QString("%1").arg((int)QDateTime::currentSecsSinceEpoch()));

	// ��ʼ���ź�
	QObject::connect(m_ui.buttonEnter, &QPushButton::clicked, this, &ConnectDialog::OnClickButtonConnect);
	QObject::connect(&m_connectTimer, &QTimer::timeout, this, &ConnectDialog::TryConnect);

	// ��֤��
	QIntValidator* portValidator = new QIntValidator(1, 65535, m_ui.textPort);
	m_ui.textPort->setValidator(portValidator);

	// ���� ��Ҫ������Ϊdisable�Ŀؼ��б�
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
		// ��¼��갴��ʱ��ȫ������ʹ��ڵ�ƫ����
		m_dragPosition = event->globalPos() - frameGeometry().topLeft();
	}
	event->accept();
}

void ConnectDialog::mouseMoveEvent(QMouseEvent* event) {
	if (event->buttons() & Qt::LeftButton) {
		// �ƶ����ڵ���굱ǰ��ȫ�������ȥƫ����
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

