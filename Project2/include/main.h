#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <iostream>
#include "def.h"
#include "init.h"
#include "string.h"
#include "../lib_externe/SDL2_image-2.0.5/include/SDL_image.h"
#include "../lib_externe/SDL2-2.0.12/include/SDL.h"

using namespace std;
extern bool initWindow(void);
extern void close(void);
extern void prepareScene(void);
extern void updateScene(void);
extern void doInput(void);
extern void initStage(void);
extern void initSound(void);


App app;
Input input;
long then;
float _remainder;
#endif // MAIN_H_INCLUDED
