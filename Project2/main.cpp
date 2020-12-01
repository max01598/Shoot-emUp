#include "main.h"

static void capFrameRate(long* then, float* r);

int main(int argc, char* argv[])
{
    memset(&app, 0, sizeof(App));
    initWindow();
    initSound();
    printf("init Stage Begin");
    initStage();
    printf("init Stage Finished");
    then = SDL_GetTicks();
    _remainder = 0;
    input.quit = false;
    while (!input.quit)
    {
        prepareScene();
        doInput();
        app.delegate.logic();
        app.delegate.draw();
        updateScene();
        capFrameRate(&then, &_remainder);
    }
    close();
    return 0;
}

static void capFrameRate(long* then, float* remainder)
{
    long wait, frameTime;
    wait = 16 + *remainder;
    *remainder -= (int)*remainder;
    frameTime = SDL_GetTicks() - *then;
    wait -= frameTime;
    if (wait < 1)
    {
        wait = 1;
    }
    SDL_Delay(wait);
    *remainder += 0.667;
    *then = SDL_GetTicks();
}
