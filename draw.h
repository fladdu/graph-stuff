#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h>
#include <math.h>

extern const int win_w;
extern const int win_h;

//constants
#define BGTYPE_PLAIN 0
#define BGTYPE_GRID 1

//background
void drawGrid(SDL_Renderer *rend,void *app,void *args);
#endif
