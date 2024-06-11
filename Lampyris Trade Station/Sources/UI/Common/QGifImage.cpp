/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "QGifImage.h"

// QT Include(s)
#include <QVBoxLayout>

QGifImage::QGifImage(QWidget *parent) : QWidget(parent) {
    m_gifLabel = new QLabel(this);
    m_gifMovie = new QMovie(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_gifLabel);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    // 帧更新时将更新QLabel显示的图片
    QObject::connect(m_gifMovie, &QMovie::frameChanged, [this]() {
        m_gifLabel->setPixmap(QPixmap::fromImage(m_gifMovie->currentImage()));
    });
}

QGifImage::~QGifImage() {
    m_gifMovie->stop();
    delete m_gifMovie;
    delete m_gifLabel;
}

void QGifImage::setGifImagePath(const QString &path) {
    // 设置 GIF 文件路径并开始播放
    m_gifMovie->setFileName(path);
    m_gifMovie->start();
}

void QGifImage::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    m_gifLabel->setFixedSize(size());
}
