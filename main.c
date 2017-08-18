#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>

void drawbg(int,int,SDL_Texture*,SDL_Renderer*);


const int win_w = 1024;
const int win_h = 840;

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("failed to init SDL");
    }
    
    //init vars
    int offset_x = 0;
    int offset_y = 0;

    //init SDL vars
    SDL_Window *main_win = SDL_CreateWindow("Graph Visualizer",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,win_w,win_h,0);
    SDL_Renderer *main_rend = SDL_CreateRenderer(main_win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *win_tx = SDL_GetRenderTarget(main_rend);
    SDL_Texture *bg_tx = SDL_CreateTexture(main_rend,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,win_w,win_h);
    SDL_Texture *fg_tx = SDL_CreateTexture(main_rend,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,win_w,win_h);
    
    //SDL_SetRenderDrawColor(main_rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(main_rend);
    SDL_RenderPresent(main_rend);

    
    //draw bg texture
    SDL_SetRenderTarget(main_rend, bg_tx);
    SDL_SetRenderDrawColor(main_rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(main_rend);
    SDL_SetRenderDrawColor(main_rend,0x70,0x70,0x70,SDL_ALPHA_OPAQUE);
    for(int i = 0; i < 2*win_w; i += 100) {
        SDL_RenderDrawLine(main_rend,i,0,i,win_h);
    }
    for(int i = 0; i < 2*win_h; i += 100) {
        SDL_RenderDrawLine(main_rend,0,i,win_w,i);
    }
    SDL_RenderPresent(main_rend);
    SDL_SetRenderTarget(main_rend, NULL);
    
    int quit = 1;
    //main app loop
    while (quit) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            //handle events here
            if (e.type == SDL_QUIT) quit = 0;

            switch(e.type) {
                case SDL_QUIT: 
                    quit = 0;
                    break;
                case SDL_MOUSEMOTION:
                    //offset_x = e.motion.x;
                    break;
            }
        }
        
        //update logic here
        if (offset_x < -win_w) {
            offset_x = -win_w;
        } else if (offset_x > win_w) {
            offset_x = win_w;
        }

        if (offset_y < -win_h) {
            offset_y = -win_h;
        } else if (offset_y > win_h) {
            offset_y = win_h;
        }
       
 
        //DRAW
        SDL_RenderClear(main_rend);
        
        //draw bg
        drawbg(offset_x,offset_y,bg_tx,main_rend);


        SDL_RenderPresent(main_rend);
    }

    SDL_DestroyTexture(fg_tx);
    SDL_DestroyTexture(win_tx);
    SDL_DestroyTexture(bg_tx);
    SDL_DestroyRenderer(main_rend);
    SDL_DestroyWindow(main_win);
    SDL_Quit();

}

void drawbg(int x,int y,SDL_Texture *bg,SDL_Renderer *rend) {
        SDL_Rect bg1_s;
        SDL_Rect bg1_d;
        
        //first x
        bg1_s.x = win_w - x;
        bg1_d.x = 0;

        bg1_s.y = 0;//temp
        bg1_d.y = 0;

        bg1_s.w = x;
        bg1_d.w = x;

        bg1_s.h = win_h;//temp
        bg1_d.h = win_h;//temp

        SDL_RenderCopy(rend,bg,&bg1_s,&bg1_d);

        //second x
        bg1_d.x = x;
        bg1_s.x = 0;

        bg1_s.y = 0;//temp
        bg1_d.y = 0;

        bg1_s.w = win_w - x;
        bg1_d.w = win_w - x;

        bg1_s.h = win_h;//temp
        bg1_d.h = win_h;//temp

        SDL_RenderCopy(rend,bg,&bg1_s,&bg1_d);

}
