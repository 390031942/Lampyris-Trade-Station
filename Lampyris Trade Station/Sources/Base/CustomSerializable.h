/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>
#include <QDateTime>

// Boost Include(s)
#include <boost/serialization/nvp.hpp>

/*
 * 如果想要一个自定义类型支持boost.serialization库进行序列化，
 * 需要在这里定义 非侵入式序列化/序列化方法
*/
namespace boost::serialization {
	/* QString begin */
	template<class Archive>
	void save(Archive& ar, const QString& str, unsigned int version) {
		std::string stdStr = str.toUtf8().constData();
		ar & boost::serialization::make_nvp("QString", stdStr);
	}

	template<class Archive>
	void load(Archive& ar, QString& str, unsigned int version) {
		std::string stdStr;
		ar& boost::serialization::make_nvp("QString", stdStr);
		str = QString::fromStdString(stdStr);
	}
	/* QString end*/

	/* QDateTime begin */
	template<class Archive>
	void save(Archive& ar, const QDateTime& dateTime, unsigned int version) {
		QString dateTimeStr = dateTime.toString(Qt::ISODate);
		ar& boost::serialization::make_nvp("dateTime", dateTimeStr);
	}

	template<class Archive>
	void load(Archive& ar, QDateTime& dateTime, unsigned int version) {
		QString dateTimeStr;
		ar& boost::serialization::make_nvp("dateTime", dateTimeStr);
		dateTime = QDateTime::fromString(dateTimeStr, Qt::ISODate);
	}
	/* QDateTime end*/

} // end of namespace 'boost::serialization'

BOOST_SERIALIZATION_SPLIT_FREE(QString);
BOOST_SERIALIZATION_SPLIT_FREE(QDateTime);
