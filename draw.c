#include "draw.h"
#include <SDL2/SDL_rect.h>

//TODO this is test struct, DELETE
typedef struct test {
    int ox;
    int oy;
    int res;
} Test;

//background
void drawGrid(SDL_Renderer *rend, void *app, void *args) {
    
    Test temp = *((Test*) app);
    SDL_Rect r;
    
    SDL_RenderGetViewport(rend, &r);
    
    SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(rend);
    //draw grid
    SDL_SetRenderDrawColor(rend,0x66,0x66,0x66,SDL_ALPHA_OPAQUE);
    for(int i = temp.ox%temp.res; i < r.w; i+=temp.res) {
        SDL_RenderDrawLine(rend,i,0,i,r.h);
    }
    for(int i = temp.oy%temp.res; i < r.h; i+=temp.res) {
        SDL_RenderDrawLine(rend,0,i,r.w,i);
    }
}
