#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#define SCREEN_WIDTH 860
#define SCREEN_HEIGHT 650

#define MAX_TILES 7 //Max number of tile types
#define TILE_SIZE 64//=>width and height of our tile
#define MAP_WIDTH 40//map data
#define MAP_HEIGHT 20
#define MAP_REND_WIDTH 20//Number tile rendered on the screen
#define MAP_REND_HEIGHT 12

#define MAX_KEYB_KEYS 350
#define PLAYER_SPEED 4
#define BULLET_SPEED 16

#define PLAYER_SIDE 0
#define ENNEMI_SIDE 1

#define ENNEMI_BULLET_SPEED 8
#define FPS 60

#define NB_MAX_STAR 100

#define NB_MAX_CHANNELS 8

enum
{
    CH_ANY = -1,
    CH_PLAYER,
    CH_ALIEN_FIRE
};


enum
{
    SND_PF,
    SND_AF,
    SND_PD,
    SND_AD,
    SND_MAX
};
#endif // DEF_H_INCLUDED
