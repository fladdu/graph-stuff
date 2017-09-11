#include "GUIevent.h"

//struct
struct guieventhandler {
    event_handler hover,
                  hover_ON,
                  hover_OFF,
                  mouse_DOWN,
                  mouse_UP,
                  mouse_SCROLL,
                  key_DOWN,
                  key_UP;
};

GUIeventHandler *createGUIeventHandler() {
    GUIeventHandler *p;

    p = malloc(sizeof(GUIeventHandler));

    p->hover = NULL;
    p->hover_ON = NULL;
    p->hover_OFF = NULL;
    p->mouse_DOWN = NULL;
    p->mouse_UP = NULL;
    p->mouse_SCROLL = NULL;
    p->key_DOWN = NULL;
    p->key_UP = NULL;

    return p;
}
    
void destroyGUIeventHandler(GUIeventHandler *eh) {
    free(eh);
}

void addEventHandler(GUIeventHandler *eh, GUIeventType t, event_handler func) {
    switch (t) {
        case MOUSE_HOVER:
            eh->hover = func;
            break;
        case MOUSE_HOVER_ON:
            eh->hover_ON = func;
            break;
        case MOUSE_HOVER_OFF:
            eh->hover_OFF = func;
            break;
        case MOUSE_DOWN:
            eh->mouse_DOWN = func;
            break;
        case MOUSE_UP:
            eh->mouse_UP = func;
            break;
        case MOUSE_SCROLL:
            eh->mouse_SCROLL = func;
            break;
        case KEY_DOWN:
            eh->key_DOWN = func;
            break;
        case KEY_UP:
            eh->key_UP = func;
            break;
    }
}

int handleEvent(GUIeventHandler *eh, GUIeventType t, void *app, SDL_Event *e) {
    event_handler func = NULL;

    switch (t) {
        case MOUSE_HOVER:
            func = eh->hover;
            break;
        case MOUSE_HOVER_ON:
            func = eh->hover_ON;
            break;
        case MOUSE_HOVER_OFF:
            func = eh->hover_OFF;
            break;
        case MOUSE_DOWN:
            func = eh->mouse_DOWN;
            break;
        case MOUSE_UP:
            func = eh->mouse_UP;
            break;
        case MOUSE_SCROLL:
            func = eh->mouse_SCROLL;
            break;
        case KEY_DOWN:
            func = eh->key_DOWN;
            break;
        case KEY_UP:
            func = eh->key_UP;
            break;
    }

    if (func != NULL) {return func(app,e);}

    return -1;
}
