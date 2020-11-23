#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "bled.h"
#include "bild.h"

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};

class Squid {
private:
    // the movement, pos and so on
    // [2] = x, y | [3] = r, g, b
    int speed[2];
    int direction[2];
    int position[2];
    int color[3];
    int size;
    int borders[2];
public:
    // constructor, deconstructor
    Squid(int width, int height);
    ~Squid();

    BLed* led;

};

Squid::Squid(int width, int height) {

}

Squid::~Squid() {
    // do we really need this? nah
}


#endif // WIDGET_H
