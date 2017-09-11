#include "GUI.h"
#include "GUIelement.h"
#include <SDL2/SDL.h>
#include <string.h>

/*
==============================
typdefs
==============================
*/

typedef struct section {
    draw_func drawbg;
    SDL_Rect area;
    int id;
    int enabled;
} Section;

typedef struct gui {
    
    //SDL stuff
    SDL_Window *main_win;
    SDL_Renderer *main_rend;
    //SDL_Texture *win_tx;
    SDL_Texture *bg_tx;
    SDL_Texture *fg_tx;

    //data
    SDL_Rect win;

    //app
    void *app;

    //layout stuff
    int numSections;//TODO maybe move sections to elements?
    Section *sections;
     
    int numElements;
    GUIelement *elems;

    GUIelement *hovered;
    GUIelement *clicked;
    GUIelement *focused;
} GUI;

/*
===============================
helpers decl
===============================
*/
GUIelement *getElementAtPos(GUI *g,int x, int y);

/*
===============================
helpers implementation
===============================
*/
GUIelement *getElementAtPos(GUI *g,int x, int y) {
    SDL_Point p = {.x = x, .y = y};
    GUIelement *el= NULL;
    for(int i = g->numElements; i > 0; --i) {
        if (SDL_PointInRect(&p, &(g->elems[i-1].area))) {
            //TODO have z levels or somthing (now is like stack)
            el = g->elems+i;
            break;
        }
    }
    return el;
}

//creation
GUI *createGUI(const char *name, void *app, const SDL_Rect win) {
    GUI *temp = malloc(sizeof(GUI));

    temp->win = win;
    temp->app = app;
   
    temp->main_win = SDL_CreateWindow(name,win.x,win.y,win.w,win.h,0);
    temp->main_rend = SDL_CreateRenderer(temp->main_win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //temp->win_tx = SDL_GetRenderTarget(temp->main_rend);
    temp->bg_tx = SDL_CreateTexture(temp->main_rend,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,win.w,win.h);
    temp->fg_tx = SDL_CreateTexture(temp->main_rend,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_TARGET,win.w,win.h);
    
    temp->numSections = 0;
    temp->sections = NULL;
    temp->numElements = 0;
    temp->elems = NULL;

    temp->hovered = NULL;
    temp->clicked = NULL;
    temp->focused = NULL;

    SDL_SetTextureBlendMode(temp->fg_tx,SDL_BLENDMODE_BLEND);

    return temp;
}

//deletion
void destroyGUI(GUI *g) {
    if (g->numSections != 0) {
        free(g->sections);
    }

    if (g->numElements != 0) {
        for (int i = 0; i < g->numElements; ++i) {
            destroyGUIelement(g->elems+i);
        }
        free(g->elems);
    }

    g->app = NULL;

    SDL_DestroyTexture(g->fg_tx);
    SDL_DestroyTexture(g->bg_tx);
    SDL_DestroyRenderer(g->main_rend);
    SDL_DestroyWindow(g->main_win);
    
    free(g);
}

//drawing
void drawBG(GUI *g) {
    
    for(int i = 0; i < g->numSections; ++i) {
        SDL_RenderSetViewport(g->main_rend,&(g->sections[i].area));
        g->sections[i].drawbg(g->main_rend, g->app, NULL);
    }
    SDL_RenderSetViewport(g->main_rend,NULL);
}

void useDrawFunc(GUI *g, void *userdata, draw_func df, int sec) {
    
    //TODO make getSection function
    Section *s = NULL;
    for(int i = 0; i < g->numSections; i++) {
        if (g->sections[i].id == sec) {
            s = (g->sections)+i;
            break;
        }
    }

    if (s == NULL && sec != 0) {
        //section doesnt exist
        return;
    } else if (sec == 0) {
        SDL_RenderSetViewport(g->main_rend,NULL);
    } else {
        SDL_RenderSetViewport(g->main_rend,&(s->area));
    }

    df(g->main_rend,g->app,userdata);
    SDL_RenderSetViewport(g->main_rend,NULL);
}

void update(GUI *g) {
    SDL_RenderPresent(g->main_rend);
}
    

//events
int handleEvents(GUI *g) {
    SDL_Event e;
    int quit = 0;
        while (SDL_PollEvent(&e)) {

            //handle events here //TODO
            switch(e.type) {
                case SDL_QUIT: 
                    quit = 1;
                    break;
                case SDL_MOUSEMOTION: {
                    GUIelement *el = getElementAtPos(g, e.motion.x, e.motion.y);
                    if (el == NULL) {break;}
                    handleEvent(el->eh,MOUSE_HOVER,g->app,&e);

                    if (g->hovered == el) {
                        break;
                    } else if (el != g->hovered) {
                        if (g->hovered != NULL) {
                            setTexture(g->hovered, DEFAULT_TEXTURE);
                            handleEvent(g->hovered->eh,MOUSE_HOVER_OFF,g->app,&e);
                        }
                        g->hovered = el;
                        setTexture(el, HOVER_TEXTURE);
                        handleEvent(el->eh, MOUSE_HOVER_ON, g->app,&e);
                    }
                    break;
                }
                case SDL_KEYDOWN: {
                    break;
                    /*curr = e.key.keysym.sym;
                    if (curr == SDLK_i && mode != CURSOR_ADD) {
                        puts("Entered insert mode");
                        mode = CURSOR_ADD;
                    } else if (curr == SDLK_m && mode !=CURSOR_MOVE) {
                        puts("Entered move mode");
                        mode = CURSOR_MOVE;
                    }
                    break;*/
                }
                case SDL_MOUSEBUTTONDOWN:
                 
                    break;
            }
        }
    return quit;
}

/*
============================================================
    gui elements
============================================================
*/

/*
    helper
    adds elements while keeping pointers intact
*/
void addElement(GUI *g, GUIelement *el) {
    GUIelement *temp = malloc(sizeof(GUIelement) * (g->numElements+1));
    for(int i = 0; i < g->numElements; ++i) {
        temp[i] = g->elems[i];
        if (g->elems+i == g->hovered) {
            g->hovered = temp+i;
        }
        if (g->elems+i == g->clicked) {
            g->clicked = temp+i;
        }
        if (g->elems+i == g->focused) {
            g->focused = temp+i;
        }
    }
    temp[++g->numElements] = *el;
}


void addButton(GUI *g, SDL_Rect *hitbox, const char *name, int val, callback c) {
   
    char file_name[strlen(name)+5];

    strcpy(file_name,name);
    strcat(file_name, ".bmp");
 
    SDL_Surface *load = SDL_LoadBMP(file_name);
    if (load == NULL) {
        puts("error loading image");
        return;
    }

    SDL_Surface *toTexture = SDL_CreateRGBSurface(0,(load->w)*2,(load->h)*2,SDL_BITSPERPIXEL(load->format->format),load->format->Rmask,load->format->Gmask,load->format->Bmask,load->format->Amask);
    
    SDL_BlitSurface(load, NULL, toTexture, hitbox);
    
    GUIelement el = {
        .type = BUTTON,
        .val = val,
        .name = name,
        .area = *hitbox,
        .eh = createGUIeventHandler(),
        .clip = *hitbox,
        .sprites = SDL_CreateTextureFromSurface(g->main_rend, toTexture),
        .button = {.c = c}
    };

    addElement(g,&el);

    SDL_FreeSurface(load);
    SDL_FreeSurface(toTexture);
}

void addDisplay(GUI *g, SDL_Rect *hitbox, const char *name, int val, int format) {

    //TODO add sprites

    GUIelement el = {
        .type = BUTTON,
        .val = val,
        .name = name,
        .area = *hitbox,
        .eh = createGUIeventHandler(),
        .clip = *hitbox,
        .sprites = SDL_CreateTexture(g->main_rend,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,hitbox->w,hitbox->h),
        .display = {.canvas = SDL_CreateTexture(g->main_rend,format,SDL_TEXTUREACCESS_STREAMING,hitbox->w,hitbox->h)}
    };

    addElement(g,&el);
}

void addSection(GUI *g, SDL_Rect *area, draw_func bgDrawer) {

    Section temp = {
        .drawbg = bgDrawer,
        .area = *area,
        .id = ++(g->numSections),
        .enabled = 1
    };

    g->sections = realloc(g->sections, sizeof(Section) * g->numSections);
    g->sections[g->numSections - 1] = temp;
}
