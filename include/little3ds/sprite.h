#pragma once

#include <time.h>
#include <citro2d.h>
#include <stdlib.h>
#include <3ds.h>

#include "vector2D.h"

#define MAX_SPRITES   768

#define TOP_SCREEN  true
#define BOT_SCREEN  false

#define TOP_SCREEN_WIDTH  400
#define BOT_SCREEN_WIDTH  320

#define SCREEN_HEIGHT 240

#define PLAYER_SPRITE   0
#define ALIEN_SPRITE    1
#define BULLET_SPRITE   2
#define BULLET_E_SPRITE 3
#define LIFE_SPRITE     4
#define SHOOTER_SPRITE  5


typedef struct
{
	C2D_Sprite spr;
    C2D_SpriteSheet* sprite_sheet;

    uint16_t cur_frame;

    bool used;
    bool screen;
} Sprite;

extern Sprite sprites[MAX_SPRITES];
extern size_t numSprites;

Sprite* newSprite(bool pscreen, C2D_SpriteSheet* p_sheet, int usedFrame, Vector2D pos, int angle);
void killSprite(Sprite* s);
void killAllSprites();
