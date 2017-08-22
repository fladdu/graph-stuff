#include "draw.h"

//background
void drawbg(int x,int y,int res,SDL_Texture *bg,SDL_Renderer *rend,int type) {
    SDL_SetRenderDrawColor(rend,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(rend);
    if (bg == NULL) {
        switch (type) {
            case BGTYPE_PLAIN:
                break;
            case BGTYPE_GRID:
                //draw grid
                SDL_SetRenderDrawColor(rend,0x66,0x66,0x66,SDL_ALPHA_OPAQUE);
                for(int i = x%res; i < win_w; i+=res) {
                    SDL_RenderDrawLine(rend,i,0,i,win_h);
                }
                for(int i = y%res; i < win_h; i+=res) {
                    SDL_RenderDrawLine(rend,0,i,win_w,i);
                }
                break;
            default:
                break;
        }
    } else {
        //TODO background given
    }
}



//rect
SDL_Rect getRect(int x,int y,int w,int h) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;
}

void moveRect(SDL_Rect *r,int x,int y) {
    r->x += x;
    r->y += y;
}

//circle
void renderDrawCircle(SDL_Renderer *rend, int x, int y, int r) {
    for(int row = 0; row < 2*r; row++) {
        for(int col = 0; col < 2*r; col++) {
            int cur_x = (x-r)+col;
            int cur_y = (y-r)+row;
            float dist = hypot(cur_x-x,cur_y-y);

            if (dist <= r) {
                SDL_RenderDrawPoint(rend,cur_x,cur_y);
            }
        }
    }
}
