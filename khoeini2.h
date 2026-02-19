

#ifndef PROJECT_SCRATCH_KHOEINI2_H
#define PROJECT_SCRATCH_KHOEINI2_H
#include<bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <cstdint>
using namespace std;
enum type_of_blocks {B_ineffective=0,B_wait_secs=1,B_wait_until=2,B_stop=3
    ,B_repeat_beg=4,B_repeat_end=5,B_forever_beg=6
    ,B_forever_end=7,B_if_beg=8,B_else=9,B_if_end=10
    ,B_repeat_until_beg=11,B_repeat_until_end=12};
struct block {
    type_of_blocks type;
    int num=0;
    int cond=0;
    int jump_to_f=-1;
    int jump_to_s=-1;
};
struct repeat_f {
    int beg_num;
    int remain;
};
struct repeat_until_f {
    int beg_num;
};
struct engine_con {
    vector<repeat_f> repeat_stack;
    vector<repeat_until_f> repeat_until_stack;
bool is_running=false;
    int pc=0;
    bool debug_mode_pointer=false;
    bool is_waited=false;
    uint32_t wait_until_t=0;
     int watchdog_counter=0;
     int watchdog_max=1000;
    int visual_pc=-1;
    bool error_active=false;
    int error_pc=-1;
};
static bool turn_con_to_bool (int con) {
    return (con==1)?true:false;
}
static bool links_of_process(vector<block>& prog,string &error_text) {
    vector<int> if_idx_stack;
    vector<int> repeat_idx_stack;
    vector<int> forever_idx_stack;
    vector<int> repeat_until_idx_stack;
    for (int i=0;i<prog.size();i++) {
        block& cur = prog[i];
        if (cur.type==B_if_beg) {
            if_idx_stack.push_back(i);;
        }
        else if(cur.type=B_else) {
            if (if_idx_stack.empty()) {
                error_text="there is no (if) with this (else)!";
                return false;
            }
            int if_beg=if_idx_stack.back();
            prog[if_beg].jump_to_s=i+1;
        }
        else if (cur.type==B_if_end) {
            if (if_idx_stack.empty()) {
                error_text="there is no (if) with this (end)!";
                return false;
            }
            int if_beg=if_idx_stack.back();
            if_idx_stack.pop_back();
            if (prog[if_beg].jump_to_s==-1) {
                prog[if_beg].jump_to_f=i+1;
            }
            for (int j=if_beg;j<i;j++) {
                if (prog[j].type==B_else) {
                    prog[j].jump_to_f=i+1;
                }
            }
        }
        else if (cur.type==B_repeat_beg) {
            repeat_idx_stack.push_back(i);
        }
        else if (cur.type==B_repeat_end) {
            if (repeat_idx_stack.empty()) {
                error_text="there is no (repeat_begin) with this (repeat_end)!";
                return false;
            }
            int begin_r=repeat_idx_stack.back();
            repeat_idx_stack.pop_back();
            prog[begin_r].jump_to_f=i;
            prog[i].jump_to_f=begin_r;
        }
        else if (cur.type==B_forever_beg) {
            forever_idx_stack.push_back(i);
        }
        else if (cur.type==B_forever_end) {
            if (forever_idx_stack.empty()) {
                error_text="there is no (forever_begin) with this (forever_end)!";
                return false;
            }
            int begin_f=forever_idx_stack.back();
            forever_idx_stack.pop_back();
            prog[i].jump_to_f=begin_f;
        }
        else if (cur.type==B_repeat_until_beg) {
            repeat_until_idx_stack.push_back(i);
        }
        else if (cur.type==B_repeat_until_end) {
            if (repeat_until_idx_stack.empty()) {
                error_text="there is no (repeat_until_begin) with this (repeat_untilr_end)!";
                return false;
            }
            int begin_r=repeat_until_idx_stack.back();
            repeat_until_idx_stack.pop_back();
            prog[i].jump_to_f=begin_r;
            prog[begin_r].jump_to_f=i;
        }
    }
    if (!if_idx_stack.empty()) {
        error_text="there is no (if_end) with this (if)!";
        return false;
    }
    if (!repeat_idx_stack.empty()) {
        error_text="there is no (repeat_end) with this (repeat_begin)!";
        return false;
    }
    if (!forever_idx_stack.empty()) {
        error_text="there is no (forever_end) with this (forever_begin)!";
        return false;
    }
    if (!repeat_until_idx_stack.empty()) {
        error_text="there is no (repeat_until_end) with this (repeat_until_begin)!";
        return false;
    }
    return true;
}
static void run_a_block(vector<block> &prog,engine_con & st) {
    if (!st.is_running) {
        return;
    }
    if (st.pc<0||(st.pc>=(int)prog.size())) {
        st.is_running=false;
        return;
    }
    block& cur=prog[st.pc];
    switch (cur.type) {
        case B_ineffective: {
            st.pc+=1;
        }break;
        case B_wait_secs: {
            uint32_t now=SDL_GetTicks();
            st.is_waited=true;
            st.wait_until_t=now+(uint32_t)cur.num;
            st.pc+=1;
        }break;
        case B_wait_until: {
            if (turn_con_to_bool(cur.cond)) {
                st.pc+=1;
            }else{

            }
        }break;
        case B_stop: {
            st.is_running=false;
        }break;
        case B_repeat_beg: {
            repeat_f fr;
            fr.beg_num=st.pc;
            fr.remain=cur.num;
            st.repeat_stack.push_back(fr);
            st.pc+=1;
        }break;
        case B_repeat_end: {
            if (st.repeat_stack.empty()) {
                st.is_running=false;
                break;
            }
            repeat_f & top=st.repeat_stack.back();
            top.remain-=1;
            if (top.remain>0) {
                st.pc=prog[st.pc].jump_to_f+1;
            }else {
                st.repeat_stack.pop_back();
                st.pc+=1;
            }
        }break;
        case B_forever_beg: {
            st.pc+=1;
        }break;
        case B_forever_end: {
                st.pc=prog[st.pc].jump_to_f+1;
        }break;
            case B_if_beg: {
                bool c=turn_con_to_bool(cur.cond);
                if (c) {
                    st.pc+=1;
                }else {
                    if (cur.jump_to_s!=-1) {
                        st.pc=cur.jump_to_s;
                    }else {
                        st.pc=cur.jump_to_f;
                    }
                }
            }break;
            case B_else: {
                st.pc=cur.jump_to_f;
            }break;
            case B_if_end: {
                st.pc+=1;
            }break;
            case B_repeat_until_beg: {
                if (turn_con_to_bool(cur.cond)) {
                    st.pc=cur.jump_to_f+1;
                }else {
                    repeat_until_f fr;
                    fr.beg_num=st.pc;
                    st.repeat_until_stack.push_back(fr);
                    st.pc+=1;
                }
            }break;
            case B_repeat_until_end: {
                if (st.repeat_until_stack.empty()) {
                    st.is_running=false;
                    break;
                }
                int beg=prog[st.pc].jump_to_f;
                st.repeat_until_stack.pop_back();
                st.pc=beg;
            }break;
            default: {
                st.is_running=false;
            }break;
    }
}
static void performance_of_engine_in_each_frame(vector<block> &prog,engine_con & st,bool debug_mode_pressed) {
    if (!st.is_running) {
        return;
    }
    if (st.is_waited) {
        uint32_t now=SDL_GetTicks();
        if (now>=st.wait_until_t) {
            st.is_waited=false;
        }else {
            return;
        }
    }
    if (st.debug_mode_pointer) {
        if (!debug_mode_pressed) {
            return;
        }
        st.watchdog_counter=0;
        run_a_block(prog,st);
        return;
    }
    st.watchdog_counter=0;
    while (st.is_running) {
        st.watchdog_counter+=1;
        if (st.watchdog_counter>st.watchdog_max) {
            cerr<<"[watchdog] Possible infinite loop at pc="<<st.pc<<endl;
            st.is_running=false;
            break;
        }
        run_a_block(prog,st);
        if (st.is_waited) {
            break;
        }
    }
}
// grafic of this shit
static inline void scratch_background_color(Uint8& r, Uint8& g, Uint8& b,Uint8& a) {
    r=30;
    g=30;
    b=30;
    a=255;
}
static inline void control_block_color(Uint8& r,Uint8& g,Uint8& b,Uint8& a) {
    r=255;
    g=178;
    b=64;
    a=255;
}
static inline void control_ongoing_block_highlight(Uint8& r,Uint8& g,Uint8& b,Uint8& a) {
    r=255;
    g=210;
    b=120;
    a=255;
}
static inline void error_block_color(Uint8& r,Uint8& g,Uint8& b,Uint8& a) {
    r=220;
    g=60;
    b=60;
    a=255;
}
static inline const char* title_of_each_block(type_of_blocks t) {
    switch (t) {
        case B_wait_secs: {
            return"wait";
        }
        case B_wait_until: {
            return"wait until";
        }
        case B_stop: {
            return"stop all";
        }
        case B_repeat_beg: {
            return"repeat";
        }
        case B_repeat_end: {
            return"end repeat";
        }
        case B_forever_beg: {
            return"forever";
        }
        case B_forever_end: {
            return"end forever";
        }
        case B_if_beg: {
            return"if";
        }
        case B_else: {
            return"else";
        }
        case B_if_end: {
            return"end if";
        }
        case B_repeat_until_beg: {
            return"repeat until";
        }
        case B_repeat_until_end: {
            return"end repeat until";
        }
        default: {
            return"";
        }
    }
}
static inline void draw_text(SDL_Renderer* r,TTF_Font* font,const string& text,int x, int y,Uint8& tr,Uint8& tg, Uint8& tb) {
    if (!font) {
        return;
    }
    SDL_Color col{
        tr,tg,tb,255
    };
    SDL_Surface* s = TTF_RenderUTF8_Blended(font, text.c_str(), col);
    if (!s) {
        return;
    }
    SDL_Texture *t=TTF_RenderUTF8_Blended(font,text.c_str(),col);
    if (!t) {
        SDL_FreeSurface(s);
        return;
    }
    SDL_Rect ds{x,y,s->w,s->h};
    SDL_RenderCopy(r,t,nullptr,&ds);
    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);
}
static inline void draw_scratch_blocks(SDL_Renderer* ren,int x, int y,int w,int h,bool has_top_notch,bool has_bottom_tab,bool highlight,bool error, const string & text,TTF_Font* font) {
    Uint8 br,bg,bb,ba;
    if (error) {
        error_block_color(br,bg,bb,ba);
    }else if (highlight) {
        control_block_color(br,bg,bb,ba);
    }else {
        control_block_color(br,bg,bb,ba);
    }
int r=12;
    roundedBoxRGBA(ren,x,y,x+w,y+h,r,br,bg,bb,ba);
    if (has_top_notch) {
        Uint8 rr,rg,rb,ra;
        scratch_background_color(rr,rg,br,bg);
        int notch_w=52;
        int notch_h=12;
        int notch_x=x+34;
        int notch_y=y-1;
        roundedBoxRGBA(ren,notch_x,notch_y,notch_x+notch_w,notch_y+notch_h,6,rr,rg,rb,ra);
    }
if (has_bottom_tab) {
    int tab_w=62;
    int tab_h=14;
    int tab_x=x+30;
    int tab_y=y+h-2;
    roundedBoxRGBA(ren,tab_x,tab_y,tab_x+tab_w,tab_y+tab_h,7,br,bg,bb,ba);
}
    Uint8 orr,org,orb,ora;
    orr=(Uint8)std::max(0,(int)br-40);
    org=(Uint8)std::max(0,(int)bg-40);
    orb=(Uint8)std::max(0,(int)bb-40);
    ora=255;
    roundedBoxRGBA(ren,x,y,x+w,y+h,r,orr,org,orb,ora);
    draw_text(ren,font,text,x+18,y+10,255,255,255);
}
static inline void draw_control_main_script(SDL_Renderer* ren,TTF_Font* font,const vector<block>& prog,const engine_con & st,int start_x,int start_y) {
    int y=start_y;
    int indent=0;
    const int block_w=260;
    const int block_h=44;
    const int gap=8;
    const int indent_p=24;
    for (int i=0;i<(int)prog.size();i++) {
        const block& b=prog[i];
        if (b.type==B_repeat_end||b.type==B_if_end||b.type==B_forever_end||b.type==B_repeat_until_end) {
            indent=std::max(0,indent-1);
        }
        bool highlight=(st.visual_pc==i);
        bool error=(st.error_active&&st.error_pc==i);
        bool hasTopNotch=true;
        bool hasBottomTab=true;
        if (b.type==B_repeat_end||b.type==B_if_end||b.type==B_forever_end||b.type==B_repeat_until_end) {
            hasBottomTab=false;
        }
        string label=title_of_each_block(b.type);
        if (b.type==B_wait_secs) {
            label+="("+to_string(b.num)+"ms)";
        }
        if (b.type==B_repeat_beg) {
            label+="("+to_string(b.num)+")";
        }
        if (b.type==B_wait_until||b.type==B_if_beg||b.type==B_repeat_until_beg) {
            label+="(cond="+to_string(b.cond)+")";
        }
        int x=start_x+(indent*indent_p);
        draw_scratch_blocks(ren,x,y,block_w,block_h,hasTopNotch,hasBottomTab,highlight,error,label,font);
        y+=block_h+gap;
        if (b.type==B_repeat_beg||b.type==B_if_beg||b.type==B_forever_beg||b.type==B_repeat_until_beg) {
            indent+=1;
        }
        if (b.type==B_else) {

        }
    }
}
static inline void clear_code_panel(SDL_Renderer* r) {
    Uint8 rr,rg,rb,ra;
    scratch_background_color(rr,rg,rb,ra);
    SDL_SetRenderDrawColor(r, rr,rg,rb,ra);
    SDL_RenderClear(r);
}
#endif