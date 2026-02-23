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

#include "khoeini2.h"
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
#ifndef snap_dist_looks
#define snap_dist_looks
#endif

static inline double looks_clamp_f(float v,float min,float max) {
    return(v<min)?min:(v>max)?max:v;
}
static inline int looks_clamp_i(float v,float min,float max) {
    return(v<min)?min:(v>max)?max:v;
}
static inline double looks_absf(double v) {
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
    if(c>='a'&& c<='z') {
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
enum field_type_looks {field_none_looks=0,field_text_looks=1,field_number_looks=2,field_dropdown_looks=3};
struct field_looks {
    field_type_looks type;
    SDL_Rect rect;
    char text[max_text_of_looks];
    float number;
    int dropdown_index;
};
struct block_looks {
    bool use;
    int id;
    block_type_looks type;
    float x;
    float y;
    float w;
    float h;
    int next;
    int prev;
    field_looks field[2];
    int field_count;
};
struct thread_looks {
  bool ali;
    int pc;
    uint32_t wait_until;
};
struct  palet_item_looks{
    block_type_looks type;
    SDL_Rect rect;
};
struct  app_looks{
    SDL_Renderer* ren;
    int win_h;
    int win_w;
    SDL_Rect top_bar;
    SDL_Rect palet;
    SDL_Rect workspace;
    SDL_Rect stage_p;
    SDL_Color back_ground;
    SDL_Color panel;
    SDL_Color panel_border;
    SDL_Color looks_color;
    SDL_Color looks_color_dark;
    SDL_Color looks_outline;
    SDL_Color text;
    SDL_Color input_bg;
    SDL_Color input_border;
    SDL_Color highlight;
    palet_item_looks palette_item[64];
    int palette_count;
    int palette_scroll_y;
    block_looks block[max_block_of_looks];
    int block_count;
    bool dragging;
    int drag_root;
    int drag_from_pallete;
    float drag_ox;
    float drag_oy;
    bool text_input_on;
    int edit_block;
    int edit_field;
    bool is_num_edit;
    bool dropdown_open;
    int dropdown_block;
    int dropdown_field;
    SDL_Rect button_run;
    SDL_Rect button_stop;
    bool running;
    thread_looks thread[max_threads_of_looks];
    int thread_count;
    looks_stage stage;
    sprite_looks sprite[max_sprites_of_looks];
    int sprite_count;
    int active_sprite;
    int sprite_order[max_sprites_of_looks];
    int mouse_x;
    int mouse_y;
    int mouse_down;
};
static inline SDL_Texture* create_checker_texture_looks(SDL_Renderer* ren,int w,int h,SDL_Color a,SDL_Color b) {
    SDL_Surface * sur=SDL_CreateRGBSurfaceWithFormat(0,w,h,32,SDL_PIXELFORMAT_RGBA32);
    if (!sur) {
        return nullptr;
    }
    uint32_t* px=(uint32_t*)sur->pixels;
    const uint32_t ca=SDL_MapRGBA(sur->format,a.r,a.g,a.b,a.a);
    const uint32_t cb=SDL_MapRGBA(sur->format,b.r,b.g,b.b,b.a);
    for (int y=0;y<h;y++) {
        for (int x=0;x<w;x++) {
            int v=((x/16)+(y/16))&1;
            px[y*(sur->pitch/4)+x]=v?ca:cb;
        }
    }
    SDL_Texture* text=SDL_CreateTextureFromSurface(ren,sur);
    SDL_FreeSurface(sur);
    return text;
}
static inline SDL_Texture* create_shit_face_sprite_texture_looks(SDL_Renderer* ren,int w, int h) {
    SDL_Surface* sur=SDL_CreateRGBSurfaceWithFormat(0,w,h,32,SDL_PIXELFORMAT_RGBA32);
if (!sur) {
    return nullptr;
}
SDL_FillRect(sur,nullptr,SDL_MapRGBA(sur->format,0,0,0,0));
uint32_t* px=(uint32_t*)sur->pixels;
const int cx=w/2;
const int cy=h/2;
const int r=(w<h?w:h)/2-2;
const uint32_t col=SDL_MapRGBA(sur->format,255,200,50,255);
    for (int y=0;y<h;y++) {
        for (int x=0;x<w;x++) {
            int dx=x-cx;
            int dy=y-cy;
            if (dx*dx+dy*dy<=r*r) {
                px[y*(sur->pitch/4)+x]=col;
            }
        }
    }
    SDL_Texture* text=SDL_CreateTextureFromSurface(ren,sur);
    SDL_FreeSurface(sur);
    return text;
}
static inline void safe_str_cpy_looks(char* dst,size_t dst_size,const char* src) {
    if (!dst||dst_size==0) {
        return;
    }
    if (!src) {
        dst[0]='\0';
        return;
    }
    snprintf(dst,dst_size,"%s",src);
}
static inline void reset_stage_looks(app_looks* app) {
    if (!app) return;
    for (int i=0;i<app->stage.backdrop_count;i++) {
        if (app->stage.backdrop[i].tex) {
            SDL_DestroyTexture(app->stage.backdrop[i].tex);
        }
        app->stage.backdrop[i].tex=nullptr;
    }
    app->stage.backdrop_count=0;
    app->stage.backdrop_index=0;
    app->stage.watch_backdrop=false;
    app->stage.watch_costume=false;
    app->stage.watch_size=false;
    app->stage.watch_x=10;
    app->stage.watch_y=10;
}
static inline void reset_sprites_looks(app_looks* app) {
    if (!app) return;
    for (int s=0;s<app->sprite_count;s++) {
        sprite_looks& sp=app->sprite[s];
        for (int c=0;c<sp.costume_count;c++) {
            if (sp.costume[c].tex) {
                SDL_DestroyTexture(sp.costume[c].tex);
            }
            sp.costume[c].tex=nullptr;
        }
        sp.costume_count=0;
    }
    app->sprite_count=0;
    app->active_sprite=0;
}
static inline int add_sprites_looks(app_looks* app,const char* name) {
    if (!app) return -1;
    if (app->sprite_count>=max_sprites_of_looks) return -1;
    int idx=app->sprite_count++;
    sprite_looks& sp=app->sprite[idx];
    memset(&sp,0,sizeof(sprite_looks));
    safe_str_cpy_looks(sp.name,sizeof(sp.name),name?name:"Sprite");
    sp.x=0.0f;
    sp.y=0.0f;
    sp.visible=true;
    sp.size_per=100.0f;
    sp.color_effect=0.0f;
    sp.alph=255;
    sp.bubble_type=bubble_none_looks;
    sp.bubble_text[0]='\0';
    sp.bubble_exp_ms=0;
    sp.costume_count=0;
    sp.costume_index=0;
    for (int i=app->sprite_count-1;i>0;i--) {
        app->sprite_order[i]=app->sprite_order[i-1];
    }
    app->sprite_order[0]=idx;
    return idx;
}
static inline int add_costume_to_sprite_looks(app_looks* app,int sprite_index,const char* costume_name,SDL_Texture* tex,int w,int h) {
    if (!app) return -1;
    if (sprite_index<0||sprite_index>=app->sprite_count) return -1;
    sprite_looks& sp=app->sprite[sprite_index];
    if (sp.costume_count>=max_sprites_of_looks) return -1;
    int ci=sp.costume_count++;
    safe_str_cpy_looks(sp.costume[ci].name,sizeof(sp.costume[ci].name),costume_name?costume_name:"costume");
    sp.costume[ci].tex=tex;
    sp.costume[ci].w=w;
    sp.costume[ci].h=h;
    return ci;
}
static inline SDL_Texture* load_texture_bmp_looks(app_looks* app,const char* filepath,int* out_w,int* out_h) {
    if (!app||!app->ren||!filepath) return nullptr;
    SDL_Surface* surf=SDL_LoadBMP(filepath);
    if (!surf) {
        return nullptr;
    }
    if (out_w) {
        *out_w=surf->w;
    }
    if (out_h) {
        *out_h=surf->h;
    }
    SDL_SetColorKey(surf,SDL_TRUE,SDL_MapRGB(surf->format,255,0,255));
    SDL_Texture* tex=SDL_CreateTextureFromSurface(app->ren,surf);
    SDL_FreeSurface(surf);
    if (tex) {
        SDL_SetTextureBlendMode(tex,SDL_BLENDMODE_BLEND);
    }
    return tex;
}
static inline int add_costume_bmp_looks(app_looks* app,int sprite_index,const char* name,const char *bmp_path) {
    int w=0,h=0;
    SDL_Texture* tex=load_texture_bmp_looks(app,bmp_path,&w,&h);
    if (!tex) {
        return -1 ;
    }
    return add_costume_to_sprite_looks(app,sprite_index,name,tex,w,h);
}
static inline int add_backdrop_looks(app_looks* app,const char* name,SDL_Texture*tex,int w,int h) {
    if (!app) return -1;
    if (app->stage.backdrop_count>=max_backdrops_of_looks) return -1;
    int bi=app->stage.backdrop_count++;
    safe_str_cpy_looks(app->stage.backdrop[bi].name,sizeof(app->stage.backdrop[bi].name),name?name:"backdrop");
    app->stage.backdrop[bi].tex=tex;
    app->stage.backdrop[bi].w=w;
    app->stage.backdrop[bi].h=h;
    return bi;
}
static inline int add_backdrop_bmp_looks(app_looks* app,const char* name,const char* bmp_path) {
    int w=0,h=0;
    SDL_Texture* tex=load_texture_bmp_looks(app,bmp_path,&w,&h);
    if (!tex) {
        return -1;
    }
    return add_backdrop_looks(app,name,tex,w,h);
}
static inline void add_default_da_looks(app_looks* app) {
    if (!app||!app->ren) return;
    SDL_Texture * bg1=create_checker_texture_looks(app->ren,512,384,looks_rgb(30,30,40),looks_rgb(40,40,55));
    SDL_Texture* bg2=create_checker_texture_looks(app->ren,512,384,looks_rgb(20,50,35),looks_rgb(30,70,45));
    add_backdrop_looks(app,"GRID",bg1,512,384);
    add_backdrop_looks(app,"FOREST",bg2,512,384);
    int s1=add_sprites_looks(app,"Sprite1");
    int s2=add_sprites_looks(app,"Sprite2");
    SDL_Texture* t1=create_shit_face_sprite_texture_looks(app->ren,80,80);
    SDL_Texture* t2=create_shit_face_sprite_texture_looks(app->ren,60,60);
    app->sprite[s1].x=-80;
    app->sprite[s1].y=-20;
    app->sprite[s2].x=-60;
    app->sprite[s2].y=10;
    app->active_sprite=s1;
}
static inline void recal_c_layout(app_looks* app) {
    if (!app) return;
    const int top_h=44;
    const int pal_w=290;
    const int stage_w=360;
    app->top_bar=SDL_Rect{0,0,app->win_w,top_h};
    app->palet=SDL_Rect{0,top_h,pal_w,app->win_h-top_h};
    app->stage_p=SDL_Rect{app->win_w-stage_w,top_h,stage_w,app->win_h-top_h};
    app->workspace=SDL_Rect{pal_w,top_h,app->win_w - pal_w -stage_w,app->win_h - top_h};
    app->button_run=SDL_Rect{12,8,90,28};
    app->button_stop=SDL_Rect{110,8,90,28};
}
static inline void init_field_text_looks(field_looks& f,SDL_Rect r,const char* txt) {
    f.type=field_text_looks;
    f.rect=r;
    safe_str_cpy_looks(f.text,sizeof(f.text),txt?txt:"");
    f.number=0.0f;
    f.dropdown_index=0;
}
static inline void init_field_num(field_looks& f,SDL_Rect r,float v) {
    f.type=field_number_looks;
    f.rect=r;
    f.text[0]='\0';
    f.number=v;
    f.dropdown_index=0;
}
static inline void init_field_dd_looks(field_looks& f,SDL_Rect r,int idx) {
    f.type=field_dropdown_looks;
    f.rect=r;
    f.text[0]='\0';
    f.number=0.0f;
    f.dropdown_index=idx;
}
static inline void setup_block_fields_looks(app_looks* app,block_looks& b) {
    (void)app;
    b.field_count=0;
    if (block_is_reporter(b.type)) {
        b.w=160;
        b.h=28;
    }else {
        b.w=240;
        b.h=44;
    }
    switch (b.type) {
        case block_say_looks:
            b.field_count=1;
            init_field_text_looks(b.field[0],SDL_Rect{62,12,160,20},"Hello!");
            break;
        case block_say_secs_looks:
            b.w=285;
            b.h=44;
            b.field_count=2;
            init_field_text_looks(b.field[0],SDL_Rect{62,12,140,20},"Hello!");
            init_field_num(b.field[1],SDL_Rect{235,12,36,20},2.0f);
            break;
        case block_think_looks:
            b.field_count=1;
            init_field_text_looks(b.field[0],SDL_Rect{74,12,148,20},"Hmm...");
            break;
            case block_think_secs_looks:
            b.w=305;
            b.h=44;
            b.field_count=2;
            init_field_text_looks(b.field[0],SDL_Rect{74,12,150,20},"Hmm...");
            init_field_num(b.field[1],SDL_Rect{255,12,36,20},2.0f);
            break;
        case block_swich_costume_looks:
            b.w=275;
            b.h=44;
            b.field_count=1;
            init_field_dd_looks(b.field[0],SDL_Rect{160,12,100,20},0);
            break;
        case block_next_costume_looks:
            b.field_count=0;
            break;
        case block_swich_backdrop_looks:
            b.w=280;
            b.h=44;
            b.field_count=1;
            init_field_dd_looks(b.field[0],SDL_Rect{164,12,104,20},0);
            break;
            case block_next_backdrop_looks:
            b.field_count=0;
            break;
        case block_change_size_looks:
            b.w=250;
            b.h=44;
            b.field_count=1;
            init_field_num(b.field[0],SDL_Rect{154,12,60,20},10.0f);
            break;
            case block_set_size_looks:
            b.w=255;
            b.h=44;
            b.field_count=1;
            init_field_num(b.field[0],SDL_Rect{128,12,60,20},100.0f);
            break;
        case block_change_color_effect_looks:
            b.w=290;
            b.h=44;
            b.field_count=1;
            init_field_num(b.field[0],SDL_Rect{198,12,60,20},25.0f);
            break;
        case block_clear_color_effect_looks:
            b.w=220;
            b.h=44;
            b.field_count=0;
            break;
        case block_show_looks:
            b.w=110;
            b.h=44;
            b.field_count=0;
            break;
        case block_hide_looks:
            b.w=110;
            b.h=44;
            b.field_count=0;
            break;
        case block_go_front_l_looks:
            b.w=200;
            b.h=44;
            b.field_count=0;
            break;
            case block_go_back_l_looks:
            b.w=195;
            b.h=44;
            b.field_count=0;
            break;
        case block_go_forward_l_looks:
            b.w=245;
            b.h=44;
            b.field_count=1;
            init_field_num(b.field[0],SDL_Rect{128,12,44,20},1.0f);
            break;
            case block_go_backward_l_looks:
            b.w=258;
            b.h=44;
            b.field_count=1;
            init_field_num(b.field[0],SDL_Rect{140,12,44,20},1.0f);
            break;
        case block_report_costume_looks:
        case block_report_backdrop_looks:
        case block_report_size_looks:
            b.field_count=0;
            b.w=150;
            b.h=28;
            break;
            default:break;
    }
    b.next=-1;
    b.prev=-1;
}
static inline block_looks* all_oc_block_looks(app_looks* app,block_type_looks type) {
    if (!app)return nullptr;
    for (int i=0;i<max_block_of_looks;i++) {
        if (!app->block[i].use) {
            block_looks* b= app->block[i];
            std::memset(&b,0,sizeof(block_looks));
            b->use=true;
            b->id=i;
            b->type=type;
            b->x=(float)app->workspace.x+30.0f;
            b->y=(float)app->workspace.y+30.0f;
            setup_block_fields_looks(app,b);
            app->block_count=(app->block_count<i+1)?(i+1):app->block_count;
            return & b;
        }
    }
    return nullptr;
}
static inline void free_block_looks(app_looks* app,int idx) {
    if (!app)return;
    if (idx<0||idx>=max_block_of_looks) return;
    if (!app->block[idx].use) return;
    int p=app->block[idx].prev;
    int n=app->block[idx].next;
    if (p>=0)app->block[p].next=-1;
    if (n>=0) app->block[n].prev=-1;
    app->block[idx].use=false;
}
static inline int stack_tail_looks(app_looks* app,int root) {
    int t=root;
    while (t>=0&&app->block[t].next>=0)t=app->block[t].next;
    return t;
}
static inline void move_stack_looks(app_looks* app,int root,float dx,float dy) {
    int b=root;
    while (b>=0) {
        app->block[b].x+=dx;
        app->block[b].y+=dy;
        b=app->block[b].next;
    }
}
static inline int hit_test_block(app_looks* app,int mx,int my) {
    if (!app)return -1;
    int best=-1;
    for (int i=0;i<max_block_of_looks;i++) {
        if (!app->block[i].use) continue;
        block_looks& b=app->block[i];
        SDL_Rect r{(int)b.x,(int)b.y,(int)b.w,(int)b.h};
        if (is_cursor_in_rect(mx,my,r))best=i;
    }
    return best;
}
static inline void detach_from_prev(app_looks* app,int root) {
if (!app)return;
    int p=app->block[root].prev;
    if (p>=0) {
        app->block[p].next=-1;
        app->block[root].prev=-1;
    }
}
static inline int find_snap_target_looks(app_looks* app,int dragroot) {
    if (!app)return -1;
    block_looks& dr=app->block[dragroot];
    if (!block_is_stack(dr.type))return -1;
    const float topx=dr.x;
    const float topy=dr.y;
    int best=-1;
    float best_dist=1e9f;
    for (int i=0;i<max_block_of_looks;i++) {
        if (!app->block[i].use)continue;
        if (i==dragroot) continue;
        block_looks& tb=app->block[i];
        if (!block_is_stack(tb.type))continue;
        float cx=tb.x;
        float cy=tb.y+tb.h;
        float dx=(topx-cx);
        float dy=(topy-cy);
        float dist=sqrtf(dx*dx+dy*dy);
        if (dist<best_dist&&dist<=(float)snap_dist_looks) {
            best_dist=dist;
            best=i;
        }
    }
    return best;
}
static inline void snap_stack_below_looks(app_looks* app,int target,int dragroot) {
    if (!app)return;
    if (target<0||dragroot<0)return;
    int tail=stack_tail_looks(app,target);
    if (tail<0)return;
    float newx=app->block[tail].x;
    float newy=app->block[tail].y+app->block[tail].h;
    float dx=newx-app->block[dragroot].x;
    float dy=newy-app->block[dragroot].y;
    move_stack_looks(app,target,dx,dy);
    app->block[tail].next=dragroot;
    app->block[dragroot].prev=tail;
}
static inline void rebuild_palette(app_looks* app) {
    if (!app)return;
    app->palette_count=0;
    const int x=app->palet.x+16;
    int y=app->palet.y+16-app->palette_scroll_y;

    auto add_item =[&](block_type_looks t, int h){
        if (app->palette_count>=(int)(sizeof(app->palette_item)/sizeof(app->palette_item[0]))) return;
        app->palette_item[app->palette_count++]=palet_item_looks{t,SDL_Rect{x,y,app->palet.w-32,h}};
        y+=h+10;
    };
    add_item(block_say_looks,44);
    add_item(block_say_secs_looks,44);
    add_item(block_think_looks,44);
    add_item(block_think_secs_looks,44);
    y+=6;
    add_item(block_swich_costume_looks,44);
    add_item(block_next_costume_looks,44);
    y+=6;
    add_item(block_swich_backdrop_looks,44);
    add_item(block_next_backdrop_looks,44);
    y+=6;
    add_item(block_change_size_looks,44);
    add_item(block_set_size_looks,44);
    y+=6;
    add_item(block_change_color_effect_looks,44);
    add_item(block_set_color_effect_looks,44);
    add_item(block_clear_color_effect_looks,44);
    y+=6;
    add_item(block_show_looks,44);
    add_item(block_hide_looks,44);
    y+=6;
    add_item(block_go_front_l_looks,44);
    add_item(block_go_back_l_looks,44);
    add_item(block_go_forward_l_looks,44);
    add_item(block_go_backward_l_looks,44);
    y+=12;
    add_item(block_report_costume_looks,28);
    add_item(block_report_backdrop_looks,28);
    add_item(block_report_size_looks,28);
}
static inline void draw_input_box_looks(SDL_Renderer* ren,const SDL_Rect& r,SDL_Color bg,SDL_Color bord,const char* text,bool active) {
    draw_filled_rounded_rect_for_looks(ren,r,6,bg);
    draw_rounded_rect_outline_for_looks(ren,r,6,active?looks_rgb(255,255,255):bord);
    draw_text_for_looks(ren,r.x+6,r.y+6,text?text:"",1,looks_rgb(20,20,20));
}
static inline void format_number_looks(char* out,size_t outsz,float v) {
    if (!out||outsz==0)return;
    float iv=std::round(v);
    if (looks_absf(v-iv)<0.001f)std::snprintf(out,outsz,"%d",(int)iv);
    else std::sprintf(out,outsz,"%.2f",v);
}
static inline const char* block_title_looks(block_type_looks t) {
    switch (t) {
        case block_say_looks:return "say";
        case block_say_secs_looks:return "say";
        case block_think_looks:return "think";
        case block_think_secs_looks:return "think";
        case block_swich_costume_looks:return "switch costume to";
        case block_next_costume_looks:return "next costume";
        case block_swich_backdrop_looks:return "switch backdrop to";
        case block_next_backdrop_looks:return "next backdrop";
        case block_change_size_looks:return "change size by";
        case block_set_size_looks:return "set size to";
        case block_change_color_effect_looks:return "change color effect by";
        case block_set_color_effect_looks:return "set color effect to";
            case block_clear_color_effect_looks:return "clear graphic effects";
            case block_show_looks:return "show";
            case block_hide_looks:return "hide";
            case block_go_front_l_looks:return "go to front layer";
            case block_go_back_l_looks:return "go to back layer";
            case block_go_forward_l_looks:return "go forward";
            case block_go_backward_l_looks:return "go backward";
            case block_report_costume_looks:return "costume";
            case block_report_size_looks:return "size";
            case block_report_backdrop_looks:return "backdrop";
            default: return"";
    }
}
static inline void draw_stack_block_looks(SDL_Renderer* ren,const app_looks* app,const block_looks& b,bool selected) {
    SDL_Color fill=app->looks_color;
    SDL_Color outline=app->looks_outline;
    SDL_Color bg=app->back_ground;
    SDL_Rect r{(int)b.x,(int)b.y,(int)b.w,(int)b.h};
    SDL_Rect tab{r.x+34,r.y+r.h-2,64,10};
    draw_filled_rounded_rect_for_looks(ren,r,10,fill);
    draw_filled_rounded_rect_for_looks(ren,tab,5,fill);
    SDL_Rect notch{r.x+36,r.y-1,56,9};
    draw_filled_rounded_rect_for_looks(ren,notch,4,bg);
    draw_rounded_rect_outline_for_looks(ren,r,10,selected?app->highlight:outline);
    draw_rounded_rect_outline_for_looks(ren,tab,5,selected?app->highlight:outline);
    const int tx=r.x+12;
    const int ty=r.y+14;
    char numbuf[32];
    switch(b.type) {
        case block_say_looks:
        draw_text_for_looks(ren,tx,ty,"say",1,app->text);
        break;
        case block_say_secs_looks:
        draw_text_for_looks(ren,tx,ty,"say",1,app->text);
        draw_text_for_looks(ren,r.x+208,ty,"for",1,app->text);
        draw_text_for_looks(ren,r.x+276,ty,"secs",1,app->text);
        break;
        case block_think_looks:
        draw_text_for_looks(ren,tx,ty,"think",1,app->text);
        break;
        case block_think_secs_looks:
            draw_text_for_looks(ren,tx,ty,"think",1,app->text);
            draw_text_for_looks(ren,r.x+230,ty,"for",1,app->text);
            draw_text_for_looks(ren,r.x+296,ty,"secs",1,app->text);
            break;
            case block_swich_costume_looks:
            draw_text_for_looks(ren,tx,ty,"switch costume to",1,app->text);
            break;
            case block_next_costume_looks:
            draw_text_for_looks(ren,tx,ty,"next costume",1,app->text);
            break;
            case block_swich_backdrop_looks:
            draw_text_for_looks(ren,tx,ty,"switch backdrop to",1,app->text);
            break;
            case block_next_backdrop_looks:
            draw_text_for_looks(ren,tx,ty,"next backdrop",1,app->text);
            break;
            case block_change_size_looks:
            draw_text_for_looks(ren,tx,ty,"change size by",1,app->text);
            break;
            case block_set_size_looks:
            draw_text_for_looks(ren,tx,ty,"set size to",1,app->text);
            draw_text_for_looks(ren,r.x+r.w-26,ty,"%",1,app->text);
            break;
            case block_change_color_effect_looks:
            draw_text_for_looks(ren,tx,ty,"change color effect by",1,app->text);
            break;
            case block_set_color_effect_looks:
            draw_text_for_looks(ren,tx,ty,"set color effect to",1,app->text);
            break;
        case block_clear_color_effect_looks:
            draw_text_for_looks(ren,tx,ty,"clear graphic effect to",1,app->text);
            break;
        case block_show_looks:
            draw_text_for_looks(ren,tx,ty,"show",1,app->text);
            break;
            case block_hide_looks:
            draw_text_for_looks(ren,tx,ty,"hide",1,app->text);
            break;
        case block_go_front_l_looks:
            draw_text_for_looks(ren,tx,ty,"go front layer",1,app->text);
            break;
            case block_go_back_l_looks:
            draw_text_for_looks(ren,tx,ty,"go to back layer",1,app->text);
            break;
            case block_go_forward_l_looks:
            draw_text_for_looks(ren,tx,ty,"go forward",1,app->text);
            draw_text_for_looks(ren,r.x+r.w-56,ty,"layers",1,app->text);
            break;
            case block_go_backward_l_looks:
            draw_text_for_looks(ren,tx,ty,"go backward",1,app->text);
            draw_text_for_looks(ren,r.x-r.w-56,ty,"layers",1,app->text);
            break;
            default:break;
    }
    for (int i=0;i<b.field_count;i++) {
        const field_looks& f=b.field[i];
        SDL_Rect fr{r.x +f.rect.x,r.y+f.rect.y,f.rect.w,f.rect.h};
        bool active=(app->text_input_on&&app->edit_block==b.id&&app->edit_field==i);
        bool ddActive=(app->dropdown_open&&app->dropdown_block==b.id&&app->dropdown_field==i);
        if (f.type==field_text_looks) {
            draw_input_box_looks(ren,fr,app->input_bg,app->input_border,f.text,active);
        } else if (f.type==field_number_looks){
            format_number_looks(numbuf,sizeof(numbuf),f.number);
            draw_input_box_looks(ren,fr,app->input_bg,app->input_border,numbuf,active);
        } else if (f.type==field_dropdown_looks) {
            char label[max_name_of_looks]="none";
            if (b.type==block_swich_costume_looks&&app->sprite_count>0) {
                const sprite_looks& sp=app->sprite[app->active_sprite];
                if (sp.costume_count>0) {
                    int idx=looks_clamp_i(f.dropdown_index,0,sp.costume_count-1);
                    std::snprintf(label,sizeof(label),"%s",sp.costume[idx].name);
                }
            } else if (b.type==block_swich_backdrop_looks&&app->stage.backdrop_count>0) {
                int idx=looks_clamp_i(f.dropdown_index,0,app->stage.backdrop_count-1);
                std::snprintf(label,sizeof(label),"%s",app->stage.backdrop[idx].name);
            }
            draw_input_box_looks(ren,fr,app->input_bg,app->input_border,label,ddActive);
            set_draw_color(ren,looks_rgb(50,50,50));
            SDL_RenderDrawLine(ren,fr.x+fr.w-10,fr.y+8,fr.x+fr.w-4,fr.y+8);
            SDL_RenderDrawLine(ren,fr.x+fr.w-9,fr.y+9,fr.x+fr.w-5,fr.y+9);
        }
    }
}
static inline void draw_reporter_block_looks(SDL_Renderer* ren, app_looks* app,const block_looks& b,bool selected) {
    SDL_Color fill=looks_rgb(150,110,255);
    SDL_Rect r{(int)b.x,(int)b.y,(int)b.w,(int)b.h};
    draw_filled_rounded_rect_for_looks(ren,r,14,fill);
    draw_rounded_rect_outline_for_looks(ren,r,14,selected?app->highlight:app->looks_outline);
    const char* t=block_title_looks(b.type);
    draw_text_for_looks(ren,r.x+10,r.y+9,t,1,app->text);
}
static inline void draw_block_looks(SDL_Renderer* ren, app_looks& app,const block_looks& b,bool selected) {
    if (block_is_reporter(b.type))draw_reporter_block_looks(ren,app,b,selected);
    else {
        draw_stack_block_looks(ren,app,b,selected);
    }
}
 static inline  void draw_dropdown_looks(SDL_Renderer* ren,app_looks* app) {
    if (!app||!app->dropdown_open)return;
    if (app->dropdown_block<0||app->dropdown_block>=max_block_of_looks)return;
    block_looks& b=app->block[app->dropdown_block];
    if (!b.use)return;
    if (app->dropdown_field<0||app->dropdown_field>=b.field_count)return;
    field_looks& f=b.field[app->dropdown_field];
    if (f.type!=field_dropdown_looks) return;
    SDL_Rect br{(int)b.x,(int)b.y,(int)b.w,(int)b.h};
    SDL_Rect fr{br.x+f.rect.x,br.y+f.rect.y,f.rect.w,f.rect.h};
    const char* items[max_costumes_of_looks];
    int count=0;
    if (b.type==block_swich_costume_looks&&app->sprite_count>0) {
        const sprite_looks& sp=app->sprite[app->active_sprite];
        count=sp.costume_count;
        for (int i=0;i<count;i++) {
            items[i]=sp.costume[i].name;
        }
    }else if (b.type==block_swich_backdrop_looks) {
        count=app->stage.backdrop_count;
        for (int i=0;i<count;i++) {
            items[i]=app->stage.backdrop[i].name;
        }
    }
    if (count<=0)return;
    const int item_h=22;
    SDL_Rect list{fr.x,fr.y+fr.h+2,fr.w,item_h*count};
    draw_filled_rounded_rect_for_looks(ren,list,6,looks_rgb(245,245,245));
    draw_rounded_rect_outline_for_looks(ren,list,6,looks_rgb(90,90,90));
    for (int i=0;i<count;i++) {
        SDL_Rect it{list.x,list.y+i*item_h,list.w,item_h};
        bool hover=is_cursor_in_rect(app->mouse_x,app->mouse_y,it);
        if (hover){
            set_draw_color(ren,looks_rgb(220,220,220));
            SDL_RenderFillRect(ren,&it);
        }
        draw_text_for_looks(ren,it.x+6,it.y+7,items[i],1,looks_rgb(20,20,20));
    }
}
static inline void hsv_to_rgb_looks(float h_deg,float s,float v,uint8_t& outR,uint8_t& outG,uint8_t& outB) {
    float h=std::fmod(h_deg,360.0f);
    if (h<0)h+=360.0f;
    float c=v*s;
    float x=c*(1.0f-std::fabs(std::fmod(h/60.0f,2.0f)-1.0f));
    float m=v-c;
    float r=0,g=0,b=0;
    if (h<60) {
        r=c;
        g=x;
        b=0;
    }
    else if (h<120) {
        r=x;
        g=c;
        b=0;
    }
    else if (h<180) {
        r=0;
        g=c;
        b=x;
    }
    else if (h<240) {
        r=0;
        g=x;
        b=c;
    }
    else if (h<300) {
        r=x;
        g=0;
        b=c;
    }
    else {
        r=c;
        g=0;
        b=x;
    }
    outR=(uint8_t)looks_clamp_i((int)std::round((r+m)*255.0f),0,255);
    outG=(uint8_t)looks_clamp_i((int)std::round((g+m)*255.0f),0,255);
    outB=(uint8_t)looks_clamp_i((int)std::round((b+m)*255.0f),0,255);
}
static inline void stage_to_screen_looks(const app_looks* app,float sx,float sy,int& outX,int& outY) {
    const SDL_Rect& R=app->stage_p;
    float scaleX=(float)R.w/(float)max_stage_width_of_looks;
    float scaleY=(float)R.h/(float)max_stage_hight_of_looks;
    outX =(int)std::round(R.x+R.w*0.5f+sx*scaleX);
    outY =(int)std::round(R.y+R.h*0.5f-sy*scaleY);
}
static inline void draw_bubble_looks(SDL_Renderer* ren,const app_looks* app,int spriteIdx) {
     const sprite_looks&sp=app->sprite[spriteIdx];
    if (sp.bubble_type==bubble_none_looks) return;
    if (sp.bubble_text[0]=='\0') return;
    int px,py;
    stage_to_screen_looks(app,sp.x,sp.y,px,py);
    int len=(int)std::strlen(sp.bubble_text);
    int w=looks_clamp_i(80+len*6,90,260);
    int h=40;
    SDL_Rect bubble {px+30,py-70,w,h};
    if (bubble.x+bubble.w>app->stage_p.x+app->stage_p.w) bubble.x=app->stage_p.x+app->stage_p.w-bubble.w-6;
    if (bubble.y<app->stage_p.y)bubble.y=app->stage_p.y+6;
    draw_filled_rounded_rect_for_looks(ren,bubble,12,looks_rgb(255,255,255));
    draw_rounded_rect_outline_for_looks(ren,bubble,12,looks_rgb(30,30,30));
    draw_text_for_looks(ren,bubble.x+10,bubble.y+14,sp.bubble_text,1,looks_rgb(10,10,10));
    if (sp.bubble_type==bubble_say_looks) {
        SDL_Point p1 {px+18,py-20};
        SDL_Point p2 {bubble.x+20,bubble.y+bubble.h};
        SDL_Point p3 {bubble.x+44,bubble.y+bubble.h};
        set_draw_color(ren,looks_rgb(255,255,255));
        for (int y=0;y<18;y++) {
            int x1=(int)std::round(p1.x+(p2.x-p1.x)*(y/18.0f));
            int x2=(int)std::round(p1.x+(p3.x-p1.x)*(y/18.0f));
            SDL_RenderDrawLine(ren,x1,p1.y+y,x2,p1.y+y);
        }
        set_draw_color(ren,looks_rgb(30,30,30));
        SDL_RenderDrawLine(ren,p1.x,p1.y,p2.x,p2.y);
        SDL_RenderDrawLine(ren,p1.x,p1.y,p3.x,p3.y);
        SDL_RenderDrawLine(ren,p2.x,p2.y,p3.x,p3.y);
    } else {
        SDL_Color c=looks_rgb(255,255,255);
        SDL_Color o=looks_rgb(30,30,30);
        auto circle=[&](int cx,int cy,int rad){
            set_draw_color(ren,c);
            for (int dy=-rad;dy<=rad;dy++) {
                for (int dx=-rad;dx<=rad;dx++) {
                    if (dx*dx+dy*dy<=rad*rad)SDL_RenderDrawPoint(ren,cx+dx,cy+dy);
                }
            }
            set_draw_color(ren,o);
            for (int ang=0;ang<360;ang+=12) {
                float a=ang*3.14159265f/180.0f;
                int dx=(int)std::round(std::cos(a)*rad);
                int dy=(int)std::round(std::sin(a)*rad);
                SDL_RenderDrawPoint(ren,cx+dx,cy+dy);
            }
        };
        circle(px+22,py-14,6);
        circle(px+30,py-26,5);
        circle(px+40,py-38,4);
    }
}
static inline void render_stage_looks(app_looks* app) {
    if (!app) return;
    SDL_Renderer* ren=app->ren;
    draw_filled_rounded_rect_for_looks(ren,app->stage_p,10,looks_rgb(245,245,250));
    draw_rounded_rect_outline_for_looks(ren,app->stage_p,10,looks_rgb(150,150,160));
    if (app->stage.backdrop_count>0) {
        int bi=looks_clamp_i(app->stage.backdrop_index,0,app->stage.backdrop_count-1);
        SDL_Texture* tex =app->stage.backdrops[bi].tex;
        if (tex) {
            SDL_Rect dst=app->stage_p;
            SDL_RenderCopy(ren,tex,nullptr,&dst);
        }
    }else {
        set_draw_color(ren,looks_rgb(220,220,230));
        SDL_RenderFillRect(ren,&app->stage_p);
    }
    for (int oi=app->sprite_count-1;oi>=0;oi--) {
        int si=app->sprite_order[oi];
        if(si<0||si>=app->sprite_count)continue;
        sprite_looks& sp=app->sprite[si];
        if (!sp.visible)continue;
        if (sp.costume_count<=0)continue;
        int ci=looks_clamp_i(sp.costume_index,0,sp.costume_count-1);
        SDL_Texture* tex =sp.costume[ci].tex;
        if (!tex) continue;
        int px,py;
        stage_to_screen_looks(app,sp.x,sp.y,px,py);
        float scaleX=(float)app->stage_p.w/(float)max_stage_width_of_looks;
        float scaleY=(float)app->stage_p.h/(float)max_stage_hight_of_looks;
        float sc=(sp.size_per/100.0f);
        int dw=(int)std::round(sp.costume[ci].w * sc* scaleX);
        int dh=(int)std::round(sp.costume[ci].h *sc* scaleY);
        SDL_Rect dst {px-dw/2,py-dh/2,dw,dh};
        uint8_t tr=255,tg=255,tb=255;
        float hue=(sp.color_effect/200.0f)*360.0f;
        if (looks_absf(sp.color_effect)>0.001f)hsv_to_rgb_looks(hue,0.9f,1.0f,tr,tg,tb);
        SDL_SetTextureColorMod(tex,tr,tg,tb);
        SDL_SetTextureAlphaMod(tex,sp.alph);
        SDL_RenderCopy(ren,tex,nullptr,&dst);
        SDL_SetTextureColorMod(tex,255,255,255);
        SDL_SetTextureAlphaMod(tex,255);
        if (si==app->active_sprite) {
            set_draw_color(ren,looks_rgb(0,160,255));
            SDL_Rect outline=dst;
            SDL_RenderDrawRect(ren,&outline);
        }
    }
    for (int oi=app->sprite_count-1;oi>=0;oi--) {
        int si=app->sprite_order[oi];
        if (si<0||si>=app->sprite_count) continue;
        draw_bubble_looks(ren,app,si);
    }

    int mx=app->stage_p.x+app->stage.watch_x;
    int my=app->stage_p.y+app->stage.watch_y;
    auto draw_monitor=[&](const char* label,const char* value){
        SDL_Rect r {mx,my,190,28};
        draw_filled_rounded_rect_for_looks(ren,r,8,looks_rgb(255,255,210));
        draw_rounded_rect_outline_for_looks(ren,r,8,looks_rgb(120,120,90));
        draw_text_for_looks(ren,r.x+8,r.y+9,label,1,looks_rgb(40,40,20));
        draw_text_for_looks(ren,r.x+86,r.y+9,value,1,looks_rgb(40,40,20));
        my+=32;
    };
    char val[64];
    if (app->stage.watch_backdrop) {
        if (app->stage.backdrop_count>0) {
            int bi=looks_clamp_i(app->stage.backdrop_index,0,app->stage.backdrop_count-1);
            std::snprintf(val,sizeof(val),"%d %s",bi+1,app->stage.backdrop[bi].name);
        } else std::snprintf(val,sizeof(val),"none");
        draw_monitor("Backdrop:",val);
    }
    if (app->stage.watch_costume) {
        if (app->sprite_count>0) {
            const sprite_looks& sp=app->sprite[app->active_sprite];
            if (sp.costume_count>0) {
                int ci=looks_clamp_i(sp.costume_index,0,sp.costume_count-1);
                std::snprintf(val,sizeof(val),"%d %s",ci+1,sp.costume[ci].name);
            } else std::snprintf(val,sizeof(val),"none");
        } else std::snprintf(val,sizeof(val),"none");
        draw_monitor("Costume:",val);
    }
    if (app->stage.watch_size) {
        if (app->sprite_count>0) {
            std::snprintf(val,sizeof(val),"%.0f%%",app->sprite[app->active_sprite].size_per);
        } else std::snprintf(val,sizeof(val),"0%%");
        draw_monitor("Size:",val);
    }
    SDL_Rect sprPanel {app->stage_p.x,app->stage_p.y+app->stage_p.h-84,app->stage_p.w,84};
    set_draw_color(ren,looks_rgb(245,245,250));
    SDL_RenderFillRect(ren,&sprPanel);
    set_draw_color(ren,looks_rgb(180,180,190));
    SDL_RenderDrawLine(ren,sprPanel.x,sprPanel.y,sprPanel.x+sprPanel.w,sprPanel.y);
    draw_text_for_looks(ren,sprPanel.x+10,sprPanel.y+10,"Sprites:",1,looks_rgb(40,40,50));
    int bx=sprPanel.x+10;
    int by=sprPanel.y+28;
    for (int i=0;i<app->sprite_count;i++) {
        SDL_Rect btn{bx,by,100,22};
        bool act=(i==app->active_sprite);
       draw_filled_rounded_rect_for_looks(ren,btn,6,act?looks_rgb(210,235,255) : looks_rgb(240,240,245));
        draw_rounded_rect_outline_for_looks(ren,btn,6,looks_rgb(150,150,160));
        draw_text_for_looks(ren,btn.x+6,btn.y+7,app->sprite[i].name,1,looks_rgb(30,30,40));
        bx+=110;
        if (bx+100>sprPanel.x+sprPanel.w){
            bx=sprPanel.x+10;
            by+=26;
        }
    }
}
static inline void set_bubble_looks(app_looks* app,int spriteIdx,bubble_type_looks t,const char* msg,uint32_t now,float secondsOr0) {
    if (!app) return;
    if (spriteIdx<0||spriteIdx>=app->sprite_count) return;
    sprite_looks& sp=app->sprite[spriteIdx];
    sp.bubble_type=t;
    safe_str_cpy_looks(sp.bubble_text,sizeof(sp.bubble_text),msg?msg:"");
    if (secondsOr0>0.0f)sp.bubble_exp_ms=now+(uint32_t)std::round(secondsOr0*1000.0f);
    else sp.bubble_exp_ms=0;
}
static inline void clear_bubble_if_expired_looks(app_looks* app,uint32_t now) {
    if (!app) return;
    for (int i=0;i<app->sprite_count;i++) {
        sprite_looks&sp=app->sprite[i];
        if (sp.bubble_exp_ms!=0&&now>=sp.bubble_exp_ms) {
            sp.bubble_type=bubble_none_looks;
            sp.bubble_text[0]='\0';
            sp.bubble_exp_ms=0;
        }
    }
}
static inline void move_sprite_order_looks(app_looks* app,int spriteIdx,int newPosFrontIndex0) {
    if (!app) return;
    int n=app->sprite_count;
    newPosFrontIndex0=looks_clamp_i(newPosFrontIndex0,0,n-1);
    int cur=-1;
    for (int i=0;i<n;i++) if (app->sprite_order[i]==spriteIdx) {
        cur=i;
        break;
    }
    if (cur<0||cur==newPosFrontIndex0)return;
    int tmp=app->sprite_order[cur];
    if (cur<newPosFrontIndex0) {
        for (int i=cur;i<newPosFrontIndex0;i++)app->sprite_order[i]=app->sprite_order[i+1];
    } else {
        for (int i=cur;i>newPosFrontIndex0;i--)app->sprite_order[i]=app->sprite_order[i-1];
    }
    app->sprite_order[newPosFrontIndex0]=tmp;
}
static inline void exec_block_looks(app_looks* app,int blockIdx,int threadIdx,uint32_t now) {
    (void)threadIdx;
    if (!app) return;
    if (blockIdx<0||blockIdx>=max_block_of_looks) return;
    block_looks&b=app->block[blockIdx];
    if (!b.use) return;
    int sidx=looks_clamp_i(app->active_sprite,0,(app->sprite_count>0?app->sprite_count-1:0));
    auto num0=[&]()->float {return (b.field_count>=1&&b.field[0].type==field_number_looks)?b.field[0].number:0.0f;};
    auto num1=[&]()->float { return(b.field_count>=2&&b.field[1].type==field_number_looks)?b.field[1].number:0.0f;};
    switch (b.type) {
        case block_say_looks:
            if (app->sprite_count>0) set_bubble_looks(app,sidx,bubble_say_looks,b.field[0].text,now,0.0f);
            break;
        case block_say_secs_looks:
            if (app->sprite_count>0) set_bubble_looks(app,sidx,bubble_say_looks,b.field[0].text, now, num1());
            app->thread[threadIdx].wait_until=now+(uint32_t)std::round(num1()*1000.0f);
            break;
        case block_think_looks:
            if (app->sprite_count>0) set_bubble_looks(app,sidx,bubble_say_looks,b.field[0].text, now, 0.0f);
            break;
        case block_think_secs_looks:
            if (app->sprite_count>0) set_bubble_looks(app, sidx,bubble_say_looks,b.field[0].text, now, num1());
            app->thread[threadIdx].wait_until=now+(uint32_t)std::round(num1()*1000.0f);
            break;

        case block_swich_costume_looks:
            if (app->sprite_count>0) {
                sprite_looks& sp=app->sprite[sidx];
                if (sp.costume_count>0) sp.costume_index=looks_clamp_i(b.field[0].dropdown_index,0,sp.costume_count-1);
            }
            break;
        case block_next_costume_looks:
            if (app->sprite_count>0) {
                sprite_looks& sp=app->sprite[sidx];
                if (sp.costume_count>0) sp.costume_index=(sp.costume_index+1)%sp.costume_count;
            }
            break;
        case block_swich_backdrop_looks:
            if (app->stage.backdrop_count>0)app->stage.backdrop_index=looks_clamp_i(b.field[0].dropdown_index,0,app->stage.backdrop_count-1);
            break;
        case block_next_backdrop_looks:
            if (app->stage.backdrop_count>0) app->stage.backdrop_index=(app->stage.backdrop_index+1)%app->stage.backdrop_count;
            break;
        case block_change_size_looks:
            if (app->sprite_count>0) {
                sprite_looks& sp=app->sprite[sidx];
                sp.size_per=looks_clamp_f(sp.size_per+num0(),5.0f,500.0f);
            }
            break;
        case block_set_size_looks:
            if (app->sprite_count>0) {
                sprite_looks& sp=app->sprite[sidx];
                sp.size_per=looks_clamp_f(num0(),5.0f,500.0f);
            }
            break;
        case block_change_color_effect_looks:
            if (app->sprite_count>0) {
                sprite_looks& sp=app->sprite[sidx];
                sp.color_effect+=num0();
                while (sp.color_effect<0.0f) sp.color_effect+=200.0f;
                while (sp.color_effect>200.0f) sp.color_effect-=200.0f;
            }
            break;
        case block_set_color_effect_looks:
            if (app->sprite_count>0) {
                sprite_looks& sp=app->sprite[sidx];
                sp.color_effect=num0();
                while (sp.color_effect<0.0f) sp.color_effect+=200.0f;
                while (sp.color_effect>200.0f) sp.color_effect-=200.0f;
            }
            break;
        case block_clear_color_effect_looks:
            if (app->sprite_count>0) {
                sprite_looks& sp=app->sprite[sidx];
                sp.color_effect=0.0f;
                sp.alph=255;
            }
            break;
        case block_show_looks:
            if (app->sprite_count>0) app->sprite[sidx].visible = true;
            break;
        case block_hide_looks:
            if (app->sprite_count>0) app->sprite[sidx].visible = false;
            break;
        case block_go_front_l_looks:
            if (app->sprite_count>0) move_sprite_order_looks(app,sidx,0);
            break;
        case block_go_back_l_looks:
            if (app->sprite_count>0) move_sprite_order_looks(app,sidx,app->sprite_count-1);
            break;
        case block_go_forward_l_looks:
            if (app->sprite_count>0) {
                int cur=-1;
                for (int i=0;i<app->sprite_count;i++) if (app->sprite_order[i]==sidx) {
                    cur=i;break;
                }
                int step=(int)std::round(num0());
                move_sprite_order_looks(app,sidx,cur-step);
            }
            break;
        case block_go_backward_l_looks:
            if (app->sprite_count>0) {
                int cur=-1;
                for (int i=0; i<app->sprit_count;i++) {
                    if (app->sprite_order[i]==sidx) {
                        cur=i;break;
                    }
                }
                int step=(int)std::round(num0());
                move_sprite_order_looks(app,sidx,cur+step);
            }
            break;

        default:
            break;
    }
}
static inline void Looks_StartRun(app_looks* app) {
    if (!app) return;
    app->running=true;
    app->thread_count=0;
    for (int i=0;i<max_block_of_looks;i++) {
        if (!app->block[i].use) continue;
        block_looks& b=app->block[i];
        if (!block_is_stack(b.type)) continue;
        if (b.prev!=-1) continue;
        if (app->thread_count>=max_threads_of_looks) break;
        app->thread[app->thread_count++]=thread_looks{true,i,0};
    }
    if (app->thread_count==0) app->running=false;
}
static inline void stop_run_looks(app_looks* app) {
    if (!app) return;
    app->running=false;
    for (int i=0;i<app->thread_count;i++) app->thread[i].ali=false;
    app->thread_count=0;
}
static inline void end_text_input_looks(app_looks* app) {
    if (!app) return;
    if (app->text_input_on) SDL_StopTextInput();
    app->text_input_on=false;
    app->edit_block=-1;
    app->edit_field=-1;
    app->is_num_edit=false;
}
static inline void begin_text_input_looks(app_looks* app,int blockIdx,int fieldIdx,bool isNumber) {
    if (!app) return;
    app->text_input_on=true;
    app->edit_block=blockIdx;
    app->edit_field=fieldIdx;
    app->is_num_edit=isNumber;
    SDL_StartTextInput();
}
static inline void toggle_reporter_watch_looks(app_looks* app,block_type_looks t) {
    if (!app) return;
    if (t==block_report_costume_looks) app->stage.watch_costume=!app->stage.watch_costume;
    else if (t==block_report_backdrop_looks) app->stage.watch_backdrop=!app->stage.watch_backdrop;
    else if (t==block_report_size_looks) app->stage.watch_size=!app->stage.watch_size;
}
static inline void handle_click_stage_sprite_buttons_looks(app_looks* app,int mx,int my) {
    SDL_Rect sprPanel {app->stage_p.x,app->stage_p.y+app->stage_p.h-84,app->stage_p.w,84 };
    int bx=sprPanel.x+10;
    int by=sprPanel.y+28;
    for (int i=0;i<app->sprite_count;i++) {
        SDL_Rect btn {bx,by,100,22 };
        if (is_cursor_in_rect(mx,my,btn)) {
            app->active_sprite=i;
            return;
        }
        bx+=110;
        if (bx+100>sprPanel.x+sprPanel.w) {
            bx=sprPanel.x+10;by+=26;
        }
    }
}
static inline void handle_dropdown_click_looks(app_looks* app,int mx,int my) {
    if (!app||!app->dropdown_open) return;
    int bidx=app->dropdown_block;
    int fidx=app->dropdown_field;
    if (bidx<0||bidx>=max_block_of_looks) return;
    block_looks&b=app->block[bidx];
    if (!b.use) return;
    if (fidx<0||fidx>=b.field_count) return;
    field_looks&f=b.field[fidx];
    if (f.type!=field_dropdown_looks) return;
    SDL_Rect br {(int)b.x,(int)b.y,(int)b.w,(int)b.h };
    SDL_Rect fr {br.x+f.rect.x,br.y+f.rect.y,f.rect.w,f.rect.h };
    int count=0;
    if (b.type==block_swich_costume_looks&&app->sprite_count>0)count=app->sprite[app->active_sprite].costume_count;
    else if (b.type==block_swich_backdrop_looks)count=app->stage.backdrop_count;
    if (count<=0) {
        app->dropdown_open=false;
        return;
    }
    const int itemH=22;
    SDL_Rect list {fr.x,fr.y+fr.h+2,fr.w,itemH *count };
    if (!is_cursor_in_rect(mx,my,list)) {
        app->dropdown_open=false;
        return;
    }
    int relY=my-list.y;
    int idx=relY/itemH;
    idx = looks_clamp_i(idx,0,count-1);
    f.dropdown_index=idx;
    app->dropdown_open=false;
}
static inline void Looks_HandleEvent(app_looks* app, const SDL_Event& e) {
    if (!app) return;
    if (e.type==SDL_MOUSEMOTION) {
        app->mouse_x=e.motion.x;
        app->mouse_y=e.motion.y;
        if (app->dragging) {
            float nx=(float)app->mouse_x-app->drag_ox;
            float ny=(float)app->mouse_y-app->drag_oy;
            float dx=nx-app->block[app->drag_root].x;
            float dy=ny-app->block[app->drag_root].y;
            move_stack_looks(app,app->drag_root,dx,dy);
        }
    }
    if (e.type==SDL_MOUSEBUTTONDOWN&&e.button.button==SDL_BUTTON_LEFT) {
        app->mouse_down=true;
        int mx=e.button.x,my=e.button.y;
        if (app->dropdown_open) {
            handle_dropdown_click_looks(app,mx,my);
            return;
        }
        if (is_cursor_in_rect(mx,my,app->button_run)) {
            Looks_StartRun(app);
            end_text_input_looks(app);
            return;
        }
        if (is_cursor_in_rect(mx,my,app->button_stop)) {
            stop_run_looks(app);
            end_text_input_looks(app);
            return;
        }
        if (is_cursor_in_rect(mx,my,app->stage_p)) {
            handle_click_stage_sprite_buttons_looks(app,mx,my);
            end_text_input_looks(app);
            return;
        }
        if (is_cursor_in_rect(mx,my,app->palet)) {
            for (int i=0;i<app->palette_count;i++) {
                const palet_item_looks& it=app->palette_item[i];
                if (is_cursor_in_rect(mx,my,it.rect)) {
                    if (is_cursor_in_rect(it.type)) {
                        toggle_reporter_watch_looks(app,it.type);
                    }
                    block_looks* b=all_oc_block_looks(app,it.type);
                    if (!b) return;
                    b->x=(float)mx-b->w*0.3f;
                    b->y=(float)my-b->h*0.5f;
                    app->dragging=true;
                    app->drag_root=b->id;
                    app->drag_from_pallete=1;
                    app->drag_ox=(float)mx-b->x;
                    app->drag_oy=(float)my-b->y;
                    end_text_input_looks(app);
                    return;
                }
            }
        }
        if (is_cursor_in_rect(mx,my,app->workspace)) {
            int hit=hit_test_block(app,mx,my);
            if (hit>=0) {
                block_looks& b=app->block[hit];
                SDL_Rect br {(int)b.x,(int)b.y,(int)b.w,(int)b.h};
                bool fieldClicked=false;
                for (int fi=0;fi<b.field_count;fi++) {
                    field_looks& f=b.field[fi];
                    SDL_Rect fr {br.x+f.rect.x,br.y+f.rect.y,f.rect.w,f.rect.h };
                    if (is_cursor_in_rect(mx,my,fr)) {
                        fieldClicked=true;
                        if (f.type==field_text_looks) {
                            begin_text_input_looks(app,hit,fi,false);
                        } else if (f.type==field_number_looks) {
                            begin_text_input_looks(app,hit,fi,true);
                        } else if (f.type==field_dropdown_looks) {
                            app->dropdown_open=true;
                            app->dropdown_block=hit;
                            app->dropdown_field=fi;
                            end_text_input_looks(app);
                        }
                        break;
                    }
                }
                if (fieldClicked) return;
                detach_from_prev(app,hit);
                app->dragging=true;
                app->drag_root=hit;
                app->drag_from_pallete=0;
                app->drag_ox=(float)mx-b.x;
                app->drag_oy=(float)my-b.y;
                end_text_input_looks(app);
                return;
            } else {
                end_text_input_looks(app);
            }
        }
    }
    if (e.type==SDL_MOUSEBUTTONUP&&e.button.button==SDL_BUTTON_LEFT) {
        app->mouse_down=false;
        int mx=e.button.x,my=e.button.y;
        if (app->dragging) {
            bool insideWS=is_cursor_in_rect(mx,my,app->workspace);
            if (!insideWS&&app->drag_from_pallete) {
                free_block_looks(app,app->drag_root);
            } else {
                int target=find_snap_target_looks(app,app->drag_root);
                if (target>=0)snap_stack_below_looks(app,target,app->drag_root);
            }
            app->dragging=false;
            app->drag_root=-1;
            app->drag_from_pallete=0;
        }
    }
    if (app->text_input_on) {
        if (e.type==SDL_TEXTINPUT) {
            if (app->edit_block>=0&&app->edit_block<max_block_of_looks) {
                block_looks& b=app->block[app->edit_block];
                if (b.use&&app->edit_field>=0&&app->edit_field<b.field_count) {
                    field_looks& f=b.field[app->edit_field];
                    const char* in=e.text.text;
                    if (!in) return;
                    if (!app->is_num_edit) {
                        size_t cur=std::strlen(f.text);
                        size_t add=std::strlen(in);
                        if (cur+add<sizeof(f.text)-1) std::strcat(f.text,in);
                    } else {
                        char buf[64];
                        format_number_looks(buf,sizeof(buf),f.number);
                        size_t cur=std::strlen(buf);
                        size_t add=std::strlen(in);
                        if (cur+add<sizeof(buf)-1) std::strcat(buf,in);
                        f.number=(float)std::atof(buf);
                    }
                }
            }
        }
        if (e.type==SDL_KEYDOWN) {
            if (e.key.keysym.sym==SDLK_RETURN||e.key.keysym.sym==SDLK_KP_ENTER||e.key.keysym.sym==SDLK_ESCAPE) {
                end_text_input_looks(app);
            } else if (e.key.keysym.sym==SDLK_BACKSPACE) {
                if (app->edit_block>=0&&app->edit_block<max_block_of_looks) {
                    block_looks& b=app->block[app->edit_block];
                    if (b.use&&app->edit_field>=0&& app->edit_field<b.field_count) {
                        field_looks& f=b.field[app->edit_field];
                        if (!app->is_num_edit) {
                            size_t n=std::strlen(f.text);
                            if (n>0) f.text[n-1]='\0';
                        } else {
                            char buf[64];
                            format_number_looks(buf,sizeof(buf),f.number);
                            size_t n=std::strlen(buf);
                            if (n>0) buf[n-1]='\0';
                            f.number=(float)std::atof(buf);
                        }
                    }
                }
            }
        }
    }
    if (e.type==SDL_WINDOWEVENT&&e.window.event==SDL_WINDOWEVENT_SIZE_CHANGED) {
        app->win_w=e.window.data1;
        app->win_h=e.window.data2;
        recal_c_layout(app);
        rebuild_palette(app);
    }
    if (e.type==SDL_MOUSEWHEEL) {
        int mx=app->mouse_x,my=app->mouse_y;
        if (is_cursor_in_rect(mx,my,app->palet)) {
            app->palette_scroll_y-=e.wheel.y*30;
            app->palette_scroll_y=looks_clamp_i(app->palette_scroll_y,0,800);
            rebuild_palette(app);
        }
    }
}
static inline void Looks_Update(app_looks* app, float dtSeconds) {
    (void)dtSeconds;
    if (!app) return;
    uint32_t now=SDL_GetTicks();
    clear_bubble_if_expired_looks(app, now);
    if (app->running) {
        bool anyAlive=false;
        for (int ti=0;ti<app->thread_count;ti++) {
            thread_looks& th=app->thread[ti];
            if (!th.ali) continue;
            anyAlive=true;
            if (th.wait_until!=0&&now<th.wait_until)continue;
            int pc=th.pc;
            if (pc<0||pc>=max_block_of_looks||!app->block[pc].use) {
                th.ali=false;
                continue;
            }
            th.wait_until=0;
            exec_block_looks(app,pc,ti,now);
            int next=app->block[pc].next;
            th.pc=next;
            if (next<0)th.ali=false;
        }
        if (!anyAlive) app->running=false;
        bool still = false;
        for (int ti=0;ti<app->thread_count;ti++) if (app->thread[ti].ali) { still=true; break; }
        if (!still) { app->running=false;app->thread_count=0;}
    }
}
static inline void Looks_Render(app_looks* app) {
    if (!app) return;
    SDL_Renderer* ren=app->ren;
    set_draw_color(ren,app->back_ground);
    SDL_RenderClear(ren);
    set_draw_color(ren,app->panel);
    SDL_RenderFillRect(ren,&app->top_bar);
    set_draw_color(ren, app->panel_border);
    SDL_RenderDrawLine(ren,app->top_bar.x,app->top_bar.y+app->top_bar.h-1,app->top_bar.x+app->top_bar.w,app->top_bar.y+app->top_bar.h-1);
    draw_filled_rounded_rect_for_looks(ren,app->button_run,8,looks_rgb(60,200,90));
    draw_rounded_rect_outline_for_looks(ren,app->button_run,8,looks_rgb(20,80,30));
    draw_text_for_looks(ren,app->button_run.x+26,app->button_run.y+9,"RUN", 1,looks_rgb(10,20,10));
    draw_filled_rounded_rect_for_looks(ren,app->button_stop,8,looks_rgb(235,85,70));
    draw_rounded_rect_outline_for_looks(ren,app->button_stop,8,looks_rgb(90,30,20));
    draw_text_for_looks(ren,app->button_stop.x+24,app->button_stop.y+9,"STOP",1,looks_rgb(30,10,10));
    draw_filled_rounded_rect_for_looks(ren,app->palet,0,app->panel);
    set_draw_color(ren,app->panel_border);
    SDL_RenderDrawLine(ren,app->palet.x+app->palet.w-1,app->palet.y,app->palet.x+app->palet.w-1,app->palet.y+app->palet.h);
    SDL_Rect palHeader {app->palet.x,app->palet.y,app->palet.w,46 };
    draw_filled_rounded_rect_for_looks(ren, palHeader, 0, looks_rgb(35,35,45));
    draw_text_for_looks(ren,palHeader.x+16,palHeader.y+16,"LOOKS",1,looks_rgb(255,255,255));
    for (int i=0;i<app->palette_count;i++) {
        const palet_item_looks& it=app->palette_item[i];
        block_looks temp;
        std::memset(&temp,0,sizeof(temp));
        temp.use=true;
        temp.id=-1;
        temp.type=it.type;
        temp.x=(float)it.rect.x;
        temp.y=(float)it.rect.y;
        setup_block_fields_looks(app,temp);
        if (block_is_reporter(it.type)) {
            temp.w=160;
        } else {
            if (temp.w>it.rect.w) temp.w=(float)it.rect.w;
        }
        if (temp.y+temp.h<app->palet.y+palHeader.h) continue;
        if (temp.y > app->palet.y+app->palet.h) continue;
        draw_block_looks(ren,app,temp,false);
    }
    set_draw_color(ren,looks_rgb(248,248,252));
    SDL_RenderFillRect(ren,&app->workspace);
    set_draw_color(ren,looks_rgb(220,220,230));
    SDL_RenderDrawRect(ren,&app->workspace);
    for (int i=0;i<max_block_of_looks;i++) {
        if (!app->block[i].use) continue;
        bool sel=(app->dragging&&app->drag_root==i);
        draw_block_looks(ren,app,app->block[i],sel);
    }
    draw_dropdown_looks(ren,app);
    render_stage_looks(app);
    draw_text_for_looks(ren,app->workspace.x+10,app->workspace.y+app->workspace.h-18,"Drag Looks blocks here. Click RUN. Scroll palette with mouse wheel.",1,looks_rgb(90,90,110));
}
static inline void Looks_Init(app_looks* app,SDL_Renderer* ren,int winW,int winH) {
    if (!app) return;
    std::memset(app,0,sizeof(app_looks));
    app->ren=ren;
    app->win_w=winW;
    app->win_h=winH;
    app->back_ground=looks_rgb(235,235,240);
    app->panel=looks_rgb(245,245,250);
    app->panel_border=looks_rgb(210,210,220);
    app->looks_color=looks_rgb(150,90,255);
    app->looks_color_dark=looks_rgb(120,70,220);
    app->looks_outline=looks_rgb(80,50,160);
    app->text=looks_rgb(255,255,255);
    app->input_bg=looks_rgb(255,255,255);
    app->input_border=looks_rgb(200,200,210);
    app->highlight=looks_rgb(255,255,255);
    app->palette_scroll_y=0;
    app->block_count=0;
    for (int i=0;i<max_block_of_looks;i++)app->block[i].use=false;
    app->dragging=false;
    app->dragRoot=-1;
    app->edit_block=-1;
    app->edit_field=-1;
    app->dropdown_open=false;
    recal_c_layout(app);
    reset_stage_looks(app);
    reset_stage_looks(app);
    for (int i=0; i<max_sprites_of_looks;i++)app->sprite_order[i]=i;
    rebuild_palette(app);
}
static inline void Looks_Shutdown(app_looks* app) {
    if (!app) return;
    end_text_input_looks(app);
    stop_run_looks(app);
    for (int i=0; i<max_block_of_looks;i++) if (app->block[i].use)free_block_looks(app,i);
    reset_sprites_looks(app);
    reset_stage_looks(app);
}
#endif