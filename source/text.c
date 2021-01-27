#include "text.h"

C2D_TextBuf g_staticBuf;
C2D_TextBuf g_dynamicBuf;
Text textList[MAX_TEXT_OBJECTS];
C2D_Font arcadeFont;

void initTextEnv()
{
    g_staticBuf = C2D_TextBufNew(MAX_TEXT);
    g_dynamicBuf = C2D_TextBufNew(MAX_TEXT);

    arcadeFont = C2D_FontLoad("romfs:/gfx/arcade.bcfnt");
}

Text* newText(Vector2D pos, float p_size, bool p_screen, int p_color, int p_align, char* str, bool buffer)
{
    for (int i=0; i<MAX_TEXT_OBJECTS; i++)
    {
        if (!textList[i].toWrite)
        {
            Text* nText = &textList[i];

            nText->toWrite = true;
            nText->position = pos;
            nText->textID = i;

            nText->size = p_size;
            nText->screen = p_screen;
            nText->color = p_color;
            nText->alignment = p_align;

            if (buffer)
                C2D_TextFontParse(&nText->text, arcadeFont, g_staticBuf, str);
            else
                C2D_TextFontParse(&nText->text, arcadeFont, g_dynamicBuf, str);
            return nText;
        }
    }
    return NULL;
}

void changeTextStr(Text* t, char* str)
{
    C2D_TextFontParse(&t->text, arcadeFont, g_dynamicBuf, str);
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
