#pragma once

#include <citro2d.h>
#include <3ds.h>
#include "text.h"
#include "sprite.h"

extern int clearColor;

extern C3D_RenderTarget* top_screen;
extern C3D_RenderTarget* bottom_screen;

void initAllGraphics();
void destroyAllGraphics();
void renderScene();

void checkSystemStatus();
