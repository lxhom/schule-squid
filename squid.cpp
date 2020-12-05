#include "squid.h"
#include "bled.h"
#include <QColor>

Squid::Squid(QWidget *parent) {
    widget = parent;

    speed[x] = rand()%20/10+0.5;
    speed[y] = rand()%20/10+0.5;

    windowSize[x] = parent->width();
    windowSize[y] = parent->height();

    squidSize[x] = squidSize[y] = rand()%30+20;
    
    // r%2 : 0 / 1 | r%2*2 : 0 / 2 | r%2*2-1 : -1 / 1 
    direction[x] = rand()%2*2-1;
    direction[y] = rand()%2*2-1;

    position[x] = rand()%(windowSize[x] - squidSize[x]);
    position[y] = rand()%(windowSize[y] - squidSize[y]);

    randomizeColors(color[r], color[g], color[b]);

    gravitation[x] = 0;
    gravitation[y] = -0.1;

    led = new BLed(parent);

    update();

}

void Squid::update() {
    windowSize[x] = widget->width();
    windowSize[y] = widget->height();

    bool collision = false;

    position[x] += direction[x] * speed[x];
    position[y] += direction[y] * speed[y];

    speed[x] -= direction[x] * gravitation[x];
    speed[y] -= direction[y] * gravitation[y];

    if (position[x] > windowSize[x] - squidSize[x]) {
        position[x] = (windowSize[x] - squidSize[x]) * 2 - position[x];
        direction[x] *= -1; 
        collision = true;
        speed[x] *= 0.95;
    }
    if (position[y] > windowSize[y] - squidSize[y]) {
        position[y] = (windowSize[y] - squidSize[y]) * 2 - position[y];
        direction[y] *= -1; 
        collision = true;
        speed[y] *= 0.95;
    }
    if (position[x] < 0) {
        position[x] *= -1;
        direction[x] *= -1; 
        speed[x] *= 0.95;
        collision = true;
    }
    if (position[y] < 0) {
        position[y] *= -1;
        direction[y] *= -1; 
        collision = true;
        speed[y] *= 0.95;
    }

    if (collision) {
        randomizeColors(color[r], color[g], color[b]);
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
    r = rand()%200+25;
    g = rand()%200+25;
    b = rand()%200+25;
}

Squid::~Squid() {
    // do we really need this? nah
}
