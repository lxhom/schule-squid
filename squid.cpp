#include "squid.h"
#include "bled.h"

Squid::Squid(QWidget *parent) {

    this->speed[0] = rand()%10+1;
    this->speed[1] = rand()%10+1;

    this->windowSize[0] = parent->width();
    this->windowSize[1] = parent->height();

    this->squidSize = rand()%15+5;

    // r%2 : 0 / 1 | r%2*2 : 0 / 2 | r%2*2-1 : -1 / 1 
    this->direction[0] = rand()%2*2-1;
    this->direction[1] = rand()%2*2-1;

    this->position[0] = rand()%(this->windowSize[0] - this->squidSize);
    this->position[1] = rand()%(this->windowSize[0] - this->squidSize);

    this->color[0] = rand()%200+25;
    this->color[1] = rand()%200+25;
    this->color[2] = rand()%200+25;

    this->led = new BLed(parent);
    this->led->show();


}

Squid::~Squid() {
    // do we really need this? nah
}
