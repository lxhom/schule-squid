#include "bled.h"

class Squid {
private:
    // the movement, pos and so on
    // [2] = x, y | [3] = r, g, b
    int x = 0; int y = 1;
    int r = 0; int g = 1; int b = 2; 
    int speed[2];
    int windowSize[2];
    int squidSize;
    int direction[2];
    int position[2];
    int color[3];
    BLed* led;

public:

    void update();
    Squid(QWidget *parent=0);
    ~Squid();


};


