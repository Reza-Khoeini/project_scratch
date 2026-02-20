#ifndef PROJECT_SCRATCH_KHOEINI3_H
#define PROJECT_SCRATCH_KHOEINI3_H
#include<bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#ifndef max_block_of_looks
#define max_block_of_looks 512
#endif
#ifndef max_sprites_of_looks
#define max_sprites_of_looks 16
#endif
#ifndef max_costumes_of_looks
#define max_costumes_of_looks 32
#endif
#ifndef max_backdrops_of_looks
#define max_backdrops_of_looks 32
#endif
#ifndef max_threads_of_looks
#define max_threads_of_looks 64
#endif
#ifndef max_text_of_looks
#define max_text_of_looks 128
#endif
#ifndef max_name_of_looks
#define max_name_of_looks 64
#endif
#ifndef max_stage_width_of_looks
#define max_stage_width_of_looks 480
#endif
#ifndef max_stage_hight_of_looks
#define max_stage_hight_of_looks 360
#endif

static inline double looks_clamp_f(float v,float min,float max) {
    return(v<min)?min:(v>max)?max:v;
}
static inline int looks_clamp_i(float v,float min,float max) {
    return(v<min)?min:(v>max)?max:v;
}
static inline double looks_(double v) {
    return (v<0.0)?-v:v;
}
static inline bool is_cursor_in_rect(int x,int y,const SDL_Rect& r) {
    return (x>=r.x&&x<r.x+r.w&&y>=r.y&&y<r.y+r.h);
}
static inline SDL_Color looks_rgb(uint8_t r,uint8_t g,uint8_t b,uint8_t a=255) {
    SDL_Color ran;
    ran.r=r;
    ran.g=g;
    ran.b=b;
    ran.a=a;
    return ran;
}
static inline void set_draw_color(SDL_Renderer* ren,SDL_Color ran) {
    SDL_SetRenderDrawColor(ren,ran.r,ran.g,ran.b,ran.a);
}
static inline uint8_t font_row_text_h(char c,int row) {
    if (row<0||row>6) {
        return 0;
    }
    if(c>='a'&&h<='z') {
        c=(char)(c-'a'+'A');
    }
    #define bl(r0,r1,r2,r3,r4,r5,r6) {static const uint8_t r[7]={r0,r1,r2,r3,r4,r5,r6};return r[row];}
    switch (c){
        case ' ':bl(0,0,0,0,0,0,0);
        case '!':bl(0b00100,0b00100,0b00100,0b00100,0b00100,0,0b00100);
        case '.':bl(0,0,0,0,0,0b00110,0b00110);
        case ',':bl(0,0,0,0,0b00110,0b00110,0b00100);
        case ':':bl(0,0b00110,0b00110,0,0b00110,0b00110,0);
        case ';':bl(0,0b00110,0b00110,0,0b00110,0b00110,0b00100);
        case '-':bl(0,0,0,0b11111,0,0,0);
        case '+':bl(0,0b00100,0b00100,0b11111,0b00100,0b00100,0);
        case '/':bl(0b00001,0b00010,0b00100,0b01000,0b10000,0,0);
        case '\\':bl(0b10000,0b01000,0b00100,0b00010,0b00001,0,0);
        case '_':bl(0,0,0,0,0,0,0b11111);
        case '"':bl(0b01010,0b01010,0b01010,0,0,0,0);
        case '\'':bl(0b00100,0b00100,0,0,0,0,0);
        case '%':bl(0b11001,0b11010,0b00100,0b01011,0b10011,0,0);
        case '?':bl(0b01110,0b10001,0b00010,0b00100,0b00100,0,0b00100);
        case '<':bl(0b00010,0b00100,0b01000,0b10000,0b01000,0b00100,0b00010);
        case '>':bl(0b01000,0b00100,0b00010,0b00001,0b00010,0b00100,0b01000);
        case '=':bl(0,0b11111,0,0b11111,0,0,0);
        case '(':bl(0b00010,0b00100,0b01000,0b01000,0b01000,0b00100,0b00010);
        case ')':bl(0b01000,0b00100,0b00010,0b00010,0b00010,0b00100,0b01000);
        case '[':bl(0b01110,0b01000,0b01000,0b01000,0b01000,0b01000,0b01110);
        case ']':bl(0b01110,0b00010,0b00010,0b00010,0b00010,0b00010,0b01110);
        case '#':bl(0b01010,0b11111,0b01010,0b11111,0b01010,0,0);
        case '$':bl(0b00100,0b01111,0b10100,0b01110,0b00101,0b11110,0b00100);
        case '&':bl(0b01100,0b10010,0b10100,0b01000,0b10101,0b10010,0b01101);
        case '@':bl(0b01110,0b10001,0b10111,0b10101,0b10111,0b10000,0b01110);
        case '0':bl(0b01110,0b10001,0b10011,0b10101,0b11001,0b10001,0b01110);
        case '1':bl(0b00100,0b01100,0b00100,0b00100,0b00100,0b00100,0b01110);
        case '2':bl(0b01110,0b10001,0b00001,0b00010,0b00100,0b01000,0b11111);
        case '3':bl(0b11110,0b00001,0b00001,0b01110,0b00001,0b00001,0b11110);
        case '4':bl(0b00010,0b00110,0b01010,0b10010,0b11111,0b00010,0b00010);
        case '5':bl(0b11111,0b10000,0b11110,0b00001,0b00001,0b10001,0b01110);
        case '6':bl(0b00110,0b01000,0b10000,0b11110,0b10001,0b10001,0b01110);
        case '7':bl(0b11111,0b00001,0b00010,0b00100,0b01000,0b01000,0b01000);
        case '8':bl(0b01110,0b10001,0b10001,0b01110,0b10001,0b10001,0b01110);
        case '9':bl(0b01110,0b10001,0b10001,0b01111,0b00001,0b00010,0b01100);
        case 'A':bl(0b01110,0b10001,0b10001,0b11111,0b10001,0b10001,0b10001);
        case 'B':bl(0b11110,0b10001,0b10001,0b11110,0b10001,0b10001,0b11110);
        case 'C':bl(0b01111,0b10000,0b10000,0b10000,0b10000,0b10000,0b01111);
        case 'D':bl(0b11110,0b10001,0b10001,0b10001,0b10001,0b10001,0b11110);
        case 'E':bl(0b11111,0b10000,0b10000,0b11110,0b10000,0b10000,0b11111);
        case 'F':bl(0b11111,0b10000,0b10000,0b11110,0b10000,0b10000,0b10000);
        case 'G':bl(0b01111,0b10000,0b10000,0b10011,0b10001,0b10001,0b01111);
        case 'H':bl(0b10001,0b10001,0b10001,0b11111,0b10001,0b10001,0b10001);
        case 'I':bl(0b01110,0b00100,0b00100,0b00100,0b00100,0b00100,0b01110);
        case 'J':bl(0b00001,0b00001,0b00001,0b00001,0b10001,0b10001,0b01110);
        case 'K':bl(0b10001,0b10010,0b10100,0b11000,0b10100,0b10010,0b10001);
        case 'L':bl(0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b11111);
        case 'M':bl(0b10001,0b11011,0b10101,0b10101,0b10001,0b10001,0b10001);
        case 'N':bl(0b10001,0b11001,0b10101,0b10011,0b10001,0b10001,0b10001);
        case 'O':bl(0b01110,0b10001,0b10001,0b10001,0b10001,0b10001,0b01110);
        case 'P':bl(0b11110,0b10001,0b10001,0b11110,0b10000,0b10000,0b10000);
        case 'Q':bl(0b01110,0b10001,0b10001,0b10001,0b10101,0b10010,0b01101);
        case 'R':bl(0b11110,0b10001,0b10001,0b11110,0b10100,0b10010,0b10001);
        case 'S':bl(0b01111,0b10000,0b10000,0b01110,0b00001,0b00001,0b11110);
        case 'T':bl(0b11111,0b00100,0b00100,0b00100,0b00100,0b00100,0b00100);
        case 'U':bl(0b10001,0b10001,0b10001,0b10001,0b10001,0b10001,0b01110);
        case 'V':bl(0b10001,0b10001,0b10001,0b10001,0b10001,0b01010,0b00100);
        case 'W':bl(0b10001,0b10001,0b10001,0b10101,0b10101,0b10101,0b01010);
        case 'X':bl(0b10001,0b10001,0b01010,0b00100,0b01010,0b10001,0b10001);
        case 'Y':bl(0b10001,0b10001,0b01010,0b00100,0b00100,0b00100,0b00100);
        case 'Z':bl(0b11111,0b00001,0b00010,0b00100,0b01000,0b10000,0b11111);
        default: bl(0b01110,0b10001,0b00010,0b00100,0b00100,0,0b00100);
    }
    #undef bl
}
static inline void draw_text_for_looks(SDL_Renderer* ren,int x,int y,const char* s,int scale,SDL_Color ran) {
    if (!s) {
        return;
    }
    set_draw_color(ren,ran);
    const int sex=(scale<=0)?1:scale;
    const int sey=sex;
    int px=x;
    for (size_t i=0;s[i];i++) {
        char c=s[i];
        if (c=='\n') {
            px=x;
            y+=8*sey;
            continue;
        }
        for (int row=0;row<7;row++) {
            uint8_t bite=font_row_text_h(c,row);
            for (int col=0;col<5;col++) {
                if (bite&(1u<<(4-col))) {
                    SDL_Rect dst={px+col*sex,y+row+sey,sex,sey};
                    SDL_RenderFillRect(ren,&dst);
                }
            }
        }
        px+=6*sex;
    }
}
static inline void draw_filled_rounded_rect_for_looks(SDL_Renderer* ren,const SDL_Rect &r,int rad,SDL_Color fill) {
  set_draw_color(ren,fill);
    if (rad<=0) {
        SDL_RenderFillRect(ren,&r);
        return;
    }
    int ra=rad;
    if (ra*2>r.w) {
        ra=r.w/2;
    }
    if (ra*2>r.h) {
        ra=r.h/2;
    }
    SDL_Rect mid{r.x+ra,r.y,r.w-2*ra,r.h};
    SDL_RenderFillRect(ren,&mid);
    SDL_Rect left{r.x,r.y+ra,ra,r.h-2*ra};
    SDL_RenderFillRect(ren,&left);
    SDL_Rect right{r.x+r.w-ra,r.y+ra,ra,r.h-2*ra};
    SDL_RenderFillRect(ren,&right);
    for (int dy=-ra;dy<=ra;dy++) {
        for (int dx=-rad;dx<=rad;dx++) {
            if (dx*dx+dy*dy<=ra*ra) {
                SDL_RenderDrawPoint(ren,r.x+dx,r.y+ra+dy);
                SDL_RenderDrawPoint(ren,r.x+r.w-ra-1+dx,r.y+ra+dy);
                SDL_RenderDrawPoint(ren,r.x+ra+dx,r.y+r.h-ra-1+dy);
                SDL_RenderDrawPoint(ren,r.x+r.w-ra-1+dx,r.y+r.h-ra-1+dy);
            }
        }
    }
}
static  inline void draw_rounded_rect_outline_for_looks(SDL_Renderer* ren,const SDL_Rect &r,int rad,SDL_Color ran) {
    set_draw_color(ren,ran);
    if (rad<=0) {
        SDL_RenderDrawRect(ren,&r);
        return;
    }
    int ra=rad;
    if (ra*2>r.w) {
        ra=r.w/2;
    }
    if (ra*2>r.h) {
        ra=r.h/2;
    }
    SDL_RenderDrawLine(ren,r.x+ra,r.y,r.x+r.w-ra-1,r.y);
    SDL_RenderDrawLine(ren,r.x+ra,r.y+r.h-1,r.x+r.w-ra-1,r.y+r.h-1);
    SDL_RenderDrawLine(ren,r.x,r.y+ra,r.x,r.y+r.h-ra-1);
    SDL_RenderDrawLine(ren,r.x+r.w-1,r.y+ra,r.x+r.w-1,r.y+r.h-ra-1);
    for (int an=0;an<=90;an++) {
        float a=an*3.14159265f/180.0f;
        int dx=(int)std::round(cos(a)*ra);
        int dy=(int)std::round(sin(a)*ra);
        SDL_RenderDrawPoint(ren,r.x+ra-dx,r.y+ra-dy);
        SDL_RenderDrawPoint(ren,r.x+r.w-ra-1+dx,r.y+ra-dy);
        SDL_RenderDrawPoint(ren,r.x+ra-dx,r.y+r.h-ra-1+dy);
        SDL_RenderDrawPoint(ren,r.x+r.w-ra-1+dx,r.y+r.h-ra-1+dy);
    }
}
struct looks_costume {
    char name[max_name_of_looks];
    SDL_Texture* tex;;
    int w,h;
};
struct looks_backdrop {
    char name[max_name_of_looks];
    SDL_Texture* tex;
    int w,h;
};
enum bubble_type_looks :int{bubble_none_looks=0,bubble_say_looks=1,bubble_think=2};
struct sprite_looks {
    char name[max_name_of_looks];
    float x;
    float y;
    bool visible;
    float size_per;
    float color_effect;
    uint8_t alph;
    bubble_type_looks bubble_type;
    char bubble_text[max_text_of_looks];
    uint32_t bubble_exp_ms;
    looks_costume costume[max_costumes_of_looks];
    int costume_count;
    int costume_index;
};
struct looks_stage {
    looks_backdrop backdrop[max_backdrops_of_looks];
    int backdrop_count;
    int backdrop_index;
    bool watch_costume;
    bool watch_backdrop;
    bool watch_size;
    int watch_x;
    int watch_y;
};
enum block_type_looks {
    block_none_looks=0,
    block_say_looks=1,
    block_say_secs_looks=2,
    block_think_looks=3,
    block_think_secs_looks=4,
    block_swich_costume_looks=5,
    block_next_costume_looks=6,
    block_swich_backdrop_looks=7,
    block_next_backdrop_looks=8,
    block_change_size_looks=9,
    block_set_size_looks=10,
    block_change_color_effect_looks=11,
    block_set_color_effect_looks=12,
    block_clear_color_effect_looks=13,
    block_show_looks=14,
    block_hide_looks=15,
    block_go_front_l_looks=16,
    block_go_back_l_looks=17,
    block_go_forward_l_looks=18,
    block_go_backward_l_looks=19,
    block_report_costume_looks=20,
    block_report_backdrop_looks=21,
    block_report_size_looks=22,
};
static inline bool block_is_reporter(block_type_looks t) {
    return (t==block_report_costume_looks||t==block_report_backdrop_looks||t==block_report_size_looks);
}
static inline bool block_is_stack(block_type_looks t) {
    return (!block_is_reporter(t));
}
enum field_type_looks {field_none_looks=0,field_text_looks=1,field_number_looks=2,field_dropdown=3};




#endif