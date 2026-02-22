#include "Pen.h"
#include "ColorUtil.h"
#include "Drawlayer.h"
#include <cmath>

//  فعال است = 1 وگرنه = 0
static int penEn1 = 0 ;


static int penSize = 2; // پیش فرض

 static bool penIsDown = false ;
static SDL_Color penColor = { 255, 255, 255  , 255 };
// کامپایلر  flaot  بگیرد (بهینه شدن) (  f )
static float hue =  0.0f;
static float sat = 0.0f;
static float bright = 1.0f ;




static SDL_Color hsbTorgb(float h , float s , float v) {
    if (s<0.f) {
        s=0.f;
    }
    if (s>1.f) {
        s=1.f;
    }
    if (v>1.f) {
        v=1.f;
    }
    if (v<0.f) {
        v=0.f;
    }
    h = std::fmod(h, 360.f);
    if (h<0.f) {
        h+= 360.f;
    }
    float c  = v*s ;
    float x  = c*(1.f-std::fabs(std::fmod(h, 360.f)));
    float m  = v-c ;
    float r1 = 0 ,  g1 = 0 , b1 = 0 ;
    if (h<60) {
        r1 = c ;
        g1 = x ;
        b1 = 0 ;
    }
    else if (h <120) {
        r1 = x;
        g1 = c;
        b1 = 0;
    }
    else if (h < 180) {
        r1 = 0;
        g1 = c;
        b1 = x;
    }
    else if (h < 240) {
        r1 = 0;
        g1 = x;
        b1 = c;
    }
    else if (h < 300) {
        r1 = x;
        g1 = 0;
        b1 = c;
    }
    else {
        r1 = c;
        g1 = 0;
        b1 = x;
    }

    Uint8 r = (Uint8)std::lround((r1 + m) * 255.f);
    Uint8 g = (Uint8)std::lround((g1 + m) * 255.f);
    Uint8 b = (Uint8)std::lround((b1 + m) * 255.f);

    return SDL_Color{r, g, b, 255};
}







void penInit() {
    penEn1 = 0 ;
    penIsDown = false;
    penSize = 2;
    hue =0.f;
    sat = 1.f;
    bright = 1.0f ;

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
        penSize = newSize > 0 ? newSize : 1;
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
    sat = Sat ;
    bright = Bright ;
    penColor = hsbTorgb(hue,sat, bright);
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
    if (!penEn1 || !penIsDown ) {
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

