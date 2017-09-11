#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include "types.h"
#include "GUIelement.h"

/*
    a library for managing gui stuff, not application specific 
*/

typedef struct gui GUI;

//creation
GUI *createGUI(const char *name, void *app, const SDL_Rect win);

//deletion
void destroyGUI(GUI *g);

//drawing
void drawBG(GUI *g);//draws all the bgs for all the secs
void useDrawFunc(GUI *g, void *userdata, draw_func df, int sec);//uses df(rend,userdata) to draw to section sec, kinda overrides everything this library stands for but who cares?
void update(GUI *g);

//events
int handleEvents(GUI *g);

/*
============================================================
    gui elements
============================================================
*/

/*
    adds a button named name to g at *hitbox

    parameters:
        g: gui to add button to
        hitBox: the area checkd for clicks (relative to window)
        name: name of button (probably will be used for button graphics 
            (ie name_clicked, name_hover, etc))
        val: reference number (idk how useful it will be but whatevs)
        c: function to be called when button is clicked (is passed current app and val)
        
*/
void addButton(GUI *g, SDL_Rect *hitBox, const char *name, int val, callback c);


/*
    a display is a place you can draw to easy with draw_funcs

    parameters
        g: gui to add to
        hitbox: area on gui (relative to window)
        name: name of element
        val: ref number
        format: one of the SDL pixel formats
*/
void addDisplay(GUI *g, SDL_Rect *hitbox, const char *name, int val, int format);
    
/*
    a section simply defines a region of the ui so it can be maipulated easily
    
    parameters
        g: gui to add section to
        area: the rectangle defining the section
        bgDrawer: the function used to draw the sections background
*/
void addSection(GUI *g, SDL_Rect *area, draw_func bgDrawer);

#endif
