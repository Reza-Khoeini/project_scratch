#include "UI.h"
#include "Pen.h"
#include "Costumes.h"
#include "UICallback.h"
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>

using namespace std ;
#define MaxButton   35


typedef struct  {
    // float x , y ;
    // float widgh , height ;
    //  به صورت زیر اصلاح می شود
    SDL_Rect rect;
    const char* id ; //  شناسه دکمه ها
    const char* text ;
    bool visible ;

} UIButtons;



static UIButtons buttons[MaxButton] ;
static int countOfButtons = 0 ;

static int panelOpen = 0 ;
static int ww = 800 ;
static int wh = 600 ;

static SDL_Renderer * Renderer = nullptr ;


//  رسم متن روی آیکون
static TTF_Font * font = nullptr ;
static bool fontOk = false ;

// costums

static int costTool = coNone ;
static int costselected = -1 ;

static void uiADDBUTTON(int x , int y , int w ,int h ,const char* id , const char* text  ) {
    if (countOfButtons >= MaxButton) {
        return ;
    }
    buttons[countOfButtons].rect.x = x;
    buttons[countOfButtons].rect.y = y;
    buttons[countOfButtons].rect.w = w;
    buttons[countOfButtons].rect.h = h;
    buttons[countOfButtons].id = id;
    buttons[countOfButtons].text = text;
    buttons[countOfButtons].visible = true;
    countOfButtons++;
}


void uiInitCostButt() {

    int bX = 20 ;
    int bY = 80 ;
    int  bw = 120 ;
    int  bh = 28 ;
    int gap = 8 ;
    int i = 0 ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coUpload","Uplad img") ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coFlipH","Flip H") ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coFlipV","Flip V") ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coResizeUP","Resize ++") ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coResizeDN","Resize --") ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coSetPos","Set Pos") ;
    //  ابزار های نقاشی
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coPen","tool: pen") ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coEraser","tool: eraser") ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coFill","tool: fill") ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coText","tool: text") ;
    uiADDBUTTON(bX , bY + (i++)*(bh + gap ),bw , bh , "coLine","tool: line") ;
}

void addButton(int x, int y, int w, int h, const char *id, const char *text) {
    if (countOfButtons >= MaxButton) {
        return;
    }
    buttons[countOfButtons].rect.x = x;
    buttons[countOfButtons].rect.y = y;
    buttons[countOfButtons].rect.w = w;
    buttons[countOfButtons].rect.h = h;
    buttons[countOfButtons].id = id;
    buttons[countOfButtons].text =text;
    buttons[countOfButtons].visible =true;

    countOfButtons++;
}
//  رسم یا همان ن.شتن روی آیکون
static  void disignTex(SDL_Renderer * renderer , const char *  tex , int x, int y) {
    if (!font || !tex) {
        return;
    }
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, tex, color);
    if (!surface) {
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        return;
    }
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}

// حالا اینجا برای رسم آیکون اقدام می کنیم

static void drawingButton(SDL_Renderer * renderer , const UIButtons * button ) {
    if (!button || !button -> visible) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &button -> rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &button -> rect);
    if (fontOk && button -> text) {
        int dw = 0  ;
        int dh = 0  ;
        TTF_SizeUTF8( font , button -> text, &dw, &dh );
        int dx = button -> rect.x + (button->rect.w - dw )/ 2;
        int dy = button -> rect.y + (button->rect.h - dh) / 2;
        disignTex(renderer, button -> text, dx, dy);
    }
}

void haveUI(SDL_Renderer *renderer, int w, int h) {
    Renderer = renderer;
    ww = w ;
    wh = h ;
    countOfButtons = 0;
    panelOpen = 0;


    if (TTF_Init() == 0) {
        font = TTF_OpenFont("fonts/arial.ttf" , 30);
        if (font ) {
            fontOk = true;
        }
        else {
            fontOk = false;
            SDL_Log("Could not load font at '../../../fonts/arial.ttf'");
        }
    }
    else {
        fontOk = false;
        SDL_Log("Could not load font at '../../../fonts/arial.ttf'", TTF_GetError());
    }
    // ساخت دکمه  add
    addButton(20, 20, 60, 30,  "addExtension", "ADD") ;

    // دکمه هایی برای پنل   pen
    addButton(0, 0, 120, 30,  "erase all", "clear ALL") ;
    addButton(0, 0, 120, 30,  "stamp", "Stamp") ;
    addButton(0, 0, 120, 30,  "penDown", "penDown") ;
    addButton(0, 0, 120, 30,  "penUp", "penUpp") ;
     addButton(0, 0, 120, 30,  "setColor", "SetColor") ;
    countOfButtons =0 ;
    uiInitCostButt();
}

void Shutdown() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
    Renderer= nullptr;
    countOfButtons = 0;
}

//  تعیین اینکه آیا اینها درون

static  int identifyInrect(int x, int y, SDL_Rect  * r ) {
    return ((x >= r->x  && x <= r->x  + r->w ) && (y >= r->y  && y <= r->y + r->h)) ;
}

static void Panel(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 160);
    SDL_Rect fulling = {0,0,ww , wh };
    SDL_RenderFillRect(renderer, &fulling);

    // white panel
    SDL_Rect M = { ww/2 - 150 , wh/2 - 150 , 300 , 300} ;
    SDL_SetRenderDrawColor(renderer,240,240,240,255);
    SDL_RenderFillRect(renderer, &M);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderDrawRect(renderer, &M);



    int X1 =M.x  + 50 ;
    int Y1 =M.y  + 30 ;
    int couner = 1 ;
    for (int i = 0 ; i < 5 ; i++) {
        if (couner >= countOfButtons ) {
            break;
        }

        UIButtons * b = &buttons[couner ] ;
        b -> rect.x = X1 ;
        b -> rect.y = Y1 ;
        b -> rect.w = 200 ;
        b -> rect.h = 30 ;
        drawingButton(renderer, b);
        couner++ ;
    }
}


void handleUIClick(int mouseX, int mouseY) {
    if (!panelOpen) {
        if ((countOfButtons > 0)&& identifyInrect(mouseX , mouseY , &buttons[0].rect)) {
            panelOpen = true ;
            return;
        }
    }
    else {
        int counter = 1 ;
        for (int i = 0 ; (i  < countOfButtons ) ; i++ ) {
            UIButtons * b = &buttons[counter] ;
            if (!b -> visible) {
                continue;
            }
            if (identifyInrect(mouseX , mouseY , &b -> rect)) {

                if (strcmp(b->id , "coUpload") == 0) {
                    char path[512];
                    printf("Enter path to load :") ;
                    if (fgets(path, 512, stdin)) {
                        size_t L = strlen(path);
                        if (L > 0 && path[L-1] == '\n') {
                            path[L-1] = 0 ;
                        }
                        int idx = ADD_image(Renderer,path,path,0);
                        if (idx >= 0) {
                            Selct(idx);
                            printf("Loaded as index %d\n",idx);
                        }
                        else {
                            printf("Failed to load %s\n",path);
                        }
                    }
                }

                else if (strcmp(b->id , "coFlipH") == 0) {
                    int sell =  getSelect() ;
                    if (sell >= 0) {
                        flipHorizontal(sell) ;
                    }
                }
                    else if (strcmp(b->id , "coFlipV") == 0) {
                        int sell =  getSelect() ;
                        if (sell >= 0) {
                            flipHorizontal(sell) ;
                        }
                }
                    else if (strcmp(b->id , "coResizeUP") == 0) {
                        int sell =  getSelect() ;
                        if (sell >= 0) {
                            int w,h ;
                            costgetSIZE(sell ,  &w , &h ) ;
                            cosSetSize(sell , w + 20 , h + 20) ;
                        }
                    }
                    else if (strcmp(b->id , "coResizeDN") == 0) {
                        int sell =  getSelect() ;
                        if (sell >= 0) {
                            int w,h ;
                            costgetSIZE(sell ,  &w , &h ) ;
                            cosSetSize(sell , w - 20 > 4 ?  w-20 : 4  , h - 20 > 4 ?  h-20 : 4  ) ;
                        }
                    }
                else if (strcmp(b->id , "coSetPos") == 0) {
                    //  وارد کردن مختصات توسط کاربر
                    int sell =  getSelect() ;
                    if (sell >= 0) {
                        int nx , ny ;
                        printf("Enter new x ,y for selected costum : ") ;
                        if (scanf("%d %d", &nx , &ny) == 2) {
                            int c ;
                            while ((c = getchar()) != '\n' && c != EOF) {
                                costSetPosi(sell, nx , ny) ;
                            }
                        }
                        else {
                            int c ;
                            while ((c = getchar()) != '\n' && c != EOF) {
                                printf("invalid input\n") ;
                            }
                        }
                    }
                }

                else if (strcmp(b->id, "cost_tool_pen") == 0) {
                    uiCostumSET(coPen);
                }
                else if (strcmp(b->id, "cost_tool_eraser") == 0) {
                    uiCostumSET(coEraser);
                }
                else if (strcmp(b->id, "cost_tool_fill") == 0) {
                    uiCostumSET(coFill);
                }
                else if (strcmp(b->id, "cost_tool_text") == 0) {
                    uiCostumSET(coText);
                }
                else if (strcmp(b->id, "cost_tool_line") == 0) {
                    uiCostumSET(coLine);
                }

                else if (strcmp(b -> id , "erase all") == 0) {
                    EraseALL(Renderer) ;
                }
                else if (strcmp(b -> id , "stamp") == 0) {
                    onStampXY(Renderer, mouseX, mouseY) ;
                }
                else if (strcmp(b -> id , "penUp") == 0) {
                    oPenUp() ;
                }
                else if (strcmp(b -> id , "penDown") == 0) {
                    oPenDown() ;
                }
                else if (strcmp(b -> id , "setColor") == 0) {
                    SDL_Log("setColor  .... !");
                }
                else {
                }
                panelOpen = false ;
                return ;
            }
        }
        //  اکر خارج از آیگون بود بستته شود
        SDL_Rect M = {ww/2 -150 , wh/2 -150 , 300 , 300 };
        if ((!identifyInrect( mouseX, mouseY , &M )) ) {
                panelOpen = false ;
        }
    }
}

int uiCostumGET() {
    return costTool ;
}
void uiCostumSET(int tool) {
    costTool = tool ;
}
    int uiIsOk() {
    return panelOpen ;
}