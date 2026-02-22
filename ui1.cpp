#include "ui1.h"
#include "globals.h"
#include <cstdio>

void drawRect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 255);
    SDL_RenderFillRect(gRenderer, &rect);
}

void drawRectOutline(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
}

void drawText(const char* text, int x, int y, SDL_Color color) {
    if (!gFont || !text || text[0] == '\0') return;
    
    SDL_Surface* surface = TTF_RenderText_Blended(gFont, text, color);
    if (!surface) return;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if (texture) {
        SDL_Rect dest = {x, y, surface->w, surface->h};
        SDL_RenderCopy(gRenderer, texture, NULL, &dest);
        SDL_DestroyTexture(texture);
    }
    SDL_FreeSurface(surface);
}

bool isPointInRect(int px, int py, int x, int y, int w, int h) {
    return px >= x && px < x + w && py >= y && py < y + h;
}

void renderMenuBar(void) {
    drawRect(0, 0, WINDOW_WIDTH, 30, 50, 50, 60);
    
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    
    drawText("File", 10, 5, white);
    drawText("[N]ew [S]ave [L]oad", 60, 5, white);
    
    drawText(gProgramRunning ? "RUNNING" : "STOPPED", 300, 5, 
             gProgramRunning ? yellow : white);
    
    char volText[32];
    snprintf(volText, sizeof(volText), "Vol: %d%%", gMasterVolume);
    drawText(volText, WINDOW_WIDTH - 100, 5, white);
}

void renderSpritePanel(void) {
    int panelX = 10;
    int panelY = 40;
    int panelW = 200;
    int panelH = 400;
    
    drawRect(panelX, panelY, panelW, panelH, 60, 60, 70);
    drawRectOutline(panelX, panelY, panelW, panelH, 100, 100, 110);
    
    SDL_Color white = {255, 255, 255, 255};
    
    drawText("-- Sprite Manager --", panelX + 10, panelY + 5, white);
    
    char countText[32];
    snprintf(countText, sizeof(countText), "Sprites: %d", gProject.spriteCount);
    drawText(countText, panelX + 10, panelY + 25, white);
    
    for (int i = 0; i < gProject.spriteCount && i < 8; i++) {
        Sprite* s = &gProject.sprites[i];
        int itemY = panelY + 50 + i * 40;
        
        if (i == gSelectedSprite) {
            drawRect(panelX + 5, itemY, panelW - 10, 35, 80, 80, 100);
        }
        
        SDL_Color itemColor = s->visible ? white : (SDL_Color){150, 150, 150, 255};
        drawText(s->name, panelX + 10, itemY + 2, itemColor);
        
        char posText[48];
        snprintf(posText, sizeof(posText), "x:%.0f y:%.0f", s->x, s->y);
        drawText(posText, panelX + 10, itemY + 18, itemColor);
    }
    
    drawRect(panelX + 10, panelY + panelH - 30, 80, 22, 50, 150, 50);
    drawText("[+] Add", panelX + 15, panelY + panelH - 28, white);
    
    drawRect(panelX + 100, panelY + panelH - 30, 80, 22, 150, 50, 50);
    drawText("[-] Del", panelX + 105, panelY + panelH - 28, white);
}

void renderSoundPanel(void) {
    int panelX = 10;
    int panelY = 450;
    int panelW = 200;
    int panelH = 280;
    
    drawRect(panelX, panelY, panelW, panelH, 80, 60, 90);
    drawRectOutline(panelX, panelY, panelW, panelH, 120, 100, 130);
    
    SDL_Color white = {255, 255, 255, 255};
    
    drawText("-- Sound Manager --", panelX + 10, panelY + 5, white);
    
    char countText[32];
    snprintf(countText, sizeof(countText), "Sounds: %d", gProject.soundCount);
    drawText(countText, panelX + 10, panelY + 25, white);
    
    for (int i = 0; i < gProject.soundCount && i < 5; i++) {
        Sound* snd = &gProject.sounds[i];
        int itemY = panelY + 50 + i * 35;
        
        if (i == gSelectedSound) {
            drawRect(panelX + 5, itemY, panelW - 10, 30, 100, 80, 120);
        }
        
        SDL_Color itemColor = snd->muted ? (SDL_Color){150, 150, 150, 255} : white;
        drawText(snd->name, panelX + 10, itemY + 2, itemColor);
        
        char volText[32];
        snprintf(volText, sizeof(volText), "Vol: %d%% %s", snd->volume, 
                 snd->muted ? "(M)" : "");
        drawText(volText, panelX + 10, itemY + 16, itemColor);
    }
    
    drawRect(panelX + 10, panelY + panelH - 60, 180, 22, 100, 50, 150);
    drawText("[P]lay [T]oggle Mute", panelX + 15, panelY + panelH - 58, white);
    
    drawRect(panelX + 10, panelY + panelH - 30, 80, 22, 50, 150, 50);
    drawText("[+] Add", panelX + 15, panelY + panelH - 28, white);
}

void renderStage(void) {
    int stageX = WINDOW_WIDTH - 500;
    int stageY = 40;
    int stageW = 480;
    int stageH = 360;
    
    drawRect(stageX, stageY, stageW, stageH, 255, 255, 255);
    drawRectOutline(stageX, stageY, stageW, stageH, 100, 100, 100);
    
    int centerX = stageX + stageW / 2;
    int centerY = stageY + stageH / 2;
    double scale = stageW / 480.0;
    
    for (int i = 0; i < gProject.spriteCount; i++) {
        Sprite* s = &gProject.sprites[i];
        if (!s->visible) continue;
        
        int sx = centerX + (int)(s->x * scale);
        int sy = centerY - (int)(s->y * scale);
        int size = (int)(30 * s->size / 100.0);
        
        Uint8 r = (i == gSelectedSprite) ? 255 : 200;
        Uint8 g = (i == gSelectedSprite) ? 100 : 150;
        Uint8 b = 50;
        
        drawRect(sx - size/2, sy - size/2, size, size, r, g, b);
        
        if (i == gSelectedSprite) {
            drawRectOutline(sx - size/2 - 2, sy - size/2 - 2, size + 4, size + 4, 
                           255, 255, 0);
        }
    }
}

void renderEventPanel(void) {
    int panelX = 220;
    int panelY = 40;
    int panelW = 280;
    int panelH = 200;
    
    drawRect(panelX, panelY, panelW, panelH, 255, 200, 50);
    drawRectOutline(panelX, panelY, panelW, panelH, 200, 150, 30);
    
    SDL_Color black = {0, 0, 0, 255};
    
    drawText("-- Events (Section 7) --", panelX + 10, panelY + 5, black);
    
    drawText("[G] When Green Flag Clicked", panelX + 10, panelY + 30, black);
    drawText("[K] When Key Pressed", panelX + 10, panelY + 55, black);
    drawText("[B] Broadcast Message", panelX + 10, panelY + 80, black);
    drawText("[R] When I Receive", panelX + 10, panelY + 105, black);
    drawText("[Space] Start/Stop", panelX + 10, panelY + 130, black);
    
    char statusText[64];
    snprintf(statusText, sizeof(statusText), "Status: %s", 
             gProgramRunning ? "Running" : "Stopped");
    drawText(statusText, panelX + 10, panelY + 160, black);
}

void renderOperatorPanel(void) {
    int panelX = 220;
    int panelY = 250;
    int panelW = 280;
    int panelH = 200;
    
    drawRect(panelX, panelY, panelW, panelH, 100, 200, 100);
    drawRectOutline(panelX, panelY, panelW, panelH, 70, 150, 70);
    
    SDL_Color black = {0, 0, 0, 255};
    
    drawText("-- Operators (Section 10) --", panelX + 10, panelY + 5, black);
    
    drawText("Math: + - * / mod sqrt", panelX + 10, panelY + 30, black);
    drawText("Compare: < > =", panelX + 10, panelY + 55, black);
    drawText("Logic: AND OR NOT", panelX + 10, panelY + 80, black);
    drawText("String: join length letterOf", panelX + 10, panelY + 105, black);
    drawText("Functions: abs floor ceil", panelX + 10, panelY + 130, black);
    drawText("Trig: sin cos | random", panelX + 10, panelY + 155, black);
}

void renderInfoPanel(void) {
    int panelX = 220;
    int panelY = 460;
    int panelW = 280;
    int panelH = 270;
    
    drawRect(panelX, panelY, panelW, panelH, 70, 70, 80);
    drawRectOutline(panelX, panelY, panelW, panelH, 100, 100, 110);
    
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color cyan = {100, 255, 255, 255};
    
    drawText("-- Selected Sprite Info --", panelX + 10, panelY + 5, white);
    
    if (gSelectedSprite >= 0 && gSelectedSprite < gProject.spriteCount) {
        Sprite* s = &gProject.sprites[gSelectedSprite];
        
        char text[64];
        
        snprintf(text, sizeof(text), "Name: %s", s->name);
        drawText(text, panelX + 10, panelY + 30, cyan);
        
        snprintf(text, sizeof(text), "Position: (%.1f, %.1f)", s->x, s->y);
        drawText(text, panelX + 10, panelY + 55, white);
        
        snprintf(text, sizeof(text), "Direction: %.1f", s->direction);
        drawText(text, panelX + 10, panelY + 80, white);
        
        snprintf(text, sizeof(text), "Size: %.0f%%", s->size);
        drawText(text, panelX + 10, panelY + 105, white);
        
        snprintf(text, sizeof(text), "Visible: %s", s->visible ? "Yes" : "No");
        drawText(text, panelX + 10, panelY + 130, white);
        
        drawText("Controls:", panelX + 10, panelY + 160, cyan);
        drawText("Arrows: Move sprite", panelX + 10, panelY + 180, white);
        drawText("Q/E: Rotate | +/-: Size", panelX + 10, panelY + 200, white);
        drawText("V: Toggle Visibility", panelX + 10, panelY + 220, white);
        drawText("1-9: Select Sprite", panelX + 10, panelY + 240, white);
    } else {
        drawText("No sprite selected", panelX + 10, panelY + 30, white);
    }
}

void render(void) {
    SDL_SetRenderDrawColor(gRenderer, 40, 42, 54, 255);
    SDL_RenderClear(gRenderer);
    
    renderMenuBar();
    renderSpritePanel();
    renderSoundPanel();
    renderStage();
    renderEventPanel();
    renderOperatorPanel();
    renderInfoPanel();
    
    SDL_RenderPresent(gRenderer);
}
