#ifndef GUIEVENT_H
#define GUIEVENT_H

#include "types.h"
#include <SDL2/SDL_events.h>

typedef struct guieventhandler GUIeventHandler;

typedef enum guieventtype {
    MOUSE_HOVER,
    MOUSE_HOVER_ON,
    MOUSE_HOVER_OFF,
    MOUSE_DOWN,
    MOUSE_UP,
    MOUSE_SCROLL,
    KEY_DOWN,
    KEY_UP
} GUIeventType;



GUIeventHandler *createGUIeventHandler();
void destroyGUIeventHandler(GUIeventHandler *eh);

void addEventHandler(GUIeventHandler *eh, GUIeventType t, event_handler func);

int handleEvent(GUIeventHandler *eh, GUIeventType t, void *app, SDL_Event *e);

#endif
