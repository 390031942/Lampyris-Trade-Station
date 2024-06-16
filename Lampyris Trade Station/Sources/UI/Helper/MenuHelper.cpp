/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "MenuHelper.h"
#include <Utility/MemoryUtil.h>

MenuItemLinkNode::MenuItemLinkNode() {
}

MenuItemLinkNode::~MenuItemLinkNode() {
	if (isAction) {
		LAMPYRIS_SAFE_DELETE(this->action);
	}
	else {
		LAMPYRIS_SAFE_DELETE(this->menu);
	}
}

MenuHelper::MenuHelper(QMenu* menu):m_menu(menu) {
	m_rootNode = std::make_shared<MenuItemLinkNode>();
	m_rootNode->name = "HiddenRoot";
	m_rootNode->menu = menu;
}

MenuHelper::~MenuHelper() {
	
}

bool MenuHelper::add(const QString& path, std::function<void()> callback) {
	return false;
}

bool MenuHelper::remove(const QString& path) {
	return false;
}
