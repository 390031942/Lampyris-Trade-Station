/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
#pragma once

// QT Include(s)
#include <QHBoxLayout>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class QStyledGroupBoxInternal :public QWidget {
	Q_OBJECT
public:
	enum DisplayMode {
		IconOnly,
		TextOnly,
		Both,
		MaxEnum = 0x7fffffff
	};
protected:
	void paintEvent(QPaintEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void leaveEvent(QEvent* e);
public:
	QStyledGroupBoxInternal(DisplayMode mode,
		                    const QVector<QPixmap>& icons,
		                    const QVector<QString>& infos);
private:
	QVector<QPixmap>  m_icons;
	QVector<QString>  m_infos;
	DisplayMode       m_mode;

	static const int  sc_icon_width = 32;
	static const int  sc_icon_height = 32;

	static const int  sc_bounding_rect_radius = 3;
	static const int  sc_max_button_count = 16;

	int               m_hoveredMask;
	int               m_maxTextWidth;
	int               m_fontHeight;
Q_SIGNALS:
	void signalSelectedIndexChanged(int index);
};

class QStyledGroupBox :public QWidget {
	Q_OBJECT
private:
	QHBoxLayout*             m_layout;
	QStyledGroupBoxInternal* m_button;
public:
	QStyledGroupBox(const QVector<QPixmap>& icons,const QVector<QString>& infos);
Q_SIGNALS:
	void signalSelectedIndexChanged(int index);
};