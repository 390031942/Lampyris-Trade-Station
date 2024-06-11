/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// QT Include(s)
#include <QWidget>
#include <QLabel>
#include <QMovie>

class QGifImage : public QWidget {
    Q_OBJECT

public:
    explicit QGifImage(QWidget *parent = nullptr);

            ~QGifImage();

    void     setGifImagePath(const QString &path);
protected:
    void     resizeEvent(QResizeEvent *event) override;
private:
    QLabel*  m_gifLabel;

    QMovie*  m_gifMovie;
};