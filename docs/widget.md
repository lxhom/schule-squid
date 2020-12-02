# Squid documentation

## This section covers the following files:
- [widget.h](widget.h)
- [widget.cpp](widget.cpp)

------

First, we should take a look at the header file.

##### From [widget.h](widget.h)
```h
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

#include "bled.h"
#include "bild.h"
#include "squid.h"

// [...]

#endif // WIDGET_H
```

This part of the code just loads the libraries for the program (and checks for WIDGET_H).

------
Now we have to actually define the Widget object.
##### From [widget.h](widget.h)
```h
class Widget : public QWidget {
    Q_OBJECT
public:
    // [...]
public slots:
    // [...]
};
```

Here is the start of the Widget object definition. We have to use a QWidget to acess the window.

------

Now we can take a look at the members of `Widget`.

------

### (`public`) `Widget()`
This function is called when the window is opened, or to be precise, when the Widget gets initialized. It executes the following code:

##### From [widget.cpp](widget.cpp)
```cpp
Widget::Widget(QWidget *parent) : QWidget(parent) {
    this->resize(500,500);
    for (int i=0; i<10; i++) {
        squids[i] = new Squid(this);
    }
    timer = new QTimer(this);
    timer->connect(timer,SIGNAL(timeout()),this,SLOT(updater()));
    timer->start(16);
}
```
This might seem like a lot, but its fairly simple. Lets go through it.

The `Widget::Widget(QWidget *parent) : QWidget(parent) { ... }` just declares the constructor. There are a few parameters here, but they're not so important right now.

`this->resize(500,500)` just sets the window dimensions to 500x500.

Now we have the for loop (`for (int i=0; i<10; i++) { ... }`) which counts from 0-9 and stores it into a variable. This for loop has the following body:

##### From [widget.cpp](widget.cpp)
```cpp
squids[i] = new Squid(this);
```
It constructs a new Squid (`new Squid(this)`) and stores it into the squids array (`squids[i] =`) (we'll talk about that later)

Here is the end of the for loop body.

Now we initialize the timer:
##### From [widget.cpp](widget.cpp)
```cpp
timer = new QTimer(this);
timer->connect(timer,SIGNAL(timeout()),this,SLOT(updater()));
timer->start(16);
```
What it does | The code
------ | ------
It constructs | `timer = new QTimer(this);`
a timer which waits for the timeout signal from the timer `updater()` | `timer->connect(timer,SIGNAL(timeout()),`
and calls `updater()` | `this,SLOT(updater()));`
once every 16ms. | `timer->start(16);`

If you're wondering why i picked exactly 16ms: I want the program to run at 60fps, and to get that we have to divide one second, or 1000 milliseconds, through 60. This results in 16.66666 and I just rounded it to 16.

Now we only have the end of the constructor function and that's it.

------

### (`public`) `~Widget()`

This is the destructor. You'll know what it does when I show you the function:

##### From [widget.cpp](widget.cpp)
```cpp
Widget::~Widget() {
}
```

It does nothing.

------

### (`public`) `Squid* squids[1000]`

This is the array that we mentioned previously which contains the instances of Squid. It has 1000 entries, but doesn't use all of them. I do that so I dont have to change this value every time I change the amount of Squid's.

------

### (`public`) `QTimer* timer`

This is the timer that we mentioned above.

That's all.

------

### (`public slots`) `void updater`

This is the function connected to the timer which just calls the update function for each instance of Squid. It looks like this:

##### From [widget.cpp](widget.cpp)
```cpp
void Widget::updater() {
    for (int i=0; i<10; i++) {
        squids[i]->update();
    }
}
```

This just loops through 0-9 in the Squids array and calls the `update()` function.

------

###### Last documented commit: [4e80f1](4e80f176ab2e3420eaf460dd1d95cdfae21e8901)
