/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#include "PathUtil.h"

const QString& PathUtil::GetAppDocumentSavePath() {
    static QString path;

    if (path.size() <= 0) {
        // ��ȡ�û��ĵ�Ŀ¼·��
        QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        if (!documentsPath.isEmpty()) {
            path = QDir(documentsPath).filePath("Lampyris Trade System");
        }
    }

    return path;
}
