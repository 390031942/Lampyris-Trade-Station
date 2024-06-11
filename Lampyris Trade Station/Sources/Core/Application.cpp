/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#include "Application.h"

void Application::Connect(const QString& ip, int port, int clientId) {

}

void Application::Disconnect() {
}

bool Application::IsConnected() {
	return false;
}

Application::Application():
	m_wrapper(nullptr),m_clientSocket(nullptr) {
}

Application::~Application() {
	
}
