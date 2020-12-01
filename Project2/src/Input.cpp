#include "Input.h"
void doInputDown(SDL_Event e)
{
    if(e.key.keysym.scancode < MAX_KEYB_KEYS)
        input.inputs[e.key.keysym.scancode] = 1;
}


void doInputUP(SDL_Event e)
{
    if(e.key.keysym.scancode < MAX_KEYB_KEYS)
        input.inputs[e.key.keysym.scancode] = 0;
}


void doInput()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            input.quit = true;
        }
        else
        {
            switch(e.type)
            {
            case SDL_KEYDOWN :
                doInputDown(e);
                break;
            case SDL_KEYUP :
                doInputUP(e);
                break;
            }
        }
    }
}


