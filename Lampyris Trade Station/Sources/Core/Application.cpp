/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "Application.h"

bool Application::connect(const QString& ip, int port, int clientId) {
	if (m_clientSocket == nullptr) {
		return false;
	}
	return m_clientSocket->eConnect(ip.toUtf8().constData(), port, clientId);
}

void Application::disconnect() {
	if (isConnected()) {
		m_clientSocket->eDisconnect();
	}
}

bool Application::isConnected() {
	if (m_clientSocket == nullptr) {
		return false;
	}

	return m_clientSocket->isConnected();
}

Application::Application() {
}

Application::~Application() {
	
}

void Application::readConfigFromFile() {
} 
