/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// Project Include(s)
#include <Base/SerializeMacro.h>
#include <Base/SerializableSingleton.h>

// Qt Include(s)
#include <QColor>

class AppUIStyle:public SerializableSingleton<AppUIStyle> {
	LAMPYRIS_DECLARE_SERILIZATION(AppUIStyle);
public:
    // 行情中证券 "名字" 颜色
    QColor quoteNameColor = QColor(223, 251, 164, 255);

    // 行情 通用 颜色
    QColor quoteNormalColor = QColor(200, 200, 200, 255);

    // 行情 上涨 颜色
    QColor quoteRiseColor = QColor(255, 92, 92, 255);

    // 行情 下跌 颜色
    QColor quoteFallColor = QColor(56, 229, 101, 255);

    // 行情 金额 颜色
    QColor quoteMoneyColor = QColor(0, 255, 255, 255);

    // 普通的白色
    QColor normalWhiteColor = QColor(255, 255, 255, 255);

    // 提示-黄色
    QColor tipYellowColor = QColor(255, 255, 39, 255);

    // 提示-红色
    QColor tipRedColor = QColor(255, 92, 92, 255);

    // 暗色-浅背景
    QColor darkLessBgColor = QColor(53, 53, 53, 255);

    // 暗色-深背景
    QColor darkLessBgColor = QColor(31, 31, 31, 255);

    // 涨跌颜色反转
    bool reverseRiseFallColor = false;

    QColor getRiseFallColor(float percentage) {
        if (percentage > 0.0f) {
            return !reverseRiseFallColor ? quoteRiseColor : quoteFallColor;
        }
        else if (percentage < 0.0f) {
            return reverseRiseFallColor ? quoteRiseColor : quoteFallColor;
        }

        return normalWhiteColor;
    }
};

LAMPYRIS_SERIALIZATION_IMPL_BEGIN(AppUIStyle)
{
    LAMPYRIS_SERIALIZATION_FIELD(quoteNameColor);
    LAMPYRIS_SERIALIZATION_FIELD(quoteNormalColor);
    LAMPYRIS_SERIALIZATION_FIELD(quoteRiseColor);
    LAMPYRIS_SERIALIZATION_FIELD(quoteFallColor);
    LAMPYRIS_SERIALIZATION_FIELD(quoteMoneyColor);
    LAMPYRIS_SERIALIZATION_FIELD(normalWhiteColor);
    LAMPYRIS_SERIALIZATION_FIELD(tipYellowColor);
    LAMPYRIS_SERIALIZATION_FIELD(tipRedColor);
    LAMPYRIS_SERIALIZATION_FIELD(darkLessBgColor);
    LAMPYRIS_SERIALIZATION_FIELD(darkLessBgColor);
    LAMPYRIS_SERIALIZATION_FIELD(reverseRiseFallColor);
}
LAMPYRIS_SERIALIZATION_IMPL_END

#ifndef UIStyle
 #define UIStyle AppUIStyle::getInstance()
#endif // !UIStyle