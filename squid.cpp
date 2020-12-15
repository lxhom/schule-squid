#include "squid.h"
#include "bled.h"
#include <QColor>

Squid::Squid(QWidget *parent) {

    // Store parent into a var
    widget = parent;

    // Initialize squidSize[x,y] for anything between [20..50] with step=1
    squidSize[x] = squidSize[y] = rand()%31+20;

    // Initialize window size
    windowSize[x] = parent->width();
    windowSize[y] = parent->height();

    // loop: dimension for d in [x,y] (0,1)
    for (int d = x; d <= y; d++) {

        // Initialize speed for anything between [0.5..2.5] with step=0.1
        speed[d] = rand()%21/10+0.5;

        // Initialize direction for anything between [-1..1] with step=2 (-1|1)
        direction[d] = rand()%2*2-1;

        // Initialize position for anything between [0...windowSize[x] - squidSize[x]] with step=1
        position[d] = rand()%(windowSize[d] - squidSize[d]);
    }

    // Initialize color for anything between [25..225] with step=1
    randomizeColors(color[r], color[g], color[b]);

    // Initialize the gravitation values
    gravitation[x] = 0;
    gravitation[y] = -0.1;

    // Create the LED's
    led = new BLed(parent);

    // Call the update function
    update();

}

void Squid::update() {

    // update borders
    windowSize[x] = widget->width();
    windowSize[y] = widget->height();

    // init collisions array
    bool collisions[2] = {false, false};

    // loop: dimension for d in [x,y] (0,1)
    for (int d = x; d <= y; d++) {
        // Position

        // pos update
        position[d] += direction[d] * speed[d];

        // Speed

        // speed update
        speed[d] -= direction[d] * gravitation[d];

        // negative speed correction
        if (speed[d] < 0) { 
            speed[d] *= -1; 
            direction[d] *= -1; 
        }

        // Border collision

        // border collision for pos = windowsize
        if (position[d] > windowSize[d] - squidSize[d]) {
            position[d] = (windowSize[d] - squidSize[d]) * 2 - position[d];
            collisions[d] = true;
        }

        // border collision for pos = 0
        if (position[d] < 0) {
            position[d] *= -1;
            collisions[d] = true;
        }

        // border collision corrections and other stuff
        if (collisions[d]) {

            // direction correction
            direction[d] *= -1;

            // speed correction
            speed[d] *= 0.95;
            speed[d] -= 0.25;
            if (speed[d] < 0) speed[d] = 0;

            // color change
            if (speed[d] != 0) {
                randomizeColors(color[r], color[g], color[b]);
            }
        }
    }

    // Apply the changes
    led->setGeometry(
        position[x],position[y],
        squidSize[x],squidSize[y]
    );
    led->setColor(QColor(
        color[r], color[g], color[b]
    ));
    led->show();
}

// Initialize {r,g,b} for anything between [25..225] with step=1
void Squid::randomizeColors(int& r, int& g, int& b) {
    r = rand()%201+25;
    g = rand()%201+25;
    b = rand()%201+25;
}

Squid::~Squid() {
    // do we really need this? nah
}
