/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s) 
#include "PathUtil.h"

// QT Include()
#include <QApplication>

QString PathUtil::getAppDocumentSavePath(const QString& path) {
    // ��ȡ�û��ĵ�Ŀ¼·��
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString ret = QDir(QDir(documentsPath).filePath("Lampyris Trade System")).filePath(path);
    return ret;
}

QString PathUtil::getAppWorkPath(const QString& path) {
    QString ret = QDir(QApplication::applicationDirPath()).filePath(path);
    return ret;
}
