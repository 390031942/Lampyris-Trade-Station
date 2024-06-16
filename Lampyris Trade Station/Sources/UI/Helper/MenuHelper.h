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
 * �����Ĳ˵�(ͨ����˵������Ҽ��˵�)��Ľڵ㣬һ�Զ��ϵ
*/
struct MenuItemLinkNode {
	// �Ƿ���Ҷ�ӽڵ㣬Ҳ����QAction
	bool    isAction;
	// �ڵ�����
	QString name;
	union {
		QAction* action = nullptr;
		QMenu*   menu;
	};
	// ���׽ڵ�
	MenuItemLinkNodePtr pParent = nullptr;
	// ������ı��ַ���->�ڵ�
	QMap<QString, MenuItemLinkNodePtr> root2NodeMap;

	         MenuItemLinkNode();
	virtual ~MenuItemLinkNode();
};

/* ����һ��·�������Կ�����ӻ�ɾ�������Ĳ˵�����,
 * ���� ����һ��·��"����/��ǰ��Ŀ/��ĿA",
 * ��ô�ͻ����δ���QMenu("����"), QMenu("��ǰ��Ŀ"),QAction("��ĿA"),
 * ����QMenu��addMenu,addAction���������ò˵���֮��Ĺ�ϵ��
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