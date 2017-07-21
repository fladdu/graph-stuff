#include "display.h"
struct display {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
};


//creation-----------------
Display *createDisplay(int width, int height) {
    Display *ret = malloc(sizeof(Display));

    ret->window = SDL_CreateWindow("GraphVis", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    ret->renderer = SDL_CreateRenderer(ret->window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    ret->texture = SDL_GetRenderTarget(ret->renderer);

    return ret;
}

//deletion-------------------
void destroyDisplay(Display *d) {
    SDL_DestroyTexture(d->texture);
    SDL_DestroyRenderer(d->renderer);
    SDL_DestroyWindow(d->window);
}

//drawing-background-----------------
void wipeDisplay(Display *d) {
    //TODO add background texture
    SDL_SetRenderDrawColor(d->renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(d->renderer);
    //SDL_RenderPresent(d->renderer);
}

void updateDisplay(Display *d) {
    SDL_RenderPresent(d->renderer);
}

//drawing----------------------------------
void drawSquare(Display *d, int x, int y, int l) {
    SDL_SetRenderDrawColor(d->renderer, 0xff, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = r.h = l;
    SDL_RenderFillRect(d->renderer, &r);
}
