#include "bled.h"

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
    // hi
    Squid(QWidget *parent=0);
    ~Squid();

    BLed* led;

};


