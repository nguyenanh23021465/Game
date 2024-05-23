#include "tile.h"
using namespace std;
tile::tile()
{
    exist=1;
    turn=0;
    tex0=NULL;
    tex1=NULL;
    pos.x=0;
    pos.y=0;
    pos.w=600;
    pos.h=600;
}
void tile::getImg()
{
    SDL_Surface* tmpSurface;
    tmpSurface=IMG_Load("resources/nothing.png");
    tex0=SDL_CreateTextureFromSurface(renderer,tmpSurface);
//    if(tmpSurface==NULL) cout<<"nguvcl";

    tmpSurface=IMG_Load("resources/one.png");
    tex1=SDL_CreateTextureFromSurface(renderer,tmpSurface);

    SDL_FreeSurface(tmpSurface);
}
void tile::render()
{
    if(turn) SDL_RenderCopy(renderer,tex1,NULL,NULL);
    else  SDL_RenderCopy(renderer,tex0,NULL,NULL);
}

void tile::event(SDL_Event &e)
{
    if(e.type==SDL_MOUSEMOTION||e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState( &x, &y );
        if(pos.x<=x&&x<=pos.x+pos.w&&pos.y<=y&&y<=pos.y+pos.h)
        {
            if(e.type == SDL_MOUSEBUTTONDOWN) turn=1-turn;
        }
    }
}
