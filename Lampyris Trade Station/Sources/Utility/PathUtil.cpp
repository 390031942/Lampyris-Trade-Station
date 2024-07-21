/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "PathUtil.h"

// Windows Include(s)
#include <Windows.h>

QString PathUtil::getAppDocumentSavePath(const QString& path) {
	// ��ȡ�û��ĵ�Ŀ¼·��
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
	// ��ȡ��ǰִ���ļ�������·��
	wchar_t modulePath[MAX_PATH];
	GetModuleFileNameW(NULL, modulePath, MAX_PATH);

	// ������·������ȡĿ¼·��
	QString appDir = QFileInfo(QString::fromStdWString(modulePath)).dir().path();

	// ��������·��
	QString fullPath = QDir(appDir).absoluteFilePath(path);
	return fullPath;
}
