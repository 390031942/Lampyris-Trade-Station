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
	 * ��ȡ ���������� ��ϵͳ�û��ĵ��ļ��� �еĴ洢·����
	 * ��ѡ����{path}:�ļ����е����·��
	 * ���أ��洢·���ľ���·���ַ���
	*/
	static QString getAppDocumentSavePath(const QString& path);

	/*
	 * ��ȡ ������·����
	 * ��ѡ����{path}:�ļ����е����·��
	 * ���أ�������·���ľ���·���ַ���
	*/
	static QString getAppWorkPath(const QString& path);
};// end of namespace 'PathUtil'