/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// STD Include(s)
#include <type_traits>
#include <concepts>

// Project Include(s)
#include <Interface/ISerializable.h>

template<class T>
class SerializableHandler {
public:
	SerializableHandler(ISerializable* object) {
		this->m_object = object;

		m_object->deserialize();
		m_object->postDeserialize();
	}

	~SerializableHandler() {
		m_object->serialize();
	}

	ISerializable* getPointer() inline { return m_object; }
private:
	ISerializable* m_object;
};

template<class T>
class SerializableSingleton:ISerializable {
public:
	static T* getInstance() {
		static SerializableHandler<T> handler(new T);
		return handler.getPointer();
	}
};