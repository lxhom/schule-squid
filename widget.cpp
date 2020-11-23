#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    test = new Squid(this);
}

Widget::~Widget() {
}

