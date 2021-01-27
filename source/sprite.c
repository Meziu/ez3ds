#include "sprite.h"

C2D_SpriteSheet general_spriteSheet;
Sprite sprites[MAX_SPRITES];
size_t numSprites = 0;

Sprite* newSprite(bool pscreen, int usedFrame, Vector2D pos, int angle)
{
    for (int i = 0; i < MAX_SPRITES; i++)
	{
        if (!sprites[i].used)
        {
            Sprite* nSprite = &sprites[i];

            nSprite->used = true;
            nSprite->screen = pscreen;

            // Random image, position, rotation and speed
            C2D_SpriteFromSheet(&nSprite->spr, general_spriteSheet, usedFrame);
            C2D_SpriteSetCenter(&nSprite->spr, 0.5f, 0.5f);
            C2D_SpriteSetPos(&nSprite->spr, (int)pos.x, (int)pos.y);
            
            C2D_SpriteSetRotation(&nSprite->spr, C3D_Angle(angle));

            numSprites++;
            return nSprite;
        }
    }
    svcBreak(USERBREAK_PANIC);
    return NULL;
}

void killSprite(Sprite* s)
{
    s->used = false;
    numSprites--;
}

void killAllSprites()
{
    for (int i = 0; i < MAX_SPRITES; i++)
	{
        killSprite(&sprites[i]);
    }
}
