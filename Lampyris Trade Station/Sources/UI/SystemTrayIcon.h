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
 * 上下文菜单(通俗来说是鼠标右键菜单)项的节点，一对多关系
*/

struct ContextMenuItemLinkNode {
	bool isAction;
	union {
		QAction* action;
		QMenu*   menu;
	};

	// 父亲节点
	ContextMenuItemLinkNodePtr pParent = nullptr;

	// 子项的文本字符串->节点
	std::unordered_map<QString, ContextMenuItemLinkNodePtr> root2NodeMap;

	QString name;

	ContextMenuItemLinkNode();

	~ContextMenuItemLinkNode();
};

/* 给定一个路径，可以快速添加或删除上下文菜单的项,
 * 比如 给定一个路径"设置/当前项目/项目A",
 * 那么就会依次创建QMenu("设置"), QMenu("当前项目"),QAction("项目A"),
 * 利用QMenu的addMenu,addAction函数来设置菜单项之间的关系。
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