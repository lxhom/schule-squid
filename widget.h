#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

#include "bled.h"
#include "bild.h"
#include "squid.h"

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Squid* squids[1000];
    QTimer* timer;

public slots:
    void updater();
};

#endif // WIDGET_H
