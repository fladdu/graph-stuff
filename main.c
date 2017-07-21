#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "display.h"
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

    Display *main_win = createDisplay(1024, 840);
    wipeDisplay(main_win);

    int quit = 1;
    //Uint32 start = SDL_GetTicks();

    //main app loop
    while (quit) {
        /*if (SDL_TICKS_PASSED(SDL_GetTicks(), start + 50)) {
            start = SDL_GetTicks();
        } else {
            SDL_Delay
        }*/

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
        
        //draw
        wipeDisplay(main_win);
        drawSquare(main_win,100,100,30);
        updateDisplay(main_win);
    }

    destroyDisplay(main_win);
    SDL_Quit();

}
