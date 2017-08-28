#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "draw.h"
#include "cursor.h"
#include <SDL2/SDL.h>
#include <math.h>


const int win_w = 1024;
const int win_h = 840;
const int MAX_RES = 200;
const int MIN_RES = 15;

int main(int argc, char *argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("failed to init SDL");
    }
    
    //init vars
    int offset_x = 0;
    int offset_y = 0;
    int bg_size = win_w + win_h;
    float res = argv[1]?atoi(argv[1]):70; //pixels per grid square
    float zoom = 1; //zoom level
    float sensitivity = .95;

    //init SDL vars
    SDL_Window *main_win = SDL_CreateWindow("Graph Visualizer",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,win_w,win_h,0);
    SDL_Renderer *main_rend = SDL_CreateRenderer(main_win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *win_tx = SDL_GetRenderTarget(main_rend);
    SDL_Texture *bg_tx = NULL; //= SDL_CreateTexture(main_rend,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,bg_size,bg_size);
    SDL_Texture *fg_tx = SDL_CreateTexture(main_rend,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,win_w,win_h);
    
    //setup SDL stuff
    SDL_SetTextureBlendMode(fg_tx,SDL_BLENDMODE_BLEND);
    //SDL_SetRenderDrawBlendMode(main_rend,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(main_rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
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
    
    //my stuff
    int quit = 0;
    CursorMode mode = CURSOR_MOVE; 
    SDL_Rect *rect_arr = NULL;
    int rectCount = 0;
    //main app loop
    while (!quit) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {

            //for key events
            SDL_Keycode curr;

            //for locations
            int x;
            int y;

            //misc
            int temp_i;
            float temp_f;
            
            //handle events here
            switch(e.type) {
                case SDL_QUIT: 
                    quit = 1;
                    break;
                case SDL_MOUSEMOTION:
                    if (e.motion.state & SDL_BUTTON_LMASK && mode == CURSOR_MOVE) {
                        offset_x += e.motion.xrel;
                        offset_y += e.motion.yrel;
                    }
                    break;
                case SDL_KEYDOWN:
                    curr = e.key.keysym.sym;
                    if (curr == SDLK_i && mode != CURSOR_ADD) {
                        puts("Entered insert mode");
                        mode = CURSOR_ADD;
                    } else if (curr == SDLK_m && mode !=CURSOR_MOVE) {
                        puts("Entered move mode");
                        mode = CURSOR_MOVE;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = e.button.x;
                    y = e.button.y;
                    if (e.button.button == SDL_BUTTON_LEFT && mode == CURSOR_ADD) {
                        rect_arr = realloc(rect_arr,++rectCount * sizeof(SDL_Rect));
                        rect_arr[rectCount-1] = getRect(x-offset_x, y-offset_y, 45, 45);
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    break;
                    y = e.wheel.y;
                    temp_f = res;
                    res *= sqrt(pow(sensitivity,y));//add sensitivity
                    //offset_x += y * ((temp_f - res)/2);
                    //offset_y += y * ((temp_f - res)/2);
                    zoom += y*-(1-sensitivity);
                    printf("res: %f, zoom: %f\n",res, zoom);
                    //res = (res/temp_f) * zoom;
                    break;
            }
        }
        
        //update logic--------------------------------
    
        
        //capping stuff
        if (res > MAX_RES) {
            res = MAX_RES;
        } else if (res < MIN_RES) {
            res = MIN_RES;
        }

        
 
        //BEGIN DRAW-----------------------------------
        SDL_SetRenderDrawColor(main_rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(main_rend);
        
        //bg
        drawbg(offset_x,offset_y,res,bg_tx,main_rend,BGTYPE_GRID);


        //fg
        SDL_SetRenderTarget(main_rend, fg_tx);
        SDL_SetRenderDrawColor(main_rend,0xff,0xff,0xff,SDL_ALPHA_TRANSPARENT);
        SDL_RenderClear(main_rend);
        //draw stuff to fg tx
        SDL_SetRenderDrawColor(main_rend,0x33,0x23,0xff,SDL_ALPHA_OPAQUE);
        for(int i = 0; i < rectCount; i++) {
            SDL_Rect curr = rect_arr[i];
            SDL_Rect temp = getRect(curr.x + offset_x, curr.y + offset_y, curr.w, curr.h);
            renderDrawCircle(main_rend,temp.x,temp.y,((temp.w+temp.h)/4)/**sqrt(zoom)*/);
        }
        //SDL_RenderFillRects(main_rend,rect_arr,rectCount);
        //------------------
        SDL_SetRenderTarget(main_rend,NULL);

        SDL_RenderCopy(main_rend,fg_tx,NULL,NULL);

        SDL_RenderPresent(main_rend);
        //END DRAW-------------------------------------
    }

    SDL_DestroyTexture(fg_tx);
    SDL_DestroyTexture(win_tx);
    SDL_DestroyTexture(bg_tx);
    SDL_DestroyRenderer(main_rend);
    SDL_DestroyWindow(main_win);
    SDL_Quit();

    //free my stuff
    free(rect_arr);

}
