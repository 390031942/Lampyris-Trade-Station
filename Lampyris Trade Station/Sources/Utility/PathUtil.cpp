/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s) 
#include "PathUtil.h"

// QT Include()
#include <QApplication>

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
    QString ret = QDir(QApplication::applicationDirPath()).filePath(path);
    return ret;
}
