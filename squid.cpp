#include "squid.h"
#include "bled.h"
#include <QColor>

Squid::Squid(QWidget *parent) {

    speed[x] = rand()%2+1;
    speed[y] = rand()%2+1;

    windowSize[x] = parent->width();
    windowSize[y] = parent->height();

    squidSize[x] = rand()%30+20;
    squidSize[y] = rand()%30+20;

    // r%2 : 0 / 1 | r%2*2 : 0 / 2 | r%2*2-1 : -1 / 1 
    direction[x] = rand()%2*2-1;
    direction[y] = rand()%2*2-1;

    position[x] = rand()%(windowSize[x] - squidSize[x]);
    position[y] = rand()%(windowSize[y] - squidSize[y]);

    randomizeColors(color[r], color[g], color[b]);

    led = new BLed(parent);

    update();

}

void Squid::update() {
    position[x] += direction[x] * speed[x];
    position[y] += direction[y] * speed[y];

    if (position[x] > windowSize[x] - squidSize[x]) {
        position[x] = (windowSize[x] - squidSize[x]) * 2 - position[x];
        direction[x] *= -1; 
    }
    if (position[y] > windowSize[y] - squidSize[y]) {
        position[y] = (windowSize[y] - squidSize[y]) * 2 - position[y];
        direction[y] *= -1; 
    }
    if (position[x] <= 0) {
        position[x] *= -1;
        direction[x] *= -1; 
    }
    if (position[y] <= 0) {
        position[y] *= -1;
        direction[y] *= -1; 
    }


    led->setGeometry(
        position[x],position[y],
        squidSize[x],squidSize[y]
    );
    led->setColor(QColor(
        color[r], color[g], color[b]
    ));
    led->show();
}

void Squid::randomizeColors(int& r, int& g, int& b) {
    for (int i=0; i<3; i++) {
        r = rand()%200+25;
        g = rand()%200+25;
        b = rand()%200+25;
    }

}

Squid::~Squid() {
    // do we really need this? nah
}
