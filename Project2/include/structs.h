#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
#include "SDL.h"

#include "def.h"
#include "LoadedTexture.h"

typedef struct {
    void (*logic)(void);
    void (*draw)(void);
}Delegate;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window* window;
    Delegate delegate;
} App;

typedef struct {
    bool quit;
    int inputs[MAX_KEYB_KEYS];
}Input;

struct Object{
    float posX, posY;
    int w,h;
    float dx,dy;
    int health;
    int reload;
    //LoadedTexture texture;
    SDL_Texture* texture;
    int side;
    Object* next;
};

struct Explosion{
    float posX, posY;
    float dx,dy;
    int r,g,b,a;
    Explosion* next;
};

struct Debris{
    float posX, posY;
    float dx,dy;
    SDL_Rect rect;
    SDL_Texture* texture;
    int life;
    Debris* next;
};

typedef struct{
    int x,y;
    int speed;
}Star;

typedef struct {
    Object fighterHead, *fighterTail;
    Object bulletHead, *bulletTail;
    Explosion explosionHead, *explosionTail;
    Debris debrisHead, *debrisTail;
} Stage;
#endif // STRUCTS_H_INCLUDED
