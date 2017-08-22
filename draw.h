#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h>

extern const int win_w;
extern const int win_h;

//constants
#define BGTYPE_PLAIN 0
#define BGTYPE_GRID 1

//background
void drawbg(int x,int y,int res,SDL_Texture *bg,SDL_Renderer *rend,int type);



//helpers
SDL_Rect getRect(int x,int y,int w,int h);
void moveRect(SDL_Rect *r,int x,int y);
#endif
