#include "widget.h"
#include <QMouseEvent>
#include <QEvent>
#include <iostream>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    this->resize(500,500);
    for (int i=0; i<10; i++) {
        squids[i] = new Squid(this);
    }
    timer = new QTimer(this);
    timer->connect(timer,SIGNAL(timeout()),this,SLOT(updater()));
    timer->start(16);
    startpos[0] = -1;
}

void Widget::updater() {
    for (int i=0; i<10; i++) {
        squids[i]->update();
    }
}

Widget::~Widget() {
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    double delX = event->x()-Widget::startpos[0];
    double delY = event->y()-Widget::startpos[1];
    if (Widget::startpos[0] != -1) {
        for (int i=0; i<10; i++) {
            squids[i]->speed[0] += squids[i]->direction[0] * 0.05 * delX;
            squids[i]->speed[1] += squids[i]->direction[1] * 0.05 * delY;
        }
        Widget::startpos[0] = event->x();
        Widget::startpos[1] = event->y();
    }
}

void Widget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        Widget::startpos[0] = event->x();
        Widget::startpos[1] = event->y();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        Widget::startpos[0] = -1;
    }
}
