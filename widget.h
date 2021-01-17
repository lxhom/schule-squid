#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

#include "bled.h"
#include "bild.h"
#include "squid.h"
#include <QMouseEvent>

#include <QPainter>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Squid* squids[1000];
    QTimer* timer;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int startpos[2];
    void paintEvent(QPaintEvent*);
    int rectX, rectY, rectW, rectH, rectDir;

public slots:
    void updater();
};

#endif // WIDGET_H
