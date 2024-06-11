/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "ConnectDialog.h"

// QT Include(s)
#include <QMouseEvent>
#include <QDateTime>

ConnectDialog::ConnectDialog(QWidget *parent)
	: QDialog(parent) {
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

}
