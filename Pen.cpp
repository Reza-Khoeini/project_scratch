#include "Pen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <bits/stdc++.h>


bool penIsDown = false ;

int penSize = 1  ;


SDL_Color penColor = { 255, 255, 255  , 255 };
void penDown() {
    penIsDown = true;
}

void penUp() {
    penIsDown = false;
}

void setPenSize(int newSize) {
    if (newSize <= 0 ) {
        newSize = 1;
    }
    penSize = newSize;
}

void setPenColor(SDL_Color newColor) {
     penColor.r = newColor.r   ;
     penColor.g = newColor.g  ;
    penColor.b = newColor.b ;
    penColor.a = newColor.a  ;
}

void drawLine (SDL_Renderer * renderer ,int x1, int y1, int x2, int y2) {

    if (penIsDown == false) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, penColor.r, penColor.g, penColor.b, penColor.a);
    aalineRGBA(renderer , x1 , y1 , x2, y2,penColor.r, penColor.g, penColor.b, penColor.a);
}


void clearDrawing(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
}





