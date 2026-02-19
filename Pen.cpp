#include "Pen.h"
#include "ColorUtil.h"
#include "Drawlayer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <bits/stdc++.h>
#include "Drawlayer.h"


//  فعال است = 1 وگرنه = 0
static int penEn1 = 0 ;


static int penSize = 2; // پیش فرض

 static bool penIsDown = false ;
static SDL_Color penColor = { 255, 255, 255  , 255 };
// کامپایلر  flaot  بگیرد (بهینه شدن) (  f )
static float hue =  0.0f;
static float sat = 0.0f;
static float bright = 1.0f ;

void penInit() {
    penEn1 = 0 ;
    penIsDown = false;
    penSize = 2;
    hue =0;
    sat = 1;
    bright = 1.0 ;

    penColor = changeColorSlow();
}

void penEn() {
    penEn1 = 1 ;
}
void penDis() {
    penEn1 = 0 ;
}

int penisEn() {
    return penEn1 ;
}



void penDown() {
    penIsDown = true ;
}
void penUp() {
    penIsDown = false;
}


void setPenSize(int newSize) {
    if ( newSize > 0 ) {
        penSize = newSize;
    }
    else {
        penSize  = 1 ;
    }
}
int getPenSize() {
    return penSize ;
}


void setPenColor(SDL_Color newColor) {
    penColor = newColor;
}
SDL_Color getPenColor() {
    return penColor ;
}





void setPenHSB(float  Hue,float  Sat,float  Bright) {
    hue = Hue ;
    if (hue < 0 ) {
        // hue = hue %  360 +360  ; //   برای باقی مانده گیزی از اعاد اعشاری مجبور به استفاده از  fmodf  هستیم
        hue = fmodf( hue, 360.f) +360 ;
    }
    if (hue > 360.f) {
        //  دوباره باقی مانده تا در بازه باشد
         hue = fmodf(hue, 360.f) ;
    }
    if ( Sat <= 0) {
        Sat = 0 ;
    }
    if (Sat > 1 ) {
        Sat = 1 ;
    }
    if (Sat <0  ) {
        sat = 0 ;
    }
    sat = Sat ;
    if (Bright <= 0) {
        Bright = 0 ;
    }
    if (Bright > 1  ) {
        Bright = 1 ;
    }
    bright = Bright ;
    penColor = changeColorSlow();
}

//  برای تغییر رنگ تدریجی همان اشباع و شفافیت-><-
void changePenHue(float delta) {
    setPenHSB(hue + delta,sat,bright);
}
void changePenSat(float delta) {
    setPenHSB(hue ,sat + delta ,bright);
}
void changePenBright(float delta) {
    setPenHSB(hue ,sat  ,bright+ delta);
}

void drawLine (SDL_Renderer * renderer ,int x1, int y1, int x2, int y2) {
    if (!penEn1 ) {
        return;
    }
    if (!penIsDown ) {
        return;
    }
    drawLineOneLayer(renderer , x1, y1, x2, y2,penColor, penSize);
}


void penStamp(SDL_Renderer * renderer , SDL_Texture * texture, SDL_Rect * dst) {
    if (!penEn1 ) {
        return;
    }
    if (!texture || !dst) {
        return;
    }
    stampOneLayer(renderer , texture, dst);
}

// clear all !!
void clearAllDrawing(SDL_Renderer * renderer) {
    clearDrawLayer( renderer) ;
}

