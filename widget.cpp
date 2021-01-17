#include "widget.h"
#include <QMouseEvent>
#include <QEvent>
#include <iostream>
#include <QPaintEvent>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    this->resize(500,500);
    for (int i=0; i<10; i++) {
        squids[i] = new Squid(this);
    }
    timer = new QTimer(this);
    timer->connect(timer,SIGNAL(timeout()),this,SLOT(updater()));
    timer->start(16);
    startpos[0] = -99999;
    this->rectW = 100;
    this->rectH = 50;
    this->rectX = this->width() / 2 - this->rectW;
    this->rectY = this->height() / 2 - this->rectH;
    rectDir = 1;

}


void Widget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.fillRect(rectX, rectY, rectW, rectH, Qt::green);
}

void Widget::updater() {
    for (int i=0; i<10; i++) {
        squids[i]->update();
    }
    rectX+= 2 * rectDir;
    if (rectX < 0) { rectX *= -1; rectDir *= -1; }
    if (rectX > width() - rectW) { rectX = (width() - rectW) * 2 - rectX; rectDir *= -1; }
    update();





    /*QPen pen;

    pen.setColor(Qt::green);
    pen.setWidth(5);


    QPainter painter(this);
    painter.setPen(pen);

    painter.setBrush(Qt::SolidPattern);
    painter.drawRect(QRect(80,120,200,100));

    //painter.fillRect(rectX, rectY, rectW, rectH, Qt::green);
    //this->update();*/
}

Widget::~Widget() {
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    double delX = event->x()-Widget::startpos[0];
    double delY = event->y()-Widget::startpos[1];
    if (Widget::startpos[0] != -99999) {
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
        Widget::startpos[0] = -99999;
    }
}
