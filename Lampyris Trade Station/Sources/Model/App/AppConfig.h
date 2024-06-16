/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <vector>

// Project Include(s)
#include <Base/SerializeMacro.h>
#include <Base/SerializableSingleton.h>

class AppConfigDataObject:public SerializableSingleton<AppConfigDataObject> {
	LAMPYRIS_DECLARE_SERILIZATION(AppConfigDataObject);
public:
	/*
	 * 设置区域(支持zh-CN,和us-EN)
	*/
	inline void setLocale(const QString& locale) { this->m_locale = locale; }

	QString     getLocale() const { return this->m_locale; }
private:	    
	QString     m_locale;
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(AppConfigDataObject)
{
	LAMPYRIS_SERIALIZATION_FIELD(m_locale);
}
LAMPYRIS_SERIALIZATION_IMPL_END

#ifndef AppConfig
 #define AppConfig AppConfigDataObject::getInstance()
#endif // !AppConfig