#ifndef TYPES_H
#define TYPES_H


typedef int (*draw_func)(SDL_Renderer *,void *);//for drawing stuff to gui elements
typedef int (*callback)(void *,int);//for buttons/other elements (ie. change cursor state) data for ref/amt/val
typedef int (*event_handler) (void *, SDL_Event *);//same as SDL_EventFilter more general event handler

#endif
