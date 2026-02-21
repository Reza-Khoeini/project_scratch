#include "ColorUtil.h"


SDL_Color changeColorSlow() {
    static int r = 255 ;
    static int g = 0 ;
    static int b = 0 ;

    static int stage  = 0 ;

    int speed = 3 ;

    switch (stage) {
        case 0 : {
            g+= speed;
            if (g >= 255) {
                g = 255 ;
                stage = 1 ;
            }
            break;
        }
        case 1 : {
            r-= speed;
            if (r <= 0) {
                r = 0 ;
                stage = 2 ;
            }
            break;
        }
        case 2 : {
            b+= speed;
            if (b >= 255) {
                b = 255 ;
                stage = 3 ;
            }
            break;
        }
        case 3 : {
            g-= speed;
            if (g <= 0) {
                g = 0 ;
                stage = 4 ;
            }
            break;
        }
        case 4 : {
            r+= speed;
            if (r >= 255) {
                r = 255 ;
                stage = 5 ;
            }
            break;
        }
        case 5 : {
            b-= speed;
            if (b <= 0) {
                b = 0  ;
                stage = 0 ;
            }
            break;
        }
            default: {
            stage = 0 ;
            break;
        }
    }
    //  جلوگیری از  overflow
     r= (r < 0) ? 0 :(r > 255) ? 255 : r ;
    g= (g < 0) ? 0 : (g > 255) ? 255 : g ;
    b= (b < 0) ? 0 : (b > 255) ? 255 : b ;
    SDL_Color color = {(Uint8)r, (Uint8)g, (Uint8)b  , 255 };
    return color ;
}