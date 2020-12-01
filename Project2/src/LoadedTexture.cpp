#include "LoadedTexture.h"

LoadedTexture::LoadedTexture()
{
    w = 0;
    h = 0;
    texture = NULL;
}

LoadedTexture::~LoadedTexture()
{
    free();
}

void LoadedTexture::free()
{
    w = 0;
    h = 0;
    SDL_DestroyTexture(texture);
    texture = NULL;
}

bool LoadedTexture::loadFromFile(SDL_Renderer* renderer,std::string path)
{
    free();
    SDL_Texture* returnTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("%s",SDL_GetError());
        return false;
    }
    else
    {
        returnTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
        if(returnTexture == NULL)
        {
            printf("%s",SDL_GetError());
            return false;
        }
        else
        {
            w = loadedSurface->w;
            h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    texture = returnTexture;
    return (texture != NULL);
}
