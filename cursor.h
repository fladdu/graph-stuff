#ifndef CURSOR_H
#define CURSOR_H
#include <SDL2/SDL.h>

typedef enum cursormode CursorMode;

//cursor modes
enum cursormode {
    CURSOR_MOVE,
    CURSOR_SELECT,
    CURSOR_ADD,
    CURSOR_DELETE
};


#endif
