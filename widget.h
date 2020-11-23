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
    Squid test;
};

class Squid {
private:
    // the movement, pos and so on
    // [2] = x, y | [3] = r, g, b
    int speed[2];
    int windowSize[2];
    int squidSize;
    int direction[2];
    int position[2];
    int color[3];

public:
    // constructor, deconstructor
    Squid(int width, int height);
    ~Squid();

    BLed* led;

};

Squid::Squid(int width, int height) {

    this->speed[0] = rand()%10+1;
    this->speed[1] = rand()%10+1;

    this->windowSize[0] = width;
    this->windowSize[1] = height;

    this->squidSize = rand()%15+5;

    // r%2 : 0 / 1 | r%2*2 : 0 / 2 | r%2*2-1 : -1 / 1 
    this->direction[0] = rand()%2*2-1;
    this->direction[1] = rand()%2*2-1;

    this->position[0] = rand()%(this->windowSize[0] - this->squidSize);
    this->position[1] = rand()%(this->windowSize[0] - this->squidSize);

    this->color[0] = rand()%200+25;
    this->color[1] = rand()%200+25;
    this->color[2] = rand()%200+25;


}

Squid::~Squid() {
    // do we really need this? nah
}


#endif // WIDGET_H
