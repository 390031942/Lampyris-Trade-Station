/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <QDir>
#include <QStandardPaths>

namespace PathUtil {
    /*
	 * ��ȡ ���������� ��ϵͳ�û��ĵ��ļ��� �еĴ洢·����
	 * ��ѡ����{path}:�ļ����е����·��
	 * ���أ��洢·���ľ���·���ַ���
	*/
    QString getAppDocumentSavePath(const QString& path = QString());

	/*
	 * ��ȡ ������·����
	 * ��ѡ����{path}:�ļ����е����·��
	 * ���أ�������·���ľ���·���ַ���
	*/
    QString getAppWorkPath(const QString& path = QString());
} // end of namespace 'PathUtil'