/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Qt Include(s)
#include <QSystemTrayIcon>

// Project Include(s)
#include <Base/Singleton.h>
#include <Base/Delegate.h>

class SystemTrayIcon : public Singleton<SystemTrayIcon> {
	typedef void* MessageUserData;
	typedef std::vector<std::tuple<QString, std::function<void()>>> DynamicPathInfoList;
public:
	Delegate<MessageUserData> onClickMessageCallback;
	                          SystemTrayIcon();
	virtual                  ~SystemTrayIcon();
	void                      create();
	void                      Destroy();
	void                      showMessage(const QString& message, MessageUserData userData = nullptr);
	void                      show();
	void                      addDynamicContextMenuItem(const QString& path, std::function<void()> callback);
	void                      removeDynamicContextMenuItem(const QString& path);
private:			          
	bool                      m_created;
	QMenu*                    m_menu;
	MenuHelper*               m_helper;
	DynamicPathInfoList       m_dynamicPathList;
};