#include "squid.h"
#include "bled.h"
#include <QColor>

Squid::Squid(QWidget *parent) {

    speed[0] = rand()%10+1;
    speed[1] = rand()%10+1;

    windowSize[0] = parent->width();
    windowSize[1] = parent->height();

    squidSize = rand()%30+20;

    // r%2 : 0 / 1 | r%2*2 : 0 / 2 | r%2*2-1 : -1 / 1 
    direction[0] = rand()%2*2-1;
    direction[1] = rand()%2*2-1;

    position[0] = rand()%(windowSize[0] - squidSize);
    position[1] = rand()%(windowSize[0] - squidSize);

    color[0] = rand()%200+25;
    color[1] = rand()%200+25;
    color[2] = rand()%200+25;

    led = new BLed(parent);

    update();

}

void Squid::update() {
    led->setGeometry(
        position[0],position[1],
        squidSize,squidSize
    );

    led->setColor(QColor(
        color[0], color[1], color[2]
    ));


    led->show();
}

Squid::~Squid() {
    // do we really need this? nah
}
