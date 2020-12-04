# Squid documentation

## This section covers the following files:
- [squid.h](/squid.h)
- [squid.cpp](/squid.cpp)

------

First, we should take a look at start of the header and the C++ file:

##### From [squid.h](/squid.h)

```h
#include "bled.h"
```

##### From [squid.cpp](/squid.cpp)

```cpp
#include "squid.h"
#include "bled.h"
#include <QColor>
```

Those are the libraries used in the Squid class. And on that note, we should look at the header file, or to be specific, the Squid class definition:

------

##### From [squid.h](/squid.h)

```h
class Squid {
private:
    int x = 0; int y = 1;
    int r = 0; int g = 1; int b = 2; 
    int speed[2];
    int windowSize[2];
    int squidSize[2];
    int direction[2];
    int position[2];
    int color[3];
    BLed* led;
    void randomizeColors(int& r, int& g, int& b);
public:
    void update();
    Squid(QWidget *parent=0);
    ~Squid();
};
```

------

`class Squid { ... }` just declares the class Squid.

------

### (`private`) `int x` | `int y` | `int r` | `int g` | `int b`

To demonstrate why I declared those variables I've made a example:

```cpp
position = [30,50]; // x position, y position
color = [255, 255, 128]; // red value, green value, blue value

// We could do this:
setXPosition(position[0]);
setYPosition(position[1]);
// And this:
setRedValue(color[0])
setGreenValue(color[1])
setBlueValue(color[2])


// But we can also do this:
x = 0; y = 1;
r = 0; g = 1; b = 2;

// And now we can do this:
setXPosition(position[x]);
setYPosition(position[y]);
// And this:
setRedValue(color[r])
setGreenValue(color[g])
setBlueValue(color[b])
```

It's not neccesary, but it just makes the code much cleaner and makess it easier to read.

------

### (`public`) `Squid(QWidget *parent)`

This is the constructor for Squid. The *parent pointer is used to acess the parent / widget.

Note: I'll  explain most of the code below in the matching class member explanations.

##### From [squid.cpp](/squid.cpp)

```cpp
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
```

This code basically initializes all the member variables of Squid. The only thing worth noting here is the `update()` at the end, it is used to show the Squid at the beginning. 

------

### (`private`) `int speed[2]`

This is the variable that stores the x and y speed of the squid.

It is defined here:

##### From [squid.cpp](/squid.cpp)

```cpp
speed[x] = rand()%2+1;
speed[y] = rand()%2+1;
```

`rand()%2` is used to get a integer with `0 <= n < 2`, which results in `[0,1]`. We add 1 to get `[1,2]`. We do that with x and y.

------

### (`private`) `int windowSize[2]`

This is the variable that stores the dimensions of the window.

It is defined here:

##### From [squid.cpp](/squid.cpp)

```cpp
windowSize[x] = parent->width();
windowSize[y] = parent->height();
```

This stores the window width and height into the windowSize array.

------

### (`private`) `int squidSize[2]`

This is the variable that stores the dimensions of the squid.

It is defined here:

##### From [squid.cpp](/squid.cpp)

```cpp
squidSize[x] = rand()%30+20;
squidSize[y] = rand()%30+20;
```

`rand()%30` is used to get a integer with `0 <= n < 30`, which results in `[0...29]`. We add 20 to get `[20...49]`. We do that with x and y.

------

### (`private`) `int direction[2]`

This is the variable that stores the x and y direction of the squid.

Note that this isn't supposed to be a speed variable, but the direction. The `update()` function uses `position += speed * direction`. `direction` should be -1 or 1.

It is defined here:

##### From [squid.cpp](/squid.cpp)

```cpp
direction[x] = rand()%2*2-1;
direction[y] = rand()%2*2-1;
```

`rand()%2` is used to get a integer with `0 <= n < 2`, which results in `[0,1]`. We multiply it by 2 to get `[0,2]` and then we subtract 1 to get `[-1,1]`. We do that with x and y.

------

### (`private`) `int position[2]`

This is the variable that stores the x and y position of the squid.

It is defined here:

##### From [squid.cpp](/squid.cpp)

```cpp
position[x] = rand()%(windowSize[x] - squidSize[x]);
position[y] = rand()%(windowSize[y] - squidSize[y]);
```

You might notice the `windowSize-squidSize` there. We need to do that because the squid could spawn out of the borders, or inside of the border. To make this more clear here's a visualisation:
###### [(Direct image link)](/docs/img/sizesubtraction.png)
![Illustration why we have to subtract the size](/docs/img/sizesubtraction.png)

We use `rand()%[maxPos]` to get a value that's still in the borders.

------

### (`private`) `int color[3]`

This variable is used to store the color of the squid.

It is defined here:

##### From [squid.cpp](/squid.cpp)

```cpp
randomizeColors(color[r], color[g], color[b]);
```

The `randomizeColors()` function is explained later.

------

### (`private`) `BLed* led`

This is the variable that stores the BLed.

It is defined here:

##### From [squid.cpp](/squid.cpp)

```cpp
led = new BLed(parent);
```

------

### (`private`) `void randomizeColors(int& r, int& g, int& b)`

This is the function which is used to randomize colors. I made this into a seperate function because it might be called in the future outside of the costructor.

We are passing the `r`, `g`, and `b` variables as references to modify the colors by using the reference operator `&`.

The function body is very simple:

##### From [squid.cpp](/squid.cpp)

```cpp
r = rand()%200+25;
g = rand()%200+25;
b = rand()%200+25;
```

------

### (`public`) `~Squid()`

This is the deconstructor. I think the code says everything that needs to be said:

##### From [squid.cpp](/squid.cpp)

```cpp
Squid::~Squid() {
    // do we really need this? nah
}
```

------

### (`public`) `void update()`

This is the update function which should be called every single frame. 

It does 3 main things:

- Move the squid.
- Check for collisions with the borders.
  - If it collides, move it into the box,
  - and change the direction.
  - And then we change the color.
- Then we show the updated squid.

------

To start, we declare a local variable called collision, and set it to false. We will come back to this later.

##### From [squid.cpp](/squid.cpp)

```cpp
int collision = false;
```

------

### Moving the squid
To move the squid, we can use a simple formula:

```
position = position + direction * speed
```

We can shorten that into this:

```
position += direction * speed
```

Now we just need to do that for every dimension, and we are good to go.

##### From [squid.cpp](/squid.cpp)

```cpp
position[x] += direction[x] * speed[x];
position[y] += direction[y] * speed[y];
```

------

### Collision detection

There are 2 if clauses for every dimension. The first one might seem a little bit confusing, but it's actually pretty simple.

```cpp
if (position > windowSize - squidSize) {...}
if (position <= 0) {...}
```

To understand why we should do `windowSize - squidSize` we should take a look at this:

###### [(Direct image link)](/docs/img/sizesubtraction.png)
![Illustration why we have to subtract the size](/docs/img/sizesubtraction.png)

The size needs to be subtracted from the border to make the whole squid collide with the walls, and not just the top left corner, a.k.a the position. Now that we have the collision, we can do something to avoid the squid going off-screen.

------

### Moving the squid into the box again

This is super easy for postion <= 0. We can just invert the value, and we're good to go.

##### From [squid.cpp](/squid.cpp)

```cpp
if (position[x] <= 0) {
    position[x] *= -1;
    // [...]
}
if (position[y] <= 0) {
    position[y] *= -1;
    // [...]
}
```
The other end of the box is a much harder task though. We have 2 things that weren't a problem before:

- We can't just do `*= -1` because that'd just move it out of the bounds again
- We need to compensate the squid size (see [Collision detection](#collision-detection))

We can just solve this step-by-step.

To move the squid the same way we did it with the -1 we can use this formula: `position = windowSize * 2 - position`. This might seem a bit weird, but its pretty obvious if we draw it:


```
<---------WindowSize---------->
|                             |
--------------Position---------->   [Out of the borders!]
|                             |
<---------WindowSize---------->
```
```
<---------WindowSize----------><---------WindowSize---------->
|                             |                              |
|                           <--------------Position-----------
|                             |
<---------WindowSize---------->
```

Now we just have to subtract the squid size (see [Collision detection](#collision-detection)), and we're good to go. We can do this like that: `position = (windowSize - squidSize) * 2 - position`. And we're done!


##### From [squid.cpp](/squid.cpp)

```cpp
if (position[x] > windowSize[x] - squidSize[x]) {
    position[x] = (windowSize[x] - squidSize[x]) * 2 - position[x];
    // [...]
}
if (position[y] > windowSize[y] - squidSize[y]) {
    position[y] = (windowSize[y] - squidSize[y]) * 2 - position[y];
    // [...]
}
if (position[x] <= 0) {
    position[x] *= -1;
    // [...]
}
if (position[y] <= 0) {
    position[y] *= -1;
    // [...]
}
```

------

### Changing the direction

This is super easy. We just need to do `direction *= -1` for the matching dimension.

##### From [squid.cpp](/squid.cpp)

```cpp (nice)
if (position[x] > windowSize[x] - squidSize[x]) {
    position[x] = (windowSize[x] - squidSize[x]) * 2 - position[x];
    direction[x] *= -1; 
    // [...]
}
if (position[y] > windowSize[y] - squidSize[y]) {
    position[y] = (windowSize[y] - squidSize[y]) * 2 - position[y];
    direction[y] *= -1; 
    // [...]
}
if (position[x] <= 0) {
    position[x] *= -1;
    direction[x] *= -1; 
    // [...]
}
if (position[y] <= 0) {
    position[y] *= -1;
    direction[y] *= -1; 
    // [...]
}

```

------

### Changing the color

To change the color, we can set a variable to false and set it to true if it collides, and check later if it is true. We do that so we dont make our if statement for each border 200 lines long.

We can update the update function now:

##### From [squid.cpp](/squid.cpp)

```cpp
void Squid::update() {
    int collision = false;

    // [...]

    if (position[x] > windowSize[x] - squidSize[x]) {
        position[x] = (windowSize[x] - squidSize[x]) * 2 - position[x];
        direction[x] *= -1; 
        collision = true;
    }
    if (position[y] > windowSize[y] - squidSize[y]) {
        position[y] = (windowSize[y] - squidSize[y]) * 2 - position[y];
        direction[y] *= -1; 
        collision = true;
    }
    if (position[x] <= 0) {
        position[x] *= -1;
        direction[x] *= -1; 
        collision = true;
    }
    if (position[y] <= 0) {
        position[y] *= -1;
        direction[y] *= -1; 
        collision = true;
    }

    if (collision) {
        randomizeColors(color[r], color[g], color[b]);
    }
// [...]
}
```

------

### Applying / showing the changes

This is done with 3 statements that don't really need much explanation:

##### From [squid.cpp](/squid.cpp)

```cpp
led->setGeometry(
    position[x],position[y],
    squidSize[x],squidSize[y]
);
led->setColor(QColor(
    color[r], color[g], color[b]
));
led->show();
```
------

The whole update function now looks like this:


##### From [squid.cpp](/squid.cpp)

```cpp
void Squid::update() {
    int collision = false;

    position[x] += direction[x] * speed[x];
    position[y] += direction[y] * speed[y];

    if (position[x] > windowSize[x] - squidSize[x]) {
        position[x] = (windowSize[x] - squidSize[x]) * 2 - position[x];
        direction[x] *= -1; 
        collision = true;
    }
    if (position[y] > windowSize[y] - squidSize[y]) {
        position[y] = (windowSize[y] - squidSize[y]) * 2 - position[y];
        direction[y] *= -1; 
        collision = true;
    }
    if (position[x] <= 0) {
        position[x] *= -1;
        direction[x] *= -1; 
        collision = true;
    }
    if (position[y] <= 0) {
        position[y] *= -1;
        direction[y] *= -1; 
        collision = true;
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
```

------

###### Last documented commit: [cb8d07](https://github.com/lxhom/schule-squid/commit/cb8d070f28e6ab46022b259babf2ac26d232e32c)