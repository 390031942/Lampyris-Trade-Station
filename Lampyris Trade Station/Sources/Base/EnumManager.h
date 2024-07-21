/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <unordered_map>
#include <vector>
#include <string>

// Project Include(s)
#include "Singleton.h"
#include "ClassInitializer.h"
#include "Localization.h"

class EnumManager:public Singleton<EnumManager> {
public:
    inline void beginEnum(const QString& enumName) 
    { Q_ASSERT(m_currentEnumName.isEmpty()); m_currentEnumName = enumName;}

    inline void endEnum() 
    { Q_ASSERT(!m_currentEnumName.isEmpty()); m_currentEnumName = QString(); }

    inline void registerEnum(const QString& fieldName, int value, const char* description, bool localized = false) 
    { Q_ASSERT(!m_currentEnumName.isEmpty()); m_enumData[m_currentEnumName].push_back(
      { fieldName, value, description != nullptr ? (localized ? description : Localization->get(description)) : fieldName }); }

    inline const std::vector<std::tuple<QString, int, QString>>& getEnum(const QString& enumName) const 
    { return m_enumData.at(enumName);  }
private:
    QString m_currentEnumName;
    std::unordered_map<QString, std::vector<std::tuple<QString, int, QString>>> m_enumData;
};

#ifndef LAMPYRIS_ENUM_MANAGER_MACRO
#define LAMPYRIS_DECLARE_ENUM_BEGIN(enumName) \
    namespace __hidden { \
    static int __hidden##enumName = [](){ \
        EnumManager::getInstance()->beginEnum(#enumName);

#define LAMPYRIS_ENUM_FIELD_NO_DESC(field) \
    EnumManager::getInstance()->registerEnum(#field,field,nullptr);

#define LAMPYRIS_ENUM_FIELD(field, description) \
    EnumManager::getInstance()->registerEnum(#field,field,description);

#define LAMPYRIS_ENUM_FIELD_LOCALIZED(field, description) \
    EnumManager::getInstance()->registerEnum(#field,field,description,true);

#define LAMPYRIS_DECLARE_ENUM_END \
        EnumManager::getInstance()->endEnum(); \
        return 1; \
    }();}
#endif // !LAMPYRIS_ENUM_MANAGER_MACRO