/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

#include <QDir>
#include <QStandardPaths>

namespace PathUtil {
    /*
	 * ��ȡ ���������� ��ϵͳ�û��ĵ��ļ��� �еĴ洢·����
	 * ���أ��洢·���ľ���·���ַ���
	*/
    const QString& GetAppDocumentSavePath();
} // end of namespace 'PathUtil'