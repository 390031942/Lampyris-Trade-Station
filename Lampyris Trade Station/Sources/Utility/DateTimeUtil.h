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
     * ������"March 29","September 2"���ַ������õ�QDate
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

		// �ָ��ַ��������Խ����·ݺ�����
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
     * ��ȡ��ǰϵͳʱ�� ��Ӧ�ĵ���������ʱ��
    */
	static QDateTime getCurrentEasternAmericaSystemDateTime() {
		QTimeZone easternTimeZone("America/New_York");

		QDateTime currentDateTime = QDateTime::currentDateTime();
		QDateTime easternDateTime = currentDateTime.toTimeZone(easternTimeZone);

		return easternDateTime;
	}
} // end of namespace 'DateTimeUtil'