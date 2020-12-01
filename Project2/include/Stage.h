#ifndef STAGE_H
#define STAGE_H
#include "structs.h"
#include "SDL.h"
#include <string.h>
#include <stdlib.h>
#include "draw.h"

extern SDL_Texture* loadTextureFromFile(std::string path);
extern void renderTexture(SDL_Texture* texture,int x,int y,SDL_Rect* clip, double angle, SDL_Point* center,SDL_RendererFlip flip);
extern int CollisionCheck(int bx,int ex,int by, int ey,int bw,int bh,int ew,int eh);
extern void calcSlope(int x1,int y1,int x2,int y2, float *dx, float *dy);
extern void playSound(int id, int channel);
extern App app;
extern Input input;
Stage stage;
SDL_Texture* bulletTexture;
SDL_Texture* ennemiTexture;
SDL_Texture* playerTexture;
SDL_Texture* ennemiBulletTexture;
SDL_Texture* bgTexture;
SDL_Texture* explosionTexture;
struct Object* player;
Star stars[NB_MAX_STAR];
long ennemiSpawnTimer;
int stageTimer;
int bgX,bgY;
#endif // STAGE_H
