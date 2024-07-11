/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QDir>
#include <QStandardPaths>
#include <QApplication>

class PathUtil {
public:
	/*
	 * 获取 本程序数据 在系统用户文档文件夹 中的存储路径：
	 * 可选参数{path}:文件夹中的相对路径
	 * 返回：存储路径的绝对路径字符串
	*/
	static QString getAppDocumentSavePath(const QString& path);

	/*
	 * 获取 程序工作路径：
	 * 可选参数{path}:文件夹中的相对路径
	 * 返回：程序工作路径的绝对路径字符串
	*/
	static QString getAppWorkPath(const QString& path);
};// end of namespace 'PathUtil'