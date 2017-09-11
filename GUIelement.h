#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include "types.h"
#include <SDL2/SDL_rect.h>
#include "GUIevent.h"

#include "button.h"
#include "display.h"

#define DEFAULT_TEXTURE 1
#define CLICK_TEXTURE 2
#define HOVER_TEXTURE 3
#define OTHER_TEXTURE 4

typedef struct SDL_Texture SDL_Texture; //forward declaration

typedef enum type {
    BUTTON,
    DISPLAY
} Type;

typedef struct guielement {
    Type type;
    int val;
    const char* name;
    SDL_Rect area;

    //event handlers
        //TODO make structure to simplify event handling
    GUIeventHandler* eh;

    SDL_Rect clip;

    SDL_Texture *sprites; 

    /*  
        Difference between 'sprites' vs element specific textures
                    
        eg. 'Slider' gui element
         __________^____
        |_________/ \___|
           ^      |_| 
           |
           |       ^
           Lslider | texture managed in 'sprites' texture (below)
                   |
                head texture would be managed
                in the 'slider' (//TODO) structure
    */

    /*
        sprites:
        +---------+----------+
        |         |          |
        |         |          |
        |    1    |     2    |
        | default | clicked  |
        |         |          |
        |         |          |
        +---------+----------+
        |         |          |
        |         |          |
        |    3    |     4    |
        |  hover  |   other  |
        |         |          |
        |         |          |
        +---------+----------+
        
        
    */

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


/*
===============================
Texture management
===============================
*/

void setTexture(GUIelement *e, int val);

#endif
