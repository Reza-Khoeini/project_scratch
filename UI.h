//
// Created by MMSharifiM on 2/17/2026.
//

#ifndef PROJECT_SCRATCH_UI_H
#define PROJECT_SCRATCH_UI_H



#include "UI.h"
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>

using namespace std ;

struct UIButtons {
    float x , y ;
    float widgh , height ;
    bool visible ;
    bool hovered ;


};
extern UIButtons extensionButton;
extern bool extensionPanelOpen;


void  drawExtensionButton(SDL_Renderer * renderer);

void drawUI(SDL_Renderer* renderer);

void handleUIClick(int mouseX, int mouseY);

void drawExtensionPanel(SDL_Renderer* renderer);

bool pointInRect(int x, int y, SDL_Rect rect);




#endif //PROJECT_SCRATCH_UI_H