#include "GUIelement.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define DEFAULT_TEXTURE 1
#define CLICK_TEXTURE 2
#define HOVER_TEXTURE 3
#define OTHER_TEXTURE 4

/*
===============================
Destruction
===============================
*/

void destroyGUIelement(GUIelement *e) {
    //TODO add more cases as more are added

    switch (e->type) {
        case BUTTON:
            break;
        case DISPLAY:
            SDL_DestroyTexture(e->display.canvas);
            break;
    }
    
    destroyGUIeventHandler(e->eh);
    SDL_DestroyTexture(e->sprites);
}

/*
===============================
Texture management
===============================
*/

void setTexture(GUIelement *e, int val) {
    switch(val) {
        case DEFAULT_TEXTURE: {
            SDL_Rect r = {
                        .x = 0,
                        .y = 0,
                        .w = e->area.w,
                        .h = e->area.h
                      };
            e->clip = r;
            break;
        }
        case CLICK_TEXTURE: {
            SDL_Rect r = {
                        .x = e->area.w,
                        .y = 0,
                        .w = e->area.w,
                        .h = e->area.h
                      };
            e->clip = r;
            break;
        }
       case HOVER_TEXTURE: {
            SDL_Rect r = {
                        .x = 0,
                        .y = e->area.h,
                        .w = e->area.w,
                        .h = e->area.h
                      };
            e->clip = r;
            break;
        }
        case OTHER_TEXTURE: {
            SDL_Rect r = {
                        .x = e->area.w,
                        .y = e->area.h,
                        .w = e->area.w,
                        .h = e->area.h
                      };
            e->clip = r;
            break;
        }
        default:
            printf("error, unknown texture number: %d\n",val);
            break;
    }
}

