#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include "types.h"
#include <SDL2/SDL_Rect.h>

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
    cosnt char* name;
    SDL_Rect area;

    //event handlers
        //TODO make structure to simplify event handling
    event_handler click;
    event_handler unclick;
    event_handler mousemove;
    event_handler unhover;

    SDL_Rect clip;

    SDL_Texture *sprites; //nonchanging (ie non-moving) texture of element like button depressed or backgroind of slider not for things like the slider head that moves    

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
