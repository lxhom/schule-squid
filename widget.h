#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "bled.h"
#include "bild.h"
#include "squid.h"

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Squid* squids[1000];
};

#endif // WIDGET_H
