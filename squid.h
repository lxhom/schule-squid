#include "bled.h"

class Squid {
public:
    // the movement, pos and so on
    // [2] = x, y | [3] = r, g, b
    int x = 0; int y = 1;
    int r = 0; int g = 1; int b = 2; 
    double speed[2];
    int windowSize[2];
    int squidSize[2];
    int direction[2];
    double position[2];
    int color[3];
    double gravitation[2];
    BLed* led;
    void randomizeColors(int& r, int& g, int& b);
    QWidget *widget;
    void update();
    Squid(QWidget *parent=0);
    ~Squid();
};


