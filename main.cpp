#pragma once
#include "tile.h"
using namespace std;
tile T;
Mix_Music* gGameMusic = NULL;
SDL_Texture* background = NULL;
SDL_Texture* menu = NULL;
void init()
{
    bool success = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    window=SDL_CreateWindow("memory",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    T.getImg();
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    if(TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

}

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
//	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}

void game()
{
    T.play.x = 290;
    T.play.y = 400;
    T.play.w = 220;
    T.play.h = 95;
    SDL_Event e;
    int quit = 0;
    bool playgame = false;
    bool gameStarted = false;
    menu = loadTexture("memory.png", renderer);
    SDL_RenderCopy(renderer, menu, NULL, NULL);
    SDL_RenderPresent(renderer);
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
            if (T.lose == false && playgame && gameStarted)
            {
                T.event(e);
            }
            if (e.type == SDL_MOUSEBUTTONDOWN && !playgame && !gameStarted)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if ((x >= T.play.x) && (x <= T.play.x + T.play.w) && (y >= T.play.y) && (y <= T.play.y + T.play.h))
                {
                    T.loadSound("start.wav");
                    playgame = true;
                    gameStarted = true;
                    T.timegame = SDL_GetTicks();
                }
            }
        }
        T.update();

        if (playgame && gameStarted)
        {
            if (T.cnt < 16 && (SDL_GetTicks() - T.timegame) >= 0 && (SDL_GetTicks() - T.timegame) <= 35000)
            {
                background = loadTexture("background.png", renderer);
                SDL_RenderCopy(renderer, background, NULL, NULL);

                string gTime = "TIME: ";
                Uint32 timeval = 35 - (SDL_GetTicks() - T.timegame) / 1000;
                string value = to_string(timeval);
                gTime += value;

                T.loadText(gTime);
                T.render(300, 10);

            }
                T.showcards();
                SDL_RenderPresent(renderer);
        }
    }
}

void tile::loadText(string gTime)
{
	gFont = TTF_OpenFont("ocean1.ttf", 48);
	if(gFont != NULL)
	{
		SDL_Color textColor = {255, 255, 255};
		if(!T.loadFromRenderedText(gTime, textColor))
		{
			printf("Failed to render text texture!\n");
		}
	}
}

int main(int argc,char* argv[])
{
    init();
    gGameMusic = Mix_LoadMUS("gameMusic.wav");
    Mix_PlayMusic(gGameMusic, -1);
    game();
    return 0;
}
