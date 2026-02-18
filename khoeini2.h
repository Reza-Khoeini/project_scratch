

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
};
static bool turn_con_to_bool (int con) {
    return (con==1)?true:false;
}
static bool links_of_process(vector<block>& prog,string error_text) {
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
















#endif