//
// Created by MMSharifiM on 2/17/2026.
//

#ifndef PROJECT_SCRATCH_UI_H
#define PROJECT_SCRATCH_UI_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>

using namespace std ;

enum {
    coNone = 0 ,
    coPen ,
    coEraser ,
    coFill ,
    coText ,
    coLine ,
};

void uiInitCostButt() ;


void haveUI(SDL_Renderer * renderer, int w , int h);

// void CloseUI() ;
void  drawUI(SDL_Renderer * renderer);

void handleUIClick(int mouseX, int mouseY);
int uiIsOk() ;



void addButton (int x,int y ,int w ,int h , const char* id , const char * text) ;

void Shutdown();

void uiCostum() ;
int uiCostumGET() ;
void uiCostumSET(int tool) ;


#endif //PROJECT_SCRATCH_UI_H