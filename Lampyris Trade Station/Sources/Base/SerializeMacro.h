/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <fstream>
#include <vector>

// Boost Include(s)
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

// Project Include(s)
#include <Base/Singleton.h>
#include <Utility/PathUtil.h>
#include <Interface/ISerializable.h>

#ifndef LAMPYRIS_SERIALIZATION_MACRO
 #define LAMPYRIS_DECLARE_SERILIZATION(clsName)            \
	public:                                                \
	    template<class Archive>                            \
        void serialize(Archive& ar,unsigned int version);  \
                                                           \
		void serialize() {                                 \
            std::ofstream ofs(this->getStorageFileName()); \
            if(ofs.is_open()) {                            \
				boost::archive::binary_oarchive oa(ofs);   \
				oa << *this;                               \
			}                                              \
		}                                                  \
                                                           \
		void deserialize() {                               \
			std::ifstream ifs(this->getStorageFileName()); \
            if(ifs.is_open()) {                            \
				boost::archive::binary_iarchive ia(ifs);   \
				ia >> *this;                               \
			}                                              \
		}                                                  \
                                                           \
		const std::string& getStorageFileName() {		   \
			const static std::string fileName = 		   \
			 (PathUtil::getAppDocumentSavePath(   	       \
			        QString("archive/")                    \
                  + #clsName                               \
			      + ".bytes")).toUtf8().constData();       \
            return fileName;                               \
		}

 #define LAMPYRIS_SERIALIZATION_IMPL_BEGIN(clsName)        \
		template<class Archive>                            \
        void clsName::serialize(Archive& ar,unsigned int version)   

 #define LAMPYRIS_SERIALIZATION_IMPL_END

 #define LAMPYRIS_SERIALIZATION_FIELD(field)               \
	ar & boost::serialization::make_nvp(#field, field); 

#endif // !LAMPYRIS_SERIALIZATION_MACRO

class SerializeManager:public Singleton<SerializeManager> {
private:
	std::vector<ISerializable*> m_serializableList;
public:
	void start() {
		for (ISerializable* serializableObject : m_serializableList) {
			serializableObject->deserialize();
			serializableObject->postDeserialize();
		}
	}

	void destroy() {
		for (ISerializable* serializableObject : m_serializableList) {
			serializableObject->serialize();
		}
	}

	void registerObject(ISerializable* serializableObject) {
		if (serializableObject != nullptr) {
			m_serializableList.push_back(serializableObject);
		}
	}
};