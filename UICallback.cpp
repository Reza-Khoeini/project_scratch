#include "UICallback.h"
#include "Pen.h"
#include "UICallback.h"
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <stdio.h>

using namespace std ;



static SDL_Texture* sprstamp= nullptr;

void UIsetSpr (SDL_Texture * tex) {
    sprstamp= tex;
}


// clear
void EraseALL(SDL_Renderer *renderer) {
    clearAllDrawing(renderer);
}


//  عکس در مختصات
void onStampXY(SDL_Renderer * renderer , int x , int y) {
    if (!sprstamp) {
        return;
    }

    // پیش فرض 32
    SDL_Rect dst = {x - 16 , y - 16 , 32, 32};
    penStamp(renderer, sprstamp, &dst);
}

void oPenDown() {
    penDown() ;
}

void oPenUp() {
    penUp() ;

}

