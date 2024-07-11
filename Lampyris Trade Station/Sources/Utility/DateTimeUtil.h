/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QMap>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QTimeZone>

namespace DateTimeUtil {
	/*
     * 解析如"March 29","September 2"的字符串并得到QDate
    */
	static QDate parseEnglishMonthDayString(const QString& dateStr) {
		static const QMap<QString, int> monthNames = {
			{"January"  , 1},{"February", 2}, {"March"   , 3}, {"April"   , 4},
			{"May"      , 5},{"June"    , 6}, {"July    ", 7}, {"August"  , 8},
			{"September", 9},{"October" , 10},{"November", 11},{"December", 12}
		};

		int month = 0;
		int day = 0;
		bool ok = false;

		// 分割字符串并尝试解析月份和日期
		QStringList parts = dateStr.split(QRegExp("[ ,]"), QString::SkipEmptyParts);
		if (parts.count() == 2) {
			month = monthNames[parts.at(0)];
			day = parts.at(1).toInt(&ok);
		}

		if (ok && month > 0 && day > 0) {
			return QDate(QDate::currentDate().year(), month, day);
		}
		else {
			return QDate();
		}
	}

	/*
     * 获取当前系统时间 对应的的美国东部时间
    */
	static QDateTime getCurrentEasternAmericaSystemDateTime() {
		QTimeZone easternTimeZone("America/New_York");

		QDateTime currentDateTime = QDateTime::currentDateTime();
		QDateTime easternDateTime = currentDateTime.toTimeZone(easternTimeZone);

		return easternDateTime;
	}
} // end of namespace 'DateTimeUtil'