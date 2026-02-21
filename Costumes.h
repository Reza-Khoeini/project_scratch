//
// Created by MMSharifM on 2/20/2026.
//

#ifndef PROJECT_SCRATCH_COSTUMES_H
#define PROJECT_SCRATCH_COSTUMES_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include  <bits/stdc++.h>
using namespace std ;

#define MAX_COSTUMES    70
#define NAME_LENGTH 140

typedef struct {

    char name[NAME_LENGTH];
    SDL_Surface * surface;
    // برای رندر
    SDL_Texture * texture;
    // اندازه surf
    int w , h ;
     //موقعیت روی صفحه
    int x , y ;
    bool visible ;
    int isBackDROP ;

} Custome ;

// ورود  costim
  int costumeINit(SDL_Renderer * rende) ;
// آزاد سازی منابع
void costumeShtingdown(SDL_Renderer * renderer) ;

// آپلود تصویر
int ADD_image(SDL_Renderer *renderer , const char* path , const char *name , int isbackdrop);

// draw
void drawBkD(SDL_Renderer * renderer) ;
void drawSprite(SDL_Renderer * renderer);
void drawPreview(SDL_Renderer *renderer);
void drawEditorPlace(SDL_Renderer * renderer);
// select
int counterCOST() ;
void Selct(int idx) ;
int getSelect() ;

void costSetPosi(int idx , int x , int y) ;


//  تغییر افقی و عمودی

void flipHorizontal(int idx) ;
void flipVertical(int idx) ;


// توابع مخصوص رسم و اعمال تغییر  آنی  روی بخش  perview
 void Pen(int idx , int cx , int cy, SDL_Color color , int r) ;

void Eraser(int idx , int cx , int cy , int r) ;

void Fill(int idx , int cx , int cy , SDL_Color color , int r ) ;

void Text(int idx , const char* txt , int cx , int cy , TTF_Font* font  , SDL_Color color ) ;

void Line(int idx , int x1 , int y1 , int x2 , int y2 , SDL_Color color , int thick ) ;

void saveEdit(SDL_Renderer * renderer , int idx) ;

// ذخیره کردن
int  SavetoFile(int idx , const char* filepath ) ;

//  جایگاه  edit , perview
void GetPreviwRect(SDL_Rect * rect) ;
void GetEditRect(SDL_Rect * rect) ;



int costgetSIZE(int idx , int * outW , int * outH );
void cosSetSize(int idx , int  newW , int newH);

//  محل نمایش تصویر در ادیتور
void costGETEDIimg(int idx , SDL_Rect * outdst) ;

#endif //PROJECT_SCRATCH_COSTUMES_H