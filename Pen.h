//
// Created by MMSharifiM on 2/17/2026.
//

#ifndef PROJECT_SCRATCH_PEN_H
#define PROJECT_SCRATCH_PEN_H
#include <bits/stdc++.h>
using namespace std ;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <bits/stdc++.h>

void penDown();

void penUp();

void setPenSize(int newSize);

void setPenColor(SDL_Color newColor);

void drawLine (SDL_Renderer * renderer ,int x1, int y1, int x2, int y2);

void clearDrawing(SDL_Renderer * renderer);

void changePenShade( int aount ) ;





#endif //PROJECT_SCRATCH_PEN_H