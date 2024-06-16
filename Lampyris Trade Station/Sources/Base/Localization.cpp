/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "Localization.h"
#include <Model/App/AppConfig.h>

// C Include(s)
#include <stdarg.h>

SingletonImpl::LocalizationClass::LocalizationClass() {
    m_localeFilePath = "locales/localization_" + AppConfig->getLocale() + ".txt";
    m_localeFilePath = PathUtil::getAppWorkPath(m_localeFilePath);

    loadLocalizationClassFile();
}

SingletonImpl::LocalizationClass::~LocalizationClass() {
}

void SingletonImpl::LocalizationClass::setLocale(const QString& filePath) {
    m_localeFilePath = filePath;
    loadLocalizationClassFile();
}

QString SingletonImpl::LocalizationClass::get(const char* key) {
    if (m_localizationclassMap.contains(key)) {
        return m_localizationclassMap.value(key, QString());
    }

    return key;
}

QString SingletonImpl::LocalizationClass::format(const char* key, ...) {
    va_list args;
    va_start(args, key);
    QString text = get(key);

    if (!text.isEmpty()) {
        return QString::vasprintf(key, args);
    }

    va_end(key);

    return key;
}

void SingletonImpl::LocalizationClass::loadLocalizationClassFile() {
    QFile file(m_localeFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");   
    while (!in.atEnd()) {
        QString line = in.readLine();
        line = line.trimmed();
        if (!line.startsWith("//") && !line.isEmpty()) {
            int commaPos = line.indexOf(',');
            if (commaPos != -1) {
                QString key = line.left(commaPos).trimmed();
                QString value = line.mid(commaPos + 1).trimmed();
                m_localizationclassMap[key] = value.remove('"');
            }
        }
    }
    file.close();
}
