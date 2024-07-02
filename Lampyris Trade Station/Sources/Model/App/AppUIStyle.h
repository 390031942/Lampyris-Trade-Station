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
    // ������֤ȯ "����" ��ɫ
    QColor quoteNameColor = QColor(223, 251, 164, 255);

    // ���� ͨ�� ��ɫ
    QColor quoteNormalColor = QColor(200, 200, 200, 255);

    // ���� ���� ��ɫ
    QColor quoteRiseColor = QColor(255, 92, 92, 255);

    // ���� �µ� ��ɫ
    QColor quoteFallColor = QColor(56, 229, 101, 255);

    // ���� ��� ��ɫ
    QColor quoteMoneyColor = QColor(0, 255, 255, 255);

    // ��ͨ�İ�ɫ
    QColor normalWhiteColor = QColor(255, 255, 255, 255);

    // ��ʾ-��ɫ
    QColor tipYellowColor = QColor(255, 255, 39, 255);

    // ��ʾ-��ɫ
    QColor tipRedColor = QColor(255, 92, 92, 255);

    // ��ɫ-ǳ����
    QColor darkLessBgColor = QColor(53, 53, 53, 255);

    // ��ɫ-���
    QColor darkLessBgColor = QColor(31, 31, 31, 255);

    // �ǵ���ɫ��ת
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