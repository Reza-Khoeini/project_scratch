#ifndef UI1_H
#define UI1_H

#include <SDL2/SDL.h>

void drawRect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);
void drawRectOutline(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);
void drawText(const char* text, int x, int y, SDL_Color color);
bool isPointInRect(int px, int py, int x, int y, int w, int h);

void renderMenuBar(void);
void renderSpritePanel(void);
void renderSoundPanel(void);
void renderStage(void);
void renderEventPanel(void);
void renderOperatorPanel(void);
void renderInfoPanel(void);
void render(void);

#endif
