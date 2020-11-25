#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    this->resize(500,500);
    for (int i=0; i<10; i++) {
        squids[i] = new Squid(this);
    }
}

Widget::~Widget() {
}

