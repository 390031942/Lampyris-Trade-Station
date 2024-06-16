/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QMap>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Project Include(s)
#include <Base/Singleton.h>

namespace SingletonImpl {
class LocalizationClass final {
public:
                           LocalizationClass();
                          ~LocalizationClass();
    void                   setLocale(const QString& filePath);
    QString                get(const char* key);
    QString                format(const char* key,...);
private:                   
    void                   loadLocalizationClassFile();
    QMap<QString, QString> m_localizationclassMap;
    QString                m_localeFilePath;
};
} // end of namespace "SingletonImpl"