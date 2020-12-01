#include "init.h"

bool initWindow()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("%s \n",SDL_GetError());;
    }
    else
    {
        app.window = SDL_CreateWindow("Game Inf",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if(app.window == NULL)
        {
            printf("window prb : %s \n",SDL_GetError());
            success = false;
        }
        else
        {
            app.renderer = SDL_CreateRenderer(app.window,-1,SDL_RENDERER_ACCELERATED);
            if(app.renderer == NULL)
            {
                printf("Renderer prb : %s \n",SDL_GetError());
                success = false;
            }
            else
            {
                if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)<0)
                {
                    printf("IMG_init prb : %s", SDL_GetError());
                    success = false;
                }
                else
                {
                    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
                    {
                        printf("Couldn't initialize SDL Mixer\n");
                        success = false;
                    }
                    Mix_AllocateChannels(NB_MAX_CHANNELS);
                }
            }
        }
    }
    SDL_ShowCursor(0);
    return success;
}

void close()
{
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
}
