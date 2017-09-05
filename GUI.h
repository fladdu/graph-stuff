#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include "app.h"
#include "data.h"

/*
    a library for managing gui stuff, not application specific 
*/

typedef struct gui GUI;
typedef int (*draw_func)(SDL_Renderer *,App *);//for drawing stuff to gui elements
typedef int (*callback)(App *,Data);//for buttons/other elements (ie. change cursor state) data for ref/amt/val

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

/*
============================================================
    gui elements
============================================================
*/

/*
    //TODO
    make general 'GUIelement' union for other things like sliders and stuff
    so will change this method

    parameters:
        g: gui to add button to
        hitBox: the area checkd for clicks (relative to window)
        name: name of button (probably will be used for button graphics 
            (ie name_clicked, name_hover, etc))
        val: reference number (idk how useful it will be but whatevs)
        c: function to be called when button is clicked (is passed current app and val given to addButton)
        
*/
void addButton(GUI *g, SDL_Rect *hitBox, const char *name, int val, callback c);

/*
    a section simply defines a region of the ui so it can be maipulated easily
    
    parameters
        g: gui to add section to
        area: the rectangle defining the section
        bgDrawer: the function used to draw the sections background
*/
void addSection(GUI *g, SDL_Rect *area, draw_func bgDrawer);

#endif
