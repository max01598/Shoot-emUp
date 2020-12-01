#include "Stage.h"

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void playerBehav(void);
static void bulletBehav(void);
static void fireBullet(void);
static void ennemiBehav(void);
static void spawnEnnemi(void);
static int CheckCollision(Object* b);
static void resetStage(void);
static void fireEnnemieBullet(Object* e);
static void doEnemies(void);
static void initStarfield(void);
static void explosionBehav(void);
static void starfieldBehav(void);
static void bgBehav(void);
static void debrisBehav(void);
static void addExplosions(int x,int y, int num);
static void addDebris(Object* e);

void initStage(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;
    memset(&stage,0,sizeof(Stage));
    stage.bulletTail = &stage.bulletHead;
    stage.fighterTail = &stage.fighterHead;
    stage.explosionTail = &stage.explosionHead;
    stage.debrisTail = &stage.debrisHead;
    bulletTexture = loadTextureFromFile("sprites/bullet.png");
    ennemiTexture = loadTextureFromFile("sprites/TIE.png");
    ennemiBulletTexture = loadTextureFromFile("sprites/bullet.png");
    playerTexture = loadTextureFromFile("sprites/xwing.png");
    bgTexture = loadTextureFromFile("sprites/background.png");
    explosionTexture = loadTextureFromFile("sprites/explosion.png");
    ennemiSpawnTimer = 0 ;
    resetStage();
}

static void initPlayer()
{
    player = (Object*) malloc(sizeof(Object));
    memset(player,0,sizeof(Object));
    stage.fighterTail->next = player;
    stage.fighterTail = player;

    player->side = PLAYER_SIDE;
    player->posX = 100;
    player->posY = 100;
    player->health = 3;
    player->texture = playerTexture;
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void logic(void)
{
    bgBehav();
    starfieldBehav();

    playerBehav();
    ennemiBehav();
    doEnemies();
    bulletBehav();
    spawnEnnemi();


    explosionBehav();
    debrisBehav();
    if(player==NULL && --stageTimer <= 0)
    {
        printf("Fin Game");
        resetStage();
    }
}

static void playerBehav(void)
{
    if(player != NULL)
    {
        player->dx = player->dy = 0;

        if(player->reload > 0)
        {
            player->reload --;
        }
        if(input.inputs[SDL_SCANCODE_DOWN] && (player->posY + player->h < SCREEN_HEIGHT))
        {
            player->dy = PLAYER_SPEED;
        }
        else if((input.inputs[SDL_SCANCODE_RIGHT])&& (player->posX + player->w < SCREEN_WIDTH))
        {
            player->dx = PLAYER_SPEED;
        }
        else if((input.inputs[SDL_SCANCODE_UP])&& (player->posY > 0))
        {
            player->dy = -PLAYER_SPEED;
        }
        else if((input.inputs[SDL_SCANCODE_LEFT])&& (player->posX > 0))
        {
            player->dx = -PLAYER_SPEED;
        }
        if(input.inputs[SDL_SCANCODE_LCTRL] && player->reload == 0)
        {
            playSound(SND_PF,CH_PLAYER);
            fireBullet();
        }
        player->posX += player->dx;
        player->posY += player->dy;
    }

}

static void fireBullet(void)
{
    Object *bullet;
    bullet = (Object *)malloc(sizeof(Object));
    memset(bullet,0,sizeof(Object));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;

    bullet->side = PLAYER_SIDE;
    bullet->posX = player->posX;
    bullet->posY = player->posY;
    bullet->dx = BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    SDL_QueryTexture(bullet->texture,NULL,NULL,&bullet->w,&bullet->h);
    player->reload = 8;
}


static void bulletBehav()
{
    Object *b, *prev;
    prev = &stage.bulletHead;
    for(b = prev->next; b!=NULL;b = b->next)
    {
        b->posX += b->dx;
        b->posY += b->dy;
        if(b->posX > SCREEN_WIDTH || CheckCollision(b) || b->posX < -b->w || b->posY < -b->h || b->posY > SCREEN_HEIGHT)
        {
            if(b == stage.bulletTail)
            {
                stage.bulletTail = prev;
            }
            prev->next = b->next;
            free(b);
            b = prev;
        }
        prev = b;
    }
}

static void drawPlayer(void)
{
    if(player!=NULL)
        renderTexture(player->texture,player->posX,player->posY,NULL,0,0,SDL_FLIP_NONE);
}

static void drawBullet(void)
{
    Object *b;
    for(b = &stage.bulletHead;b!=NULL;b = b->next)
    {
        renderTexture(b->texture,b->posX,b->posY,NULL,0,0,SDL_FLIP_NONE);
    }

}

static void drawEnnemies(void)
{
    Object *e;
    for(e = &stage.fighterHead;e!=NULL;e = e->next)
    {
        if(e != player)
            renderTexture(e->texture,e->posX,e->posY,NULL,90,0,SDL_FLIP_NONE);
    }

}

static void drawBg(void)
{
    SDL_Rect dest;
    int x;
    for(x = bgX;x<SCREEN_WIDTH;x+=SCREEN_WIDTH)
    {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;

        SDL_RenderCopy(app.renderer,bgTexture,NULL,&dest);
    }
}

static void drawStarfield(void)
{
    int i,c;
    for(i=0;i<NB_MAX_STAR;i++)
    {
        c = 32*stars[i].speed;
        SDL_SetRenderDrawColor(app.renderer,c,c,c,255);
        SDL_RenderDrawLine(app.renderer,stars[i].x,stars[i].y,stars[i].x + 3,stars[i].y);
    }
}

static void drawExplosions(void)
{
    Explosion *e;
    SDL_SetRenderDrawBlendMode(app.renderer,SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosionTexture,SDL_BLENDMODE_ADD);
    for(e=stage.explosionHead.next;e!=NULL;e=e->next)
    {
        SDL_SetTextureColorMod(explosionTexture,e->r,e->g,e->b);
        SDL_SetTextureAlphaMod(explosionTexture,e->a);
        renderTexture(explosionTexture,e->posX,e->posY,NULL,90,0,SDL_FLIP_NONE);
    }
    SDL_SetRenderDrawBlendMode(app.renderer,SDL_BLENDMODE_NONE);
}

static void drawDebris(void)
{
    Debris *d;
    for(d=stage.debrisHead.next;d!=NULL;d=d->next)
    {
        renderTexture(d->texture,d->posX,d->posY,&d->rect,90,0,SDL_FLIP_NONE);
    }
}

static void draw(void)
{
    drawBg();
    drawStarfield();
    drawPlayer();
    drawBullet();
    drawDebris();
    drawExplosions();

    drawEnnemies();
}

static void ennemiBehav()
{
    Object *e, *prev;
    prev = &stage.fighterHead;
    for(e = stage.fighterHead.next; e!=NULL;e = e->next)
    {
        e->posX += e->dx;
        e->posY += e->dy;
        if(e!=player && e->posX < -e->w)
        {
            e->health = 0;
        }
        if(e->health == 0)
        {
            if(e == player)
            {
                player = NULL;
            }
            else
            {
                addExplosions(e->posX,e->posY,3);
                addDebris(e);
            }
            if(e == stage.fighterTail)
            {
                stage.fighterTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

static void spawnEnnemi()
{
    Object* e;
    if(--ennemiSpawnTimer <= 0)
    {
        e = (Object*)malloc(sizeof(Object));
        memset(e,0,sizeof(Object));
        stage.fighterTail->next =  e;
        stage.fighterTail = e;
        e->side = ENNEMI_SIDE;
        e->health = 1;
        e->posX = SCREEN_WIDTH;
        e->posY = rand()%SCREEN_HEIGHT;
        e->texture = ennemiTexture;
        SDL_QueryTexture(e->texture,NULL,NULL,&e->w,&e->h);
        e->dx = -(2 + (rand()%4));
        ennemiSpawnTimer = 30 + 50;
        e->reload = FPS * (1 + (rand() % 3));;
    }
}


static int CheckCollision(Object* b)
{
    Object* e;

    for(e = stage.fighterHead.next; e != NULL; e= e->next)
    {
        if(e->side != b->side && CollisionCheck(b->posX,e->posX,b->posY,e->posY,b->w,b->h,e->w,e->h))
        {
            b->health = 0;
            if(e == player)
            {
                e->health -= 1;
            }
            else
            {
                e->health = 0;
            }
            return 1;
        }
    }
    return 0;
}

static void resetStage()
{
    Object *e;
    Explosion *expl;
    Debris *d;
    while (stage.fighterHead.next)
	{
		e = stage.fighterHead.next;
		stage.fighterHead.next = e->next;
		free(e);
	}

	while (stage.bulletHead.next)
	{
		e = stage.bulletHead.next;
		stage.bulletHead.next = e->next;
		free(e);
	}


	while (stage.explosionHead.next)
	{
		expl = stage.explosionHead.next;
		stage.explosionHead.next = expl->next;
		free(expl);
	}

	while (stage.debrisHead.next)
	{
		d = stage.debrisHead.next;
		stage.debrisHead.next = d->next;
		free(d);
	}

    memset(&stage,0,sizeof(Stage));
    stage.bulletTail = &stage.bulletHead;
    stage.fighterTail = &stage.fighterHead;
    stage.explosionTail = &stage.explosionHead;
    stage.debrisTail = &stage.debrisHead;

    initStarfield();
    initPlayer();
    ennemiSpawnTimer = 0 ;
    stageTimer = FPS*2;
}

static void doEnemies(void)
{
	Object *e;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
		if (e != player && player != NULL && --e->reload <= 0)
		{
			fireEnnemieBullet(e);
		}
	}
}

static void fireEnnemieBullet(Object* e)
{
    Object *bullet;
    bullet = (Object *)malloc(sizeof(Object));
    memset(bullet,0,sizeof(Object));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;

    bullet->side = e->side;
    bullet->posX = e->posX;
    bullet->posY = e->posY;
    bullet->health = 1;
    bullet->texture = ennemiBulletTexture;
    SDL_QueryTexture(bullet->texture,NULL,NULL,&bullet->w,&bullet->h);
    bullet->posX += (e->w/2) - (bullet->w/2);
    bullet->posY += (e->h/2) - (bullet->h/2);
    calcSlope(player->posX + (player->w/2),player->posY + (player->h/2),e->posX,e->posY, &bullet->dx, &bullet->dy);
    bullet->dx *= ENNEMI_BULLET_SPEED;
    bullet->dy *= ENNEMI_BULLET_SPEED;
    e->reload = (rand()%FPS*2);
}


static void explosionBehav()
{
    Explosion *expl, *prev;
    prev = &stage.explosionHead;
    for(expl = prev->next; expl!=NULL;expl = expl->next)
    {
        expl->posX += expl->dx;
        expl->posY += expl->dy;
        if(--expl->a <= 0)
        {
            if(expl == stage.explosionTail)
            {
                stage.explosionTail = prev;
            }
            prev->next = expl->next;
            free(expl);
            expl = prev;
        }
        prev = expl;
    }
}

static void debrisBehav()
{
    Debris *d, *prev;
    prev = &stage.debrisHead;
    for(d = prev->next; d!=NULL;d = d->next)
    {
        d->posX += d->dx;
        d->posY += d->dy;
        d->posY += 0.5;
        if(--d->life <= 0)
        {
            if(d == stage.debrisTail)
            {
                stage.debrisTail = prev;
            }
            prev->next = d->next;
            free(d);
            d = prev;
        }
        prev = d;
    }
}

static void initStarfield()
{
    int i;
    for(i=0;i<NB_MAX_STAR;i++)
    {
        stars[i].x = (rand() % SCREEN_WIDTH);
        stars[i].y = (rand() % SCREEN_HEIGHT);
        stars[i].speed = 1 + rand() % 8;
    }
}

static void bgBehav()
{
    if(--bgX < -SCREEN_WIDTH)
    {
        bgX = 0;
    }
}

static void starfieldBehav()
{
    int i;
    for(i=0;i<NB_MAX_STAR;i++)
    {
        stars[i].x -= stars[i].speed;
        if(stars[i].x <= 0)
        {
            stars[i].x = SCREEN_WIDTH + stars[i].x;
        }
    }
}

static void addExplosions(int x,int y, int num)
{
    Explosion *e;
    int i;
    for(i=0;i<num;i++)
    {
        e = (Explosion*)malloc(sizeof(Explosion));
        memset(e,0,sizeof(Explosion));
        stage.explosionTail->next = e;
        stage.explosionTail = e;
        e->posX = x + (rand()%32) - (rand()%32);
        e->posY = y + (rand()%32) - (rand()%32);
        e->dx = (rand()%10) - (rand()%10);
        e->dy = (rand()%10) - (rand()%10);
        e->dx/=10;
        e->dy/=10;
        switch (rand()%4)
        {
        case 0:
            e->r = 255;
            break;
        case 1:
            e->r = 255;
            e->g = 128;
            break;
        case 2:
            e->r = 255;
            e->g = 255;
            break;
        default:
            e->r = 255;
            e->g = 255;
            e->b = 255;
            break;

        }
        e->a = (rand()%FPS*3);
    }
}


static void addDebris(Object* e)
{
    Debris *d;
    int x,y,w,h;
    w = e->w/2;
    h = e->h/2;
    for(y = 0;y<=h;y+=h)
    {
        for(x = 0;x<=w;x+=w)
        {
            d = (Debris*)malloc(sizeof(Debris));
            memset(d,0,sizeof(Debris));
            stage.debrisTail->next = d;
            stage.debrisTail = d;
            d->posX = e->posX + e->w/2;
            d->posY = e->posY + e->h/2;
            d->dx = (rand() % 5) - (rand() % 5);
            d->dy = -(5 + (rand() % 12));
            d->life = FPS*2;
            d->texture = e->texture;
            d->rect.x = x;
            d->rect.y = y;
            d->rect.h = h;
            d->rect.w = w;
        }
    }
}
