#include "draw.h"

void prepareScene()
{
    SDL_SetRenderDrawColor(app.renderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(app.renderer);
}

void updateScene()
{
    SDL_RenderPresent(app.renderer);
}

SDL_Texture* loadTextureFromFile(std::string path)
{
    SDL_Texture* returnTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("%s",SDL_GetError());
    }
    else
    {
        returnTexture = SDL_CreateTextureFromSurface(app.renderer,loadedSurface);
        if(returnTexture == NULL)
        {
            printf("%s",SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return returnTexture;
}

void renderTexture(SDL_Texture* texture,int x,int y,SDL_Rect* clip, double angle, SDL_Point* center,SDL_RendererFlip flip)
{

    int w;
    int h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    if(clip != NULL)
    {
        w = clip->w;
        h = clip->h;
    }
    SDL_Rect renderRect = {x,y,w,h};
    SDL_RenderCopyEx(app.renderer,texture,clip,&renderRect,angle,center,flip);
}



