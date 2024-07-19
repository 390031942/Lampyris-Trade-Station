/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QIcon>
#include <QString>

// Project Include(s)
#include <Base/Singleton.h>
#include <Base/ClassInitializer.h>

class MainWindowFunctionToolBarDataObject:public Singleton<MainWindowFunctionToolBarDataObject> {
	LAMPYRIS_DECLARE_CLASS_INITIALIZE(MainWindowFunctionToolBarDataObject);
	struct MainWindowFunctionToolBarData {
		QString               name;
		QString              icon;
		std::function<void()> action;
	};
	typedef std::vector<MainWindowFunctionToolBarData> DataList;
public:
	inline const DataList& getFunctionData() const { return this->m_dataList; }
private:
	void     initFunctionData();
	DataList m_dataList;
};