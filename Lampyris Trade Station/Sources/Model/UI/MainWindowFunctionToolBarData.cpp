/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "MainWindowFunctionToolBarData.h"
#include <Base/Localization.h>

LAMPYRIS_DECLARE_CLASS_BEGIN(MainWindowFunctionToolBarDataObject) 
{
	MainWindowFunctionToolBarDataObject::getInstance()->initFunctionData();
}
LAMPYRIS_DECLARE_CLASS_END;

void MainWindowFunctionToolBarDataObject::initFunctionData() {
	m_dataList = 
	{
		{ Localization->get("ToolBarFunctionTitle_1"),"TitleBarFunctionIcon/TitleBarFunctionIcon_1",[]() {} },
		{ Localization->get("ToolBarFunctionTitle_2"),"TitleBarFunctionIcon/TitleBarFunctionIcon_2",[]() {} },
	};
}
