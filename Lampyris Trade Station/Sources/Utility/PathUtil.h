/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <QDir>
#include <QStandardPaths>

namespace PathUtil {
    /*
	 * 获取 本程序数据 在系统用户文档文件夹 中的存储路径：
	 * 可选参数{path}:文件夹中的相对路径
	 * 返回：存储路径的绝对路径字符串
	*/
    QString getAppDocumentSavePath(const QString& path = QString());

	/*
	 * 获取 程序工作路径：
	 * 可选参数{path}:文件夹中的相对路径
	 * 返回：程序工作路径的绝对路径字符串
	*/
    QString getAppWorkPath(const QString& path = QString());
} // end of namespace 'PathUtil'