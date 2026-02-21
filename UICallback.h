//
// Created by MMSharifiM on 2/19/2026.
//

#ifndef PROJECT_SCRATCH_UICALLBACK_H
#define PROJECT_SCRATCH_UICALLBACK_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>


using namespace std ;

//  پاکسازی کامل
void EraseALL(SDL_Renderer* renderer);


//  عکس در مختصات
void onStampXY(SDL_Renderer * renderer , int x , int y) ;

//  وضعیت قلم
void oPenDown();
void oPenUp();

//  تنظیم کننده
 void UIsetSpr (SDL_Texture * tex);




#endif //PROJECT_SCRATCH_UICALLBACK_H