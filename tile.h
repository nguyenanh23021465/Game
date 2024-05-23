#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "all.h"
using namespace std;
#ifndef TILE_H
#define TILE_H
class tile
{
    public:
        tile();
        ~tile();
        void update();
        int cnt = 0;
        void menugame();
        void getImg();
        void showcards();
        void event(SDL_Event &e);
        void loadSound(string path);
        void close();
        bool loadFromRenderedText(string textureText, SDL_Color textColor);
        void clearTextures();
        void loadText(string gTime);
        void render(int x, int y, SDL_Rect* clip = NULL); //double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        bool win;
        bool lose;
        int timegame;
        SDL_Rect play;
    private:
        int time;
        bool exist = false;
        int turn[16] = {0};
        vector<pair<SDL_Texture*, int>> v;
        SDL_Texture* b;
        SDL_Texture* c;
        SDL_Texture* d;
        vector<pair<int,int>> p;
        int stickerIsClicked = 0;
        int mousePos[2];
        SDL_Rect pos;
        SDL_Texture* mTexture;
        Mix_Chunk* gSound;
        TTF_Font* gFont = NULL;
        int mWidth;
        int mHeight;
        void free();
        string val;
        char* tex[16] = {"shark.png", "shrimp.png", "whale.png", "turtle.png", "starfish.png", "dolphin.png", "crab.png", "seahorse.png","shark.png", "shrimp.png", "whale.png", "turtle.png", "starfish.png", "dolphin.png", "crab.png", "seahorse.png"};
};
#endif // TILE_H
