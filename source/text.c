#include "little3ds/text.h"

C2D_TextBuf g_staticBuf;
C2D_TextBuf g_dynamicBuf;
Text textList[MAX_TEXT_OBJECTS];

C2D_Font fonts[MAX_FONTS];
int fontNum = 0;

void initTextEnv()
{
    g_staticBuf = C2D_TextBufNew(MAX_TEXT);
    g_dynamicBuf = C2D_TextBufNew(MAX_TEXT);
}

Text* newText(Vector2D pos, float p_size, bool p_screen, int p_color, int p_align, char* str, int p_font, bool buffer)
{
    for (int i=0; i<MAX_TEXT_OBJECTS; i++)
    {
        if (!textList[i].toWrite)
        {
            Text* nText = &textList[i];

            nText->toWrite = true;
            nText->position = pos;

            nText->size = p_size;
            nText->screen = p_screen;
            nText->color = p_color;
            nText->alignment = p_align;

            nText->fontID = p_font;

            if (buffer)
                C2D_TextFontParse(&nText->text, fonts[nText->fontID], g_staticBuf, str);
            else
                C2D_TextFontParse(&nText->text, fonts[nText->fontID], g_dynamicBuf, str);
            return nText;
        }
    }
    return NULL;
}

void changeTextStr(Text* t, char* str)
{
    C2D_TextFontParse(&t->text, fonts[t->fontID], g_dynamicBuf, str);
}

void killText(Text* t)
{
    t->toWrite = false;
}

void killAllText()
{
    for (int i=0; i<MAX_TEXT_OBJECTS; i++)
    {
        killText(&textList[i]);
    }
    C2D_TextBufClear(g_staticBuf);
    C2D_TextBufClear(g_dynamicBuf);
}

void renderScreenText(bool p_screen)
{
    for (int i=0; i<MAX_TEXT_OBJECTS; i++)
    {
        if ((textList[i].toWrite) && (textList[i].screen == p_screen))
        {
            C2D_DrawText(&textList[i].text, C2D_WithColor | textList[i].alignment, textList[i].position.x, textList[i].position.y, 0.5f, textList[i].size, textList[i].size, textList[i].color);
        }
    }
}

void newFont(char* path)
{
    if (fontNum < MAX_FONTS)
    {
        fonts[fontNum] = C2D_FontLoad(path);
        fontNum++;
    }
}
