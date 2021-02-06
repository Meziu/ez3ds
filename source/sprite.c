#include "little3ds/sprite.h"

Sprite sprites[MAX_SPRITES];
size_t numSprites = 0;

Sprite* newSprite(bool pscreen, C2D_SpriteSheet* p_sheet, int usedFrame, Vector2D pos, int angle)
{
    for (int i = 0; i < MAX_SPRITES; i++)
	{
        if (!sprites[i].used)
        {
            Sprite* nSprite = &sprites[i];

            nSprite->used = true;
            nSprite->screen = pscreen;
            nSprite->sprite_sheet = p_sheet;
            nSprite->cur_frame = (uint16_t)usedFrame;

            // Random image, position, rotation and speed
            C2D_SpriteFromSheet(&nSprite->spr, *nSprite->sprite_sheet, (int)nSprite->cur_frame);
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
