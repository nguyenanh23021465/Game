#include "tile.h"
using namespace std;

tile::tile()
{
    mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
    gSound = NULL;
    exist = 0;
    pos.x = 100;
    pos.y = 100;
    pos.w = 135;
    pos.h = 150;
    SDL_Rect m = pos;
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++){
            p.push_back({m.x,m.y});
            m.x += 150;
        }
        m.x = 100;
        m.y += 175;
    }
}
void tile::free()
{
    if(mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

tile::~tile()
{
    free();
}

void tile::loadSound(string path)
{
    gSound = Mix_LoadWAV(path.c_str());
    Mix_PlayChannel(-1, gSound, 0);
}

void tile::menugame()
{
    SDL_Surface* tmpSurface;
    SDL_Texture* x;
    tmpSurface = IMG_Load("memory.png");
    x = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void tile::getImg()
{
    SDL_Surface* tmpSurface;
    SDL_Texture* x;
    for(int i = 0; i < 16; i++)
    {
        tmpSurface = IMG_Load(tex[i]);
        x = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        v.push_back({x,i});
    }
    tmpSurface = IMG_Load("card.png");
    b = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    tmpSurface = IMG_Load("youlosegame.png");
    c = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    tmpSurface = IMG_Load("winner.png");
    d = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    random_shuffle(v.begin(), v.end());
}

void tile::showcards()
{
    SDL_Rect m = pos;
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++){
            if (turn[index] == 1)
            {
                SDL_RenderCopy(renderer, v[index].first, NULL, &m);
            }
            else if(turn[index] == 0)
            {
                SDL_RenderCopy(renderer, b, NULL, &m);
            }
            else if(turn[index] == 2){
                SDL_DestroyTexture(v[index].first);
                v[index].first = NULL;
            }
            index++;
            m.x += 150;
        }
        m.x = 100;
        m.y += 170;
    }
}

void tile::clearTextures() {
    for (auto& texturePair : v) {
        if (texturePair.first != nullptr) {
            SDL_DestroyTexture(texturePair.first);
            texturePair.first = nullptr;
        }
    }
    v.clear();
    if (b != nullptr) {
        SDL_DestroyTexture(b);
        b = nullptr;
    }
}

bool tile::loadFromRenderedText(string textureText, SDL_Color textColor)
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if(textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if(mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}

void tile::render(int x, int y, SDL_Rect* clip) //double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(renderer, mTexture, clip, &renderQuad); //angle, center, flip);
}

void tile::event(SDL_Event& e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
         for(int i = 0; i < 16; i++)
        {
            int x, y;
            SDL_GetMouseState( &x, &y );
            if(x >= p[i].first && x <= p[i].first + pos.w && y >= p[i].second && y <= p[i].second + pos.h)
            {
                if(turn[i] == 0){

                    {
                        turn[i] = 1;
                        loadSound("clickPieceSound.wav");
                        mousePos[stickerIsClicked] = i;
                        time = SDL_GetTicks();
                        stickerIsClicked++;
                    }
                }
            }
        }
    }
}

void tile::update()
{
    if(stickerIsClicked == 2){
        if(SDL_GetTicks() - time >= 420)
        {
            if(abs(v[mousePos[0]].second - v[mousePos[1]].second) == 8)
            {
                loadSound("correctcards.wav");
                cnt += 2;
                turn[mousePos[0]] = 2;
                turn[mousePos[1]] = 2;
            }
            else
            {
                turn[mousePos[0]] = 0;
                turn[mousePos[1]] = 0;
            }
        stickerIsClicked = 0;
        }
    }
    if(cnt == 16 && !win && (SDL_GetTicks() - timegame) >= 0 && (SDL_GetTicks() - timegame) <= 35000){
        win = true;
        Mix_HaltMusic();
        SDL_Delay(600);
        SDL_RenderCopy(renderer, d, NULL, NULL);
        loadSound("winner.wav");
    }

    else if(cnt < 16 && !lose && (SDL_GetTicks() - timegame) > 35000){
        lose = true;
        Mix_HaltMusic();
        //SDL_Delay(600);
        SDL_RenderCopy(renderer, c, NULL, NULL);
        loadSound("gameover.wav");
        clearTextures();
    }
}

