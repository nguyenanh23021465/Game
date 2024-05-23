#pragma once
#include "tile.h"
using namespace std;
tile T;
void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window=SDL_CreateWindow("memory",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    T.getImg();
}
void game()
{
    SDL_Event e;
    int quit=0;
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT)
            {
//                cout<<"lmao";
                quit=1;
            }
            T.event(e);
        }
        T.render();
        SDL_RenderPresent(renderer);
    }
}
int main(int argc,char* argv[])
{
    init();
    game();
    return 0;
}
