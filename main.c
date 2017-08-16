#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {

    //------------------------------
    //TESTS
    //------------------------------
    #ifdef TEST
    Graph* g = createGraph();

    addVert(g, 1);
    addVert(g, 2);
    addVert(g, 3);
    addVert(g, 4);
    addEdge(g, 1, 2);
    addEdge(g, 3, 1);
    addEdge(g, 3, 4);
    addEdge(g, 3, 2);
    addEdge(g, 4, 1);
    
    int size;
    
    for (int j = 1; j < 5; ++j) {
        const int *adj = getAdj(g, j, &size);
        printf("%d: ", j);
        for (int i = 0; i < size; ++i) {
            printf("%d ", adj[i]);
        }
        printf("\n");

        free((int *)adj);
    }
    
    destroyGraph(g);


    //BIG TEST
    g = createGraph();
    int numVerts = 50;

    for (int i = 0; i < numVerts; ++i) {
        addVert(g, i+1);
        for (int j = i; j > 0; --j) {
            addEdge(g, i+1, j);
        }
    }
    
    printf("done\n"); 
    scanf("%d", &size);

    destroyGraph(g);
    
    #endif
    //------------------------------
    //END TESTS
    //------------------------------

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("failed to init SDL");
    }
    
    //init vars
    int win_w = 1024;
    int win_h = 840;
    //int x_offset = 0;
    //int y_offset = 0;

    //init SDL vars
    SDL_Window *main_win = SDL_CreateWindow("Graph Visualizer",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,win_w,win_h,0);
    SDL_Renderer *main_rend = SDL_CreateRenderer(main_win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *win_tx = SDL_GetRenderTarget(main_rend);
    SDL_Texture *bg_tx = SDL_CreateTexture(main_rend,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,win_w,win_h);
    
    //SDL_SetRenderDrawColor(main_rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(main_rend);
    SDL_RenderPresent(main_rend);

    
    //draw bg texture
    SDL_SetRenderTarget(main_rend, bg_tx);
    SDL_SetRenderDrawColor(main_rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(main_rend);
    SDL_SetRenderDrawColor(main_rend,0x70,0x70,0x70,SDL_ALPHA_OPAQUE);
    for(int i = 0; i < win_w; i += 100) {
        SDL_RenderDrawLine(main_rend,i,0,i,win_h);
    }
    for(int i = 0; i < win_h; i += 100) {
        SDL_RenderDrawLine(main_rend,0,i,win_w,i);
    }
    SDL_RenderPresent(main_rend);
    SDL_SetRenderTarget(main_rend, NULL);
    
    int quit = 1;
    //Uint32 start = SDL_GetTicks();
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
            }
        }
        
        //update logic here
        
        //DRAW
        
        //draw bg
        SDL_RenderCopy(main_rend,bg_tx,NULL,NULL);


        SDL_RenderPresent(main_rend);
    }

    SDL_DestroyTexture(win_tx);
    SDL_DestroyTexture(bg_tx);
    SDL_DestroyRenderer(main_rend);
    SDL_DestroyWindow(main_win);
    SDL_Quit();

}
