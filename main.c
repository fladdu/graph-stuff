#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "draw.h"
#include <SDL2/SDL.h>


const int win_w = 1024;
const int win_h = 840;

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("failed to init SDL");
    }
    
    //init vars
    int offset_x = 0;
    int offset_y = 0;
    int bg_size = win_w + win_h;
    char res = argv[1]?atoi(argv[1]):20;

    //init SDL vars
    SDL_Window *main_win = SDL_CreateWindow("Graph Visualizer",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,win_w,win_h,0);
    SDL_Renderer *main_rend = SDL_CreateRenderer(main_win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *win_tx = SDL_GetRenderTarget(main_rend);
    SDL_Texture *bg_tx = NULL; //= SDL_CreateTexture(main_rend,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,bg_size,bg_size);
    SDL_Texture *fg_tx = SDL_CreateTexture(main_rend,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,win_w,win_h);
    
    //SDL_SetRenderDrawColor(main_rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(main_rend);
    SDL_RenderPresent(main_rend);

    
    //draw bg texture
    SDL_SetRenderTarget(main_rend, bg_tx);
    SDL_SetRenderDrawColor(main_rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(main_rend);
    SDL_SetRenderDrawColor(main_rend,0x70,0x70,0x70,SDL_ALPHA_OPAQUE);
    for(int i = 0; i < bg_size; i += bg_size/res) {
        SDL_RenderDrawLine(main_rend,i,0,i,bg_size);
    }
    for(int i = 0; i < bg_size; i += bg_size/res) {
        SDL_RenderDrawLine(main_rend,0,i,bg_size,i);
    }
    SDL_RenderPresent(main_rend);
    SDL_SetRenderTarget(main_rend, NULL);
    
    int quit = 0;
    //int 
    //main app loop
    while (!quit) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            //handle events here
            switch(e.type) {
                case SDL_QUIT: 
                    quit = 1;
                    break;
                case SDL_MOUSEMOTION:
                    if (e.motion.state & SDL_BUTTON_LMASK) {
                        offset_x += e.motion.xrel;
                        offset_y += e.motion.yrel;
                    }
                    break;
                //case SDL_MOUSEBUTTONDOWN
            }
        }
        
        //update logic
        
        /*
        if (offset_x < -(bg_size)) {
            offset_x = -bg_size;
        } else if (offset_x > bg_size) {
            offset_x = bg_size;
        }

        if (offset_y < -bg_size) {
            offset_y = -bg_size;
        } else if (offset_y > bg_size) {
            offset_y = bg_size;
        }*/
       
 
        //BEGIN DRAW-----------------------------------
        SDL_RenderClear(main_rend);
        
        //bg
        drawbg(offset_x,offset_y,res,bg_tx,main_rend,BGTYPE_GRID);

        SDL_RenderPresent(main_rend);
        //END DRAW-------------------------------------
    }

    SDL_DestroyTexture(fg_tx);
    SDL_DestroyTexture(win_tx);
    SDL_DestroyTexture(bg_tx);
    SDL_DestroyRenderer(main_rend);
    SDL_DestroyWindow(main_win);
    SDL_Quit();

}
