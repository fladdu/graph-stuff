#ifndef DISPLAY_H
#define DISPLAY_H

#include "types.h"

typedef struct SDL_Texture SDL_Texture; //forward declaration

typedef struct display {
    SDL_Texture *canvas;
} Display;


#endif
