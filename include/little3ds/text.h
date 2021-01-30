#pragma once

#include <citro2d.h>
#include <3ds.h>
#include <stdbool.h>
#include "vector2D.h"

#define MAX_TEXT_OBJECTS 60
#define MAX_TEXT 1000

#define MAX_FONTS 15

#define WHITE_TEXT      C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f)
#define YELLOW_TEXT     C2D_Color32f(0.988235294f, 0.97254902f, 0.0f, 1.0f)
#define LIGHT_BLUE_TEXT C2D_Color32f(0.039215686f, 0.8f, 0.949019608f, 1.0f)

typedef struct
{
    Vector2D position;
    C2D_Text text;

    int fontID;

    float size;
    bool screen;
    int color;
    int alignment;

    bool toWrite;
} Text;

extern C2D_TextBuf g_staticBuf;
extern C2D_TextBuf g_dynamicBuf;
extern Text textList[MAX_TEXT_OBJECTS];

extern C2D_Font fonts[MAX_FONTS];
extern int fontNum;

void initTextEnv();

void newFont(char* path);

Text* newText(Vector2D pos, float p_size, bool p_screen, int p_color, int p_align, char* str, int p_font, bool buffer);
void changeTextStr(Text* t, char* str);

void killText(Text* t);
void killAllText();

void renderScreenText(bool p_screen);
