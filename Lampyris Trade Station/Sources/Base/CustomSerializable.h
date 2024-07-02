/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QString>
#include <QDateTime>
#include <QColor>

// Boost Include(s)
#include <boost/serialization/nvp.hpp>

/*
 * �����Ҫһ���Զ�������֧��boost.serialization��������л���
 * ��Ҫ�����ﶨ�� ������ʽ���л�/���л�����
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

	/* QVector4D begin */
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

	/* QColor begin */
	template<class Archive>
	void save(Archive& ar, const QColor& color, unsigned int version) {
		ar& boost::serialization::make_nvp("r", color.red());
		ar& boost::serialization::make_nvp("g", color.green());
		ar& boost::serialization::make_nvp("b", color.blue());
		ar& boost::serialization::make_nvp("a", color.alpha());
	}

	template<class Archive>
	void load(Archive& ar, QColor& color, unsigned int version) {
		int r, g, b, a;
		ar& boost::serialization::make_nvp("r", r);
		ar& boost::serialization::make_nvp("g", g);
		ar& boost::serialization::make_nvp("b", b);
		ar& boost::serialization::make_nvp("a", a);

		color = QColor(r, g, b, a);
	}
	/* QColor end*/
} // end of namespace 'boost::serialization'

BOOST_SERIALIZATION_SPLIT_FREE(QString);
BOOST_SERIALIZATION_SPLIT_FREE(QDateTime);
BOOST_SERIALIZATION_SPLIT_FREE(QColor);
