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

    SDL_DestroyTexture(e->sprites);
}

/*
===============================
Texture management
===============================
*/

void setTexture(GUIelement *e, int val) {
    switch(val) {
        case DEFAULT_TEXTURE:
            e->clip = {
                        .x = 0,
                        .y = 0,
                        .w = e->area.w,
                        .h = e->area.h
                      };
            break;
        case CLICK_TEXTURE:
            e->clip = {
                        .x = e->area.w,
                        .y = 0,
                        .w = e->area.w,
                        .h = e->area.h
                      };
            break;
       case HOVER_TEXTURE:
            e->clip = {
                        .x = 0,
                        .y = e->area.h,
                        .w = e->area.w,
                        .h = e->area.h
                      };
            break;
        case OTHER_TEXTURE:
            e->clip = {
                        .x = e->area.w,
                        .y = e->area.h,
                        .w = e->area.w,
                        .h = e->area.h
                      };
            break;
        case default:
            printf("error, unknown texture number: %d\n",val);
            break;
    }
}

