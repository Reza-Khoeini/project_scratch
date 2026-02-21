#include "Costumes.h"
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include  <bits/stdc++.h>
using namespace std ;
#include <string.h>


static  Custome costums[MAX_COSTUMES] ;
static int counter =0 ;
static int isSelect = -1 ;
static SDL_Renderer * Renderer  = nullptr;

// perview , editor مقادیر

static const int PerviewX = 650 ;
static const int PerviewY = 10 ;
static const int PerviewW= 200 ;
static const int PerviewH = 200 ;

static const int EditorW = 420 ;
static const int EditorH = 420 ;

static int windowW = 1000 ;
static int windowH = 900 ;
static inline Uint32 get_pixel32(SDL_Surface *surface, int x, int y) {
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    return *(Uint32*)p;
}

static inline void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32*)p = pixel;
}
static Uint32 colorToPixel(SDL_Surface* surf, SDL_Color c) {
    return SDL_MapRGBA(surf->format, c.r, c.g, c.b, c.a);
}
static inline int inBounds(SDL_Surface* surf, int x, int y) {
    return (x >= 0 && y >= 0 && x < surf->w && y < surf->h);
}


// init &&& shutingdown

int costumeINit(SDL_Renderer *renderer) {
    if (!renderer) {
        return 0 ;
    }
    Renderer = renderer;
    counter =0 ;
    isSelect = -1 ;
    return 1 ;
}

void costumeShtingdown(SDL_Renderer * renderer) {
    // برای  ساکت کردن کامپایلز
    (void) renderer ;
    for (int i = 0 ; i<counter ; i++) {
        if (costums [i].texture) {
            SDL_DestroyTexture(costums [i].texture);
            costums[i].texture = nullptr;
        }
        if (costums [i].surface ) {
            SDL_FreeSurface(costums [i].surface);
            costums[i].texture = nullptr;
        }
    }
    counter =0 ;
    isSelect = -1 ;
    renderer = nullptr;
}


static void updateTexure(int idx) {
    if (idx < 0 || idx >= counter) {
        return ;
    }
    if (!Renderer) {
        SDL_Log("updateTexture: Renderer is null");
        return;
    }
    Custome* c = &costums [idx];
    if (!c->surface) {
        return;
    }
    if (c->texture) {
        SDL_DestroyTexture(c->texture);
        c->texture = nullptr;
    }
    c->texture = SDL_CreateTextureFromSurface(Renderer, c->surface);
    c->w = c->surface->w;
    c->h = c->surface->h;
}


// add and laod

int ADD_image(SDL_Renderer *renderer , const char* path , const char *name , int isbackdrop) {
    if (!renderer || !path) {
        return -1 ;
    }
    if (counter >= MAX_COSTUMES) {
        return -1 ;
    }
    SDL_Surface * loading = IMG_Load(path);
    if (!loading) {
        SDL_Log("Img can not load" , IMG_GetError()) ;
        return -1 ;
    }
    SDL_Surface* surf = SDL_ConvertSurfaceFormat( loading , SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(loading);
    if (!surf) {
        SDL_Log("SDL_ConvertSurfaceFormat() failed"  );
        return -1 ;
    }
    Custome* c = &costums [counter] ;
    strncpy(c->name , name ? name : path , NAME_LENGTH - 1 ) ;
    c->name[NAME_LENGTH - 1] = '\0' ;
    c->surface = surf ;
    c->texture = SDL_CreateTextureFromSurface(Renderer, surf);
    if (!c->texture) {
        SDL_Log("SDL_CreateTextureFromSurface() failed"  , SDL_GetError() ) ;
    }
    c->w = surf->w;
    c->h = surf->h;
    //  مکان اولیه
    c->x  = 50 + (counter * 20) % 400;
    c->y  = 50 + (counter * 10) % 300;
    c->visible = 1;
    c -> isBackDROP = isbackdrop ? 1 : 0 ;
    counter++;
    return counter - 1 ;
}

// count //selecting // info

int counterCOST() {
    return counter ;
}

void Selct(int idx) {
    if (idx < 0 || idx >= counter) {
        isSelect = -1 ;
    }
    else {
        isSelect = idx ;
    }
}

int getSelect() {
    return isSelect ;
}

void costSetPosi(int idx , int x , int y) {
    if (idx < 0 || idx >= counter) {
        return;
    }
    costums [idx].x = x ;
    costums [idx].y = y ;
}
void cosSetSize(int idx , int  newW , int newH) {
    if (idx < 0 || idx >= counter) {
        return;
    }
    costums [idx].w = newW ;
    costums [idx].h = newH ;
}


// flipes

void flipHorizontal(int idx) {
    if (idx < 0 || idx >= counter) {
        return;
    }
    Custome* c = &costums [idx] ;
    if (!c -> surface) {
        return ;
    }
    SDL_Surface * s = c->surface ;
    SDL_Surface* ns = SDL_CreateRGBSurfaceWithFormat(0, s->w ,  s->h , 32 ,  s->format->format);
    if (!ns ) {
        return ;
    }
    SDL_LockSurface(s);
    SDL_LockSurface(ns);
    for (int y = 0 ; y < s->h ; y++) {
        for (int x = 0 ; x < s->w ; x++) {
            Uint32 pixel = get_pixel32(s, x, y) ;
            put_pixel32(ns, s->w-1-x, y, pixel);
        }
    }
    SDL_UnlockSurface(ns);
    SDL_UnlockSurface(s);
    SDL_FreeSurface(c->surface);
    c->surface = ns;
    updateTexure(idx) ;
}
void flipVertical(int idx) {
    if (idx < 0 || idx >= counter) {
        return;
    }
    Custome* c = &costums [idx] ;
    if (!c -> surface) {
        return ;
    }
    SDL_Surface * s = c->surface ;
    SDL_Surface* ns = SDL_CreateRGBSurfaceWithFormat(0, s->w ,  s->h , 32 ,  s->format->format);
    if (!ns ) {
        return ;
    }
    SDL_LockSurface(s);
    SDL_LockSurface(ns);
    for (int y = 0 ; y < s->h ; y++) {
        for (int x = 0 ; x < s->w ; x++) {
            Uint32 pixel = get_pixel32(s, x, y) ;
            put_pixel32(ns,x, s->h-1-y, pixel);
        }
    }
    SDL_UnlockSurface(ns);
    SDL_UnlockSurface(s);
    SDL_FreeSurface(c->surface);
    c->surface = ns;
    updateTexure(idx) ;
}


// draw functions ............
// backdrops
void drawBkD(SDL_Renderer * renderer) {
    for (int i=0;i<counter;i++) {
        Custome* c = &costums [i] ;
        if (!c->visible || !c->texture) {
            continue;
        }
        if (!c->isBackDROP ) {
            continue;
        }
        SDL_Rect dest = {c->x , c->y , c->w , c->h} ;
        SDL_RenderCopy(renderer, c->texture , nullptr , &dest);
    }
}

// drawing SPRITE
void drawSprite(SDL_Renderer * renderer) {
    for (int i=0;i<counter;i++) {
        Custome* c = &costums [i] ;
        if (!c->visible || !c->texture) {
            continue ;
        }
        if (c->isBackDROP ) {
            continue;
        }
        SDL_Rect dest = {c->x , c->y , c->w , c->h} ;
        SDL_RenderCopy(renderer, c->texture , nullptr , &dest);
    }
}

void drawPreview(SDL_Renderer * renderer) {
    SDL_Rect pr = {PerviewX,PerviewY,PerviewW,PerviewH} ;
    //  بخش بک گراند
    SDL_SetRenderDrawColor(renderer, 50 , 50 , 50 , 200 ) ;
    SDL_RenderFillRect(renderer, &pr);
    SDL_SetRenderDrawColor(renderer, 255 , 255 , 255 , 250 ) ;
    SDL_RenderDrawRect( renderer,&pr);


    if (isSelect < 0|| isSelect >= counter ) {
        return ;
    }
    Custome* c = &costums [isSelect ] ;
    if (!c -> surface) {
        return ;
    }
    if (!c ->texture) {
        return ;
    }

    if (c->w <= 0 || c->h <= 0) {
        return ;
    }
    //  تصویر به اندازه  scale
    float sx = (float )PerviewW  / (float )c->w;
    float sy = (float )PerviewH  / (float )c->h;
    float s = sx < sy ? sx : sy ;
    int dw  =(int)(c->w * s);
    int dh  = (int)(c->h * s);
     int dx = PerviewX  + ( PerviewW - dw ) / 2 ;
    int dy = PerviewY  + ( PerviewH - dh ) / 2 ;
    SDL_Rect dest = {dx,dy,dw,dh} ;
    SDL_RenderCopy(renderer, c->texture , nullptr , &dest);
}


// EDITOR AREA
void drawEditorPlace(SDL_Renderer * renderer) {
    //  مرکز پنجره
    int ex = (windowW - EditorW ) / 2 ;
    int ey = (windowH - EditorH ) / 2 ;
    SDL_Rect editrect = {ex,ey , EditorW,EditorH} ;
    //  پس زمیته editor
    SDL_SetRenderDrawColor(renderer, 230 , 230 , 230 , 250 ) ;
    SDL_RenderFillRect(renderer, &editrect);
    SDL_SetRenderDrawColor(renderer, 0 , 0 , 0 , 255 ) ;
    SDL_RenderDrawRect(renderer,&editrect);

    //  در صورت انتخاب تصویر اینجا نمایش ئائه می شود

    if (isSelect < 0|| isSelect >= counter ) {
        return ;
    }
    Custome* c = &costums [isSelect ] ;
    if (!c -> surface) {
        return ;
    }

    if (c->w <= 0 || c->h <= 0) {
        return ;
    }
    float sx = (float )EditorW / (float )c->w;
    float sy = (float )EditorH / (float )c->h;
    float s = sx < sy ? sx : sy ;
    int dw  =(int)(c->w * s);
    int dh  =(int)(c->h * s);
    int dx = ex  + ( EditorW - dw ) / 2 ;
    int dy = ey  + ( EditorH - dh ) / 2 ;
    SDL_Rect dest = {dx,dy,dw,dh} ;
    SDL_RenderCopy(renderer, c->texture , nullptr , &dest);
    //
}

void costGETEDIimg(int idx , SDL_Rect * outdst) {

    if (!outdst) {
        return ;
    }
    //  محاسبات عینا شبیه  drawEditorPlace

    int ex = (windowW - EditorW) / 2 ;
    int  ey = ( windowH - EditorH) / 2 ;
    outdst->x = ex  ;
    outdst->y = ey ;
    outdst->w = EditorW ;
    outdst->h = EditorH ;
    if (idx < 0 || idx >= counter) {
        return ;
    }
    Custome* c =&costums [idx] ;
    if (!c->texture) {
        return ;
    }
    float sx =  (float )EditorW / (float )c->w;
    float sy =  (float )EditorH / (float )c->h ;
    float s = sx < sy ? sx : sy ;
    int dw = (int)(c->w * s);
    int dh = (int)(c->h * s);
    int dx = ex + (EditorW - dw ) / 2 ;
    int dy = ey + (EditorH - dh ) / 2 ;
    outdst->x = dx;
    outdst->y = dy;
    outdst->w = EditorW ;
    outdst->h = EditorH ;
}


//  ارتباط با موس
void GetPreviwRect(SDL_Rect * rect) {
    if (!rect) {
        return ;
    }
    rect->x = PerviewX ;
    rect->y = PerviewY ;
    rect->w = PerviewW ;
    rect->h = PerviewH ;
}

void GetEditRect(SDL_Rect * rect) {
    if (!rect) {
        return ;
    }
    int ex = (windowW - EditorW ) / 2 ;
    int ey = (windowH - EditorH ) / 2 ;
    rect->x = ex ;
    rect->y = ey ;
    rect->w = EditorW ;
    rect->h = EditorH ;
}

// در صورت تغییر اندازه پنجره بروز رسانی می کنیم

//  pen // text // line

void Pen(int idx , int cx , int cy, SDL_Color color , int r) {
    if (idx < 0 || idx >= counter) {
        return ;
    }
    Custome* c = &costums [idx] ;
    if (!c -> surface) {
        return ;
    }
    SDL_Surface* s = c->surface;
    SDL_LockSurface(s);
    UINT32 pixel  = colorToPixel(s, color);
    int r2 = r*r ;
    for (int dy = -r ; dy <= r ; dy++) {
        for (int dx = -r ; dx <= r ; dx++) {
            int x = cx + dx ;
            int y = cy + dy ;
            if(((dx*dx+dy*dy)<=r2)&& inBounds(s,x,y)) {
                put_pixel32(s,x,y,pixel) ;
            }
        }
    }
    SDL_UnlockSurface(s);
    updateTexure(idx) ;
}

void Eraser(int idx , int cx , int cy , int r) {
    if (idx < 0 || idx >= counter) {
        return;
    }
        Custome* c = &costums [idx] ;
        if (!c -> surface) {
            return ;
        }
        SDL_Surface* s = c->surface;
        SDL_LockSurface(s);
        Uint32 clearpix = SDL_MapRGBA( s->format , 0,0,0,0) ;
        int r2 = r*r ;
        for (int dy = -r ; dy <= r ; dy++) {
            for (int dx = -r ; dx <= r ; dx++) {
                 int x = cx + dx ;
                int y = cy + dy ;
                if (((dx*dx+dy*dy)<=r2) && inBounds(s,x,y)) {
                    put_pixel32(s,x,y,clearpix);
                }
            }
        }
        SDL_UnlockSurface(s);
        updateTexure(idx) ;
    }

void Fill(int idx , int cx , int cy , SDL_Color color , int r ) {
    if (idx < 0 || idx >= counter) {
        return ;
    }
    Custome* c = &costums [idx] ;
    if (!c -> surface) {
        return ;
    }
    SDL_Surface* s = c->surface;
    if (!inBounds(s,cx,cy)) {
        return ;
    }
    SDL_LockSurface(s);
    UINT32 target = get_pixel32(s,cx,cy) ;
    Uint32 newpixel = colorToPixel( s , color) ;
    if (target == newpixel) {
        SDL_UnlockSurface(s);
        return ;
    }
    std::vector<std::pair<int,int>> stack ;
    stack.reserve(1024) ;
    stack.push_back({cx,cy}) ;
    while (!stack.empty()) {
        auto p = stack.back() ;
        stack.pop_back() ;
        int x = p.first ;
        int y = p.second ;
        int left = x ;
        while (left > 0 && get_pixel32(s,left-1,y) == target) {
            left -= 1 ;
        }
        int right = x ;
        while (right < s->w-1 && get_pixel32(s,right+1,y) == target) {
            right += 1 ;
        }
        for (int px= left ; px <= right ; px++) {
            put_pixel32(s,px,y,newpixel);
            if (y > 0 && get_pixel32(s,px,y-1) == target) {
                stack.push_back({px,y-1}) ;
            }
            if (y < s->h-1 && get_pixel32(s,px,y+1) == target) {
                stack.push_back({px,y+1}) ;
            }
        }
    }
    SDL_UnlockSurface(s);
    updateTexure(idx) ;
}

static void drawlinesurf(SDL_Surface* s , int x0 , int y0 , int x1 , int y1 , Uint32 pixel , int thick ) {
    int dx = abs(x1 - x0) , sx = x0 < x1 ? 1 : -1 ;
    int dy = -abs(y1 - y0) , sy = y0 < y1 ? 1 : -1 ;
    int er = dx + dy ;
    while (1) {
        for (int yy = -thick ; yy <= thick ; yy++) {
            for (int xx = -thick ; xx <= thick ; xx++) {
              if (xx*xx + yy*yy <= thick*thick) {
                  int px = x0+xx ;
                  int py = y0+yy ;
                  if (px > 0 && py >= 0 && px < s->w && py < s->h) {
                      put_pixel32(s,px,py,pixel) ;
                  }
              }
            }
        }
        if (x0 == x1 && y0 == y1) {
            break;
        }
        int ee = 2*er ;
        if (ee >= dy ) {
            ee+=dy;
            x0+= sx ;
        }
        if (ee < dx ) {
            ee+=dx ;
            y0+= sy ;
        }
    }
}
void Line(int idx , int x1 , int y1 , int x2 , int y2 , SDL_Color color , int thick ) {
    if (idx < 0 || idx >= counter) {
        return ;
    }
    Custome* c = &costums [idx] ;
    if (!c -> surface) {
        return ;
    }
    Uint32 pixel = colorToPixel(c->surface , color) ;
    SDL_LockSurface(c->surface);
    drawlinesurf(c->surface, x1,y1,x2,y2,pixel,thick);
    SDL_UnlockSurface(c->surface);
    updateTexure(idx) ;
}

void Text(int idx , const char* txt , int cx , int cy , TTF_Font* font  , SDL_Color color ) {
    if (idx < 0 || idx >= counter || !font || !txt) {
        return ;
    }
    Custome* c = &costums [idx] ;
    if (!c -> surface) {
        return ;
    }
    SDL_Surface* TxT = TTF_RenderUTF8_Blended(font,txt ,color);
    if (!TxT) {
        return ;
    }
    SDL_Surface* tabd = SDL_ConvertSurfaceFormat(TxT,c->surface->format->format,0) ;
    SDL_FreeSurface(TxT);
    if (!tabd) {
        return ;
    }
    SDL_Rect dst = {cx, cy , tabd->w,tabd->h};
    SDL_LockSurface(tabd);
    SDL_BlitSurface(tabd,nullptr,c->surface,&dst);
    SDL_UnlockSurface(c->surface);
    SDL_FreeSurface(tabd);
    updateTexure(idx);
}


void saveEdit(SDL_Renderer * renderer , int idx) {
    (void)renderer;
    updateTexure(idx);
}

int  SavetoFile(int idx , const char* filepath ) {
    if (idx < 0 || idx >= counter || !filepath) {
        return 0;
    }
    Custome* c = &costums [idx] ;
    if (!c -> surface) {
        return 0;
    }
    if (SDL_SaveBMP(c->surface, filepath) !=  0) {
        SDL_Log("SaveBMP failed: %s", SDL_GetError());
        return 0;
    }
    return 1 ;
}
