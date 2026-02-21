//
// Created by MMSharifiM on 2/18/2026.
//

#ifndef PROJECT_SCRATCH_DRAWLAYER_H
#define PROJECT_SCRATCH_DRAWLAYER_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>


using namespace std ;

 // produce texure
bool initDrawLayer(SDL_Renderer * renderer , int w , int h) ;

void destroyLayerPresent() ;

// erase all
void clearDrawLayer(SDL_Renderer* renderer ) ;

// // draw texture
void drawLayerPresent(SDL_Renderer * renderer) ;
// void drawLayerPresent(SDL_Renderer* renderer);

void drawLineOneLayer(SDL_Renderer * renderer , int x1 , int y1 , int x2 , int y2 ,SDL_Color color , int Size ) ;

// copy one dst on tex
void stampOneLayer(SDL_Renderer * renderer , SDL_Texture * spriteText , const SDL_Rect*  dst) ;

void freeDrawLayer();

#endif //PROJECT_SCRATCH_DRAWLAYER_H