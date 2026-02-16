
#ifndef PROJECT_SCRATCH_KHOEINI1_H
#define PROJECT_SCRATCH_KHOEINI1_H
#include<bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <conio.h>
#include <fstream>
#include <sstream>
using namespace std;
enum levellog{log_info=0,log_warning=1,log_error=2};
struct info_log {
    int cikl;
    int line;
    string cmd;
    string action;
    string data;
    levellog level;
};
static levellog min_level_log(log_info);
static const int max_num_logs=3000;
static const string leveltostr(levellog lvl){
    if(lvl==log_info) {
        return "[INFO]";
    }
    else if(lvl==log_warning) {
        return "[WARNING]";
    }
    else if(lvl==log_error) {
        return "[ERROR]";
    }
}
static string format(const info_log& logg) {
    ostringstream ss;
    ss<<"[Cycle:"<<(logg.cikl<0?0:logg.cikl)<<"]"<<"[Line:"<<(logg.line<0?0:logg.line)<<"]"<<"[CMD:"<<logg.cmd<<"]"<<leveltostr(logg.level)<<"->"<<logg.action;
    if (!(logg.data.empty())) {
        ss<<"->"<<logg.data;
    }
    return ss.str();
}
static vector<info_log> logs;
static const int max_log_level=3000;
static void push_log(const info_log& item) {
    if (item.level<min_level_log) {
        return;
    }
    logs.push_back(item);
    if (logs.size()>max_log_level) {
        logs.erase(logs.begin());
    }
}
static void save_log_in_file() {
    ofstream file("log_saver.txt");
    for (const auto& log : logs) {
        file<<format(log);
    }
}
static int clamp(int value, int min_value, int max_value) {
    return std::max(min_value, std::min(max_value, value));
}
struct display_pos {
    int maxx,maxy,minx,miny;
};
struct position {
    int x,y;
};
static bool is_calmp(position current,position delta, display_pos t,int cycle_num,int line_num) {
    position next{current.x+delta.x,current.y+delta.y};
    int final_x=clamp(next.x , t.minx ,t.maxx);
    int final_y=clamp(next.y,t.miny,t.maxy);
    if (final_x!=next.x||final_y!=next.y) {
        info_log l;
        l.cikl=cycle_num;
        l.line=line_num;
        l.cmd="MOVE";
        l.action="there was problem with boundary check!";
        l.level=log_warning;
        static ostringstream ss;
        ss<<"Wanted("<<next.x<<","<<next.y<<") -> "<<"Clamped("<<final_x<<","<<final_y<<")";
        l.data=ss.str();
        push_log(l);
        return true;
    }
    return false;
}
static bool daedly_error_bool=false;
static string deadly_error_text="proccess halted!";
static int watchdog_counter=0;
static int watchdog_max=1000;
static void watchdog_reset() {
    watchdog_counter=0;
}static bool is_watchdog_okay(int cycle_num,int line_num, string cmd) {
    watchdog_counter++;
    if (watchdog_counter>=watchdog_max) {
        info_log l;
        l.cikl=cycle_num;
        l.line=line_num;
        l.cmd=cmd;
        l.action="Watchdog: possible infinite loop!";
        l.data="proccess halted!";
        l.level=log_error;
        push_log(l);

        return false;
    }
    return true;
}
enum help_menu_tabs{overview_tab,logger_tab,safety_tab};
struct help_menu_button {
    SDL_Rect r;
    string text;
    help_menu_tabs tab;
};
static SDL_Renderer* khoeini_ren=nullptr;
static TTF_Font* khoeini_font=nullptr;
static int g_winW=0,g_winH=0;
static bool g_helpVisible=false;
static help_menu_tabs g_helpTab=overview_tab;










#endif