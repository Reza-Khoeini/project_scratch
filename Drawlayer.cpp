#include  "Drawlayer.h"



// SDL_Renderer * texture ; not true...


// just for this file

inline static SDL_Texture *  drawTexture = nullptr ;
static int  wLayer = 0 ;
static int  hLayer = 0 ;





// produce a layer
bool initDrawLayer(SDL_Renderer * renderer , int w , int h) {
    if (!renderer ||w <= 0 || h <= 0) {
        return false;
    }
    if (drawTexture) {
        SDL_DestroyTexture(drawTexture);
        drawTexture = nullptr ;
    }
    drawTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,w,h);

    if (!drawTexture) {
        return false ;
    }
    // alfa building ( رسم صفحه شفاف)
    SDL_SetTextureBlendMode(drawTexture, SDL_BLENDMODE_BLEND);

    SDL_Texture* prev = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, drawTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, prev);

    return true;
}

// FOR SHOW THE LAYER(show the disigns)
void drawLayerPresent(SDL_Renderer* renderer) {
    if (!renderer || !drawTexture) {
        return ;
    }
    SDL_RenderCopy(renderer, drawTexture, nullptr, nullptr);

}



void clearDrawLayer(SDL_Renderer* renderer ) {
     if (!renderer || !drawTexture) { //  اگه هیچ کدوم نشد ...
         return;
     }
    SDL_Texture *saveTar = SDL_GetRenderTarget(renderer) ;
    Uint8 r,g,b,a ;
    SDL_GetRenderDrawColor( renderer , &r, &g, &b, &a ) ;

    SDL_SetRenderTarget(renderer, drawTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //  برای شفافیت
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor( renderer , r, g, b, a ) ;
    SDL_SetRenderTarget(renderer, saveTar);
}

void drawLineOneLayer(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, SDL_Color color, int Size) {
    if (!renderer || !drawTexture) {
        return;
    }
    if (Size <= 1) {
        Size = 1 ;
    }

    SDL_Texture* prev = SDL_GetRenderTarget(renderer) ;
    // Arasteh Code
    SDL_SetRenderTarget(renderer, drawTexture); // draw on tex
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND );
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int i=0 ; i <Size ; i++) {
        SDL_RenderDrawLine( renderer, x1, y1 + i, x2,y2+i) ;
    }
    SDL_SetRenderTarget(renderer, prev);

}

// copy on tex
void stampOneLayer(SDL_Renderer *renderer, SDL_Texture *spriteText, const SDL_Rect *dst) {
    // اگر هیج کدام درست نشد هیچ کاری نکن...
     if (!renderer || !drawTexture || !spriteText || !dst) {
         return;
     }

    SDL_Texture *prev = SDL_GetRenderTarget(renderer) ;
    SDL_SetRenderTarget(renderer, drawTexture);
    SDL_SetTextureBlendMode(drawTexture, SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(renderer, spriteText, nullptr, dst);
    SDL_SetRenderTarget(renderer, prev);
}

void freeDrawLayer() {
    if (drawTexture) {
        SDL_DestroyTexture(drawTexture);
        drawTexture = nullptr;
    }
}

