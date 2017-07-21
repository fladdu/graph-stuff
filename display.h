#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct display Display;

struct display;

//creation-----------------
Display *createDisplay(int width, int height);

//deletion-------------------
void destroyDisplay(Display *d);

//drawing-background--------------
void wipeDisplay(Display *d);
void updateDisplay(Display *d);

//drawing----------------------------
void drawSquare(Display *d, int x, int y, int l);
#endif
