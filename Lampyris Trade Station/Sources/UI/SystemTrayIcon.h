/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// SID Inelude(s)
#include <unordered_map>

// Qt Include(s)
#include <QSystemTrayIcon>

// Project Include(s)
#include <Base/Singleton.h>
#include <Base/Delegate.h>

class QMenu;
class QAction;

struct ContextMenuItemLinkNode;
typedef std::shared_ptr<ContextMenuItemLinkNode> ContextMenuItemLinkNodePtr;

/*
 * �����Ĳ˵�(ͨ����˵������Ҽ��˵�)��Ľڵ㣬һ�Զ��ϵ
*/

struct ContextMenuItemLinkNode {
	bool isAction;
	union {
		QAction* action;
		QMenu*   menu;
	};

	// ���׽ڵ�
	ContextMenuItemLinkNodePtr pParent = nullptr;

	// ������ı��ַ���->�ڵ�
	std::unordered_map<QString, ContextMenuItemLinkNodePtr> root2NodeMap;

	QString name;

	ContextMenuItemLinkNode();

	~ContextMenuItemLinkNode();
};

/* ����һ��·�������Կ�����ӻ�ɾ�������Ĳ˵�����,
 * ���� ����һ��·��"����/��ǰ��Ŀ/��ĿA",
 * ��ô�ͻ����δ���QMenu("����"), QMenu("��ǰ��Ŀ"),QAction("��ĿA"),
 * ����QMenu��addMenu,addAction���������ò˵���֮��Ĺ�ϵ��
*/

class ContextMenuHelper {
public:
	ContextMenuHelper(QMenu* menu);

	virtual ~ContextMenuHelper();
	
	bool add(const QString& path, std::function<void()> callback);

	bool remove(const QString& path);
private:
	QMenu* m_menu;
	ContextMenuItemLinkNodePtr* m_rootNode;
};

class SystemTrayIcon : public Singleton<SystemTrayIcon> {
	typedef void* MessageUserData;
	typedef std::vector<std::tuple<QString, std::function<void()>>> DynamicPathInfoList;
public:
	Delegate<MessageUserData> onClickMessageCallback;

	SystemTrayIcon();

	virtual ~SystemTrayIcon();

	void create();
	void Destroy();
	void showMessage(const QString& message, MessageUserData userData = nullptr);
	void show();
	void addDynamicContextMenuItem(const QString& path, std::function<void()> callback);
	void removeDynamicContextMenuItem(const QString& path);
private:
	bool m_created;
	QMenu* m_menu;
	ContextMenuHelper* m_helper;
	DynamicPathInfoList m_dynamicPathList;
};