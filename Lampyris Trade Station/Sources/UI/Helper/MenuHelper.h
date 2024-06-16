/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// SID Inelude(s)
#include <unordered_map>
#include <memory>
#include <functional>

// QT Inelude(s)
#include <QString>
#include <QMap>

class QMenu;
class QAction;

struct MenuItemLinkNode;
typedef std::shared_ptr<MenuItemLinkNode> MenuItemLinkNodePtr;

/*
 * 上下文菜单(通俗来说是鼠标右键菜单)项的节点，一对多关系
*/
struct MenuItemLinkNode {
	// 是否是叶子节点，也就是QAction
	bool    isAction;
	// 节点名称
	QString name;
	union {
		QAction* action = nullptr;
		QMenu*   menu;
	};
	// 父亲节点
	MenuItemLinkNodePtr pParent = nullptr;
	// 子项的文本字符串->节点
	QMap<QString, MenuItemLinkNodePtr> root2NodeMap;

	         MenuItemLinkNode();
	virtual ~MenuItemLinkNode();
};

/* 给定一个路径，可以快速添加或删除上下文菜单的项,
 * 比如 给定一个路径"设置/当前项目/项目A",
 * 那么就会依次创建QMenu("设置"), QMenu("当前项目"),QAction("项目A"),
 * 利用QMenu的addMenu,addAction函数来设置菜单项之间的关系。
*/
class MenuHelper {
public:	               
	                     MenuHelper(QMenu* menu);
	virtual             ~MenuHelper();
	bool                 add(const QString& path, std::function<void()> callback);
	bool                 remove(const QString& path);
private:               
	QMenu*               m_menu;
	MenuItemLinkNodePtr  m_rootNode;
};