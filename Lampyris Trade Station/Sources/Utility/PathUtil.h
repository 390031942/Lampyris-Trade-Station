/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <QDir>
#include <QStandardPaths>

namespace PathUtil {
    /*
	 * 获取 本程序数据 在系统用户文档文件夹 中的存储路径：
	 * 返回：存储路径的绝对路径字符串
	*/
    const QString& GetAppDocumentSavePath();
} // end of namespace 'PathUtil'