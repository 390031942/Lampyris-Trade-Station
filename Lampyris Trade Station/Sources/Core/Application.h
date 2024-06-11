/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <QString>
#include <EWrapper.h>
#include <EClientSocket.h>

class Application {
public:
	void           Connect(const QString& ip,int port,int clientId);
		          
	void           Disconnect();
		          
	bool           IsConnected();

	               Application();

	virtual       ~Application();
private:
	EWrapper*      m_wrapper;

	EClientSocket* m_clientSocket;
};