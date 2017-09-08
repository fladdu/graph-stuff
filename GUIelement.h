#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include "types.h"
#include <SDL2/SDL_Rect.h>

#include "button.h"
#include "display.h"

typedef struct SDL_Texture SDL_Texture; //forward declaration

typedef enum type {
    BUTTON,
    DISPLAY
} Type;

typedef struct guielement {
    Type type;
    int val;
    cosnt char* name;
    event_handler eh; //TODO better name
    SDL_Rect area;

    SDL_Texture *sprites; //nonchanging (ie non-moving) texture of element like button depressed or backgroind of slider not for things like the slider head that moves    

    union {
        Button button;
        Display display;
        //TODO add more as more are needed
    };
} GUIelement;


/*
===============================
Destruction
===============================
*/

void destroyGUIelement(GUIelement *e);

#endif
