#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    this->resize(500,500);
    for (int i=0; i<10; i++) {
        squids[i] = new Squid(this);
        timer = new QTimer(this);
        timer->connect(timer,SIGNAL(timeout()),this,SLOT(updater()));
        timer->start(16);
    }
}

void Widget::updater() {
    for (int i=0; i<10; i++) {
        squids[i]->update();
    }
}

Widget::~Widget() {
}

