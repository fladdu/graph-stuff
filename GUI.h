#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include "app.h"
#include "data.h"

//a library for managing gui stuff, not application specific 

typedef struct gui GUI;
typedef int (*draw_func)(GUI *,App *);//for drawing stuff to gui elements
typedef int (*callback)(App *,Data);//for buttons (ie. change cursor state) data for ref/amt/val

struct gui;

//creation
GUI *createGUI();

//deletion
void destroyGUI(GUI *g);

//drawing
void drawBG(GUI *g);//draws all the bgs for all the secs
void useDrawFunc(GUI *g, App *a, draw_func df, int sec);//uses df to draw to section sec

//events
void handleEvents(GUI *g, App *a);

//gui elements
void addButton(GUI *g, SDL_Rect *hitBox, const char *name, int val, callback c);
void addSection(GUI *g, SDL_Rect *area, draw_func bgDrawer);

#endif
