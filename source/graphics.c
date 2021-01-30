#include "little3ds/graphics.h"

int clearColor;

C3D_RenderTarget* top_screen;
C3D_RenderTarget* bottom_screen;

void initAllGraphics()
{
    gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

    initTextEnv();

    // Create screens
	top_screen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	bottom_screen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    general_spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!general_spriteSheet) svcBreak(USERBREAK_PANIC);
}

void destroyAllGraphics()
{
    // Delete graphics
	C2D_SpriteSheetFree(general_spriteSheet);

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
}

void renderScene()
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(bottom_screen, clearColor);
	C2D_TargetClear(top_screen, clearColor);

	C2D_SceneBegin(top_screen);
	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		if (sprites[i].used && sprites[i].screen == TOP_SCREEN)
			C2D_DrawSprite(&sprites[i].spr);
	}
	renderScreenText(TOP_SCREEN);

		
	C2D_SceneBegin(bottom_screen);
	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		if (sprites[i].used && sprites[i].screen == BOT_SCREEN)
			C2D_DrawSprite(&sprites[i].spr);
	}
	renderScreenText(BOT_SCREEN);
	C3D_FrameEnd(0);
}

// prints debug info
void checkSystemStatus()
{
	printf("\x1b[1;1HSprites: %zu/%u\x1b[K", numSprites, MAX_SPRITES);
	printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
	printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
}
