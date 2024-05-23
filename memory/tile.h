#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "all.h"
//#include "useForAll.h"

#ifndef TILE_H
#define TILE_H
class tile
{
    public:
        tile();
        void getImg();
        void render();
        void event(SDL_Event &e);
    private:
        bool exist,turn;
        SDL_Texture *tex0;
        SDL_Texture *tex1;
        SDL_Rect pos;
};
#endif // TILE_H
