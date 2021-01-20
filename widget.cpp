#include <QPixmap>
#include "widget.h"
#include <QMouseEvent>
#include <QEvent>
#include <iostream>
//#include <QPaintEvent>
#include <QLabel>

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
    QPixmap* image = new QPixmap(":/img/dvd.png");
    scaledImage = image->scaledToWidth(this->rectW);
    this->rectH = scaledImage.height();
    this->rectX = rand()%(this->width()-rectW);
    this->rectY = rand()%(this->height()-rectH);
    this->rectDirX = 1;
    this->rectDirY = -1;
    this->color = new QColor(0, 255, 0);
    label = new QLabel(this);
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter painter(&scaledImage);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(scaledImage.rect(), *color);
    painter.end();
}

void Widget::updater() {    
    for (int i=0; i<10; i++) {
        squids[i]->update();
    }
    bool col = false;
    rectX+= 2 * rectDirX;
    rectY+= 2 * rectDirY;
    if (rectX < 0) { rectX *= -1; rectDirX *= -1; col = true; }
    if (rectX > this->width() - rectW) { rectX = (this->width() - rectW) * 2 - rectX; rectDirX *= -1; col = true; }
    if (rectY < 0) { rectY *= -1; rectDirY *= -1; col = true; }
    if (rectY > this->height() - rectH) { rectY = (this->height() - rectH) * 2 - rectY; rectDirY *= -1; col = true; }
    if (col) { color = new QColor(rand()%201+25,rand()%201+25,rand()%201+25);update();}
    label->setPixmap(scaledImage);
    label->setGeometry(rectX, rectY, rectW, rectH);





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
