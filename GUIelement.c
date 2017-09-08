#include "GUIelement.h"
#include <SDL2/SDL.h>

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
            
     

