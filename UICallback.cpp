#include "UICallback.h"
#include "Pen.h"

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

