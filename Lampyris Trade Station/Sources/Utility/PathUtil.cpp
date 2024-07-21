/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "PathUtil.h"

// Windows Include(s)
#include <Windows.h>

QString PathUtil::getAppDocumentSavePath(const QString& path) {
	// 获取用户文档目录路径
	QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
	documentsPath = QDir(documentsPath).filePath("LampyrisTradeSystem");
	QDir dir(documentsPath);
	if (!dir.exists()) {
		dir.mkpath(documentsPath);
	}
	if (path.size() == 0) {
		return documentsPath;
	}
	QString destPath = QDir(documentsPath).filePath(path);
	QFileInfo fileInfo(destPath);
	dir = QDir(fileInfo.absoluteDir().absolutePath());
	if (!dir.exists()) {
		dir.mkpath(destPath);
	}
	return destPath;
}

QString PathUtil::getAppWorkPath(const QString& path) {
	// 获取当前执行文件的完整路径
	wchar_t modulePath[MAX_PATH];
	GetModuleFileNameW(NULL, modulePath, MAX_PATH);

	// 从完整路径中提取目录路径
	QString appDir = QFileInfo(QString::fromStdWString(modulePath)).dir().path();

	// 构建绝对路径
	QString fullPath = QDir(appDir).absoluteFilePath(path);
	return fullPath;
}
