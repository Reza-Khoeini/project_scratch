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
#ifndef snap_dist_looks
#define snap_dist_looks
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
    bool dropdown_on;
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
static inline SDL_Texture* create_checker_texture_looks(SDSDL_Renderer* ren,int w,int h,SDL_Color a,SDL_Color b) {
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
            init_field_text_looks(b.fields[0],SDL_Rect{74,12,150,20},"Hmm...");
            init_field_num(b.fields[1],SDL_Rect{255,12,36,20},2.0f);
            break;
        case block_swich_costume_looks:
            b.w=275;
            b.h=44;
            b.field_count=1;
            init_field_dd_looks(b.fields[0],SDL_Rect{160,12,100,20},0);
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
            memset(&b,0,sizeof(block_looks));
            b->use=true;
            b->id=i;
            b->type=type;
            b->x=(float)app->workspace.x+30.0f;
            b->y=(float)app->workspace.y+30.0f;
            setup_block_fields_looks(app,b);
            app->block_count=(app->block_count<i+1)?(i+1):app->block_count;
            return &b;
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
        if (dist<best_dist&&dist<=(flaot)snap_dist_looks) {
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
}


#endif