/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "ConnectDialog.h"
#include <Core/Application.h>
#include <Utility/StringUtil.h>
#include <UI/Common/MessageBox.h>
#include <UI/MainWindow.h>
#include <Base/Localization.h>

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
	QObject::connect(m_ui.buttonEnter, &QPushButton::clicked, this, &ConnectDialog::onClickButtonConnect);
	QObject::connect(&m_connectTimer, &QTimer::timeout, this, &ConnectDialog::tryConnect);

	QObject::connect(m_ui.toggleSaveIP, &QCheckBox::stateChanged, [this](int state) {
		IBGatewayHistoryConnection->setSaveIP(m_ui.toggleSaveIP->isChecked());
	});
	QObject::connect(m_ui.toggleAutoConnect, &QCheckBox::stateChanged, [this](int state) {
		if (state) {
			m_ui.toggleSaveIP->setChecked(true);
		}

		IBGatewayHistoryConnection->setSaveIP(m_ui.toggleSaveIP->isChecked());
		IBGatewayHistoryConnection->setAutoConnect(m_ui.toggleAutoConnect->isChecked());
    });

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

	// ��ʱ��
	m_connectTimer.setInterval(1000);
	
	// Tips
	m_ui.textIP->setToolTip(Localization->get("ConnectDialog_1"));
	m_ui.textPort->setToolTip(Localization->get("ConnectDialog_2"));
	m_ui.textClientId->setToolTip(Localization->get("ConnectDialog_3"));
	m_ui.toggleSaveIP->setToolTip(Localization->get("ConnectDialog_4"));
	m_ui.toggleAutoConnect->setToolTip(Localization->get("ConnectDialog_5"));

	// �����л�Ĭ��ֵ
	m_ui.toggleSaveIP->setChecked(IBGatewayHistoryConnection->getSaveIP());
	m_ui.toggleAutoConnect->setChecked(IBGatewayHistoryConnection->getAutoConnect());
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

void ConnectDialog::onClickButtonConnect() {
	QString ip = m_ui.textIP->text();

	if (!StringUtil::isValidIPV4(ip)) {
		QMessageBox::information(NULL, "Lampyris Trade Station", "Invalid string format for ip address");
		return;
	}

	m_connectInfo.ip = ip;
	m_connectInfo.port = m_ui.textPort->text().toInt();
	m_connectInfo.clientId = m_ui.textClientId->text().toInt();

	setControlEditable(false);
	m_connectTimer.start();
	m_ui.textInfo->setText(Localization->get("ConnectDialog_8"));
}

void ConnectDialog::tryConnect() {
	if (!Application::connect(m_connectInfo.ip, m_connectInfo.port, m_connectInfo.clientId)) {
		m_retryCount++;
		if (m_retryCount > m_maxRetryCount) {
			m_retryCount = 0;
			m_connectTimer.stop();
			MessageBox->info(Localization->get("ConnectDialog_7"));
			m_ui.textInfo->setText("");
			setControlEditable(true);
		}
		else {
			m_ui.textInfo->setText(Localization->format("ConnectDialog_6", m_retryCount));
		}
	}
	else { // ���ӳɹ�
		m_connectTimer.stop();
		IBGatewayHistoryConnection->storage(m_connectInfo);
		this->deleteLater();

		// ��������
		MainWindow* mainWindow = new MainWindow;
		mainWindow->show();
	}
}

void ConnectDialog::setControlEditable(bool value) {
	for (int i = 0; i < m_needDisableWidgetList.size(); i++) {
		m_needDisableWidgetList[i]->setDisabled(!value);
	}
}

