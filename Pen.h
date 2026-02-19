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



 void penInit() ;
void penShutdown() ;

void penDown();
void penUp();


void setPenSize(int newSize);
int getPenSize();



void setPenColor(SDL_Color newColor) ;
SDL_Color getPenColor();


void setPenHSB(float  Hue,float  Sat,float  Bright) ;
//  برای تغییر رنگ تدریجی همان اشباع و شفافیت
void changePenHue(float delta) ;
void changePenSat(float delta) ;
void changePenBright(float delta) ;


//  مرتبط با DrawLayer
void drawLine (SDL_Renderer * renderer ,int x1, int y1, int x2, int y2);

void clearAllDrawing(SDL_Renderer * renderer);

void penStamp(SDL_Renderer * renderer , SDL_Texture * texture, SDL_Rect * dst) ;

//  در ارتباط با UI
void penEn() ;
void penDis() ;
int penisEn() ;

#endif //PROJECT_SCRATCH_PEN_H