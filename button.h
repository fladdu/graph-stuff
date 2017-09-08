#ifndef BUTTON_H
#define BUTTON_H

#include "types.h"

typedef struct button {
    callback c;//if both c and click (from GUIelement) are defined, c is called before click
} Button;


#endif
