
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
static SDL_Renderer* helpren=nullptr;
static TTF_Font* helpfont=nullptr;
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
static void math_warn(int cycle_num,int line_num,const char* cmd,const char* action,const string &data) {
    info_log l;
    l.cikl=cycle_num;
    l.line=line_num;
    l.cmd=cmd?cmd:"Math";
    l.action=action;
    l.data=data;
    l.level=log_warning;
    push_log(l);
}
static bool safe_divide(double a,double b, double & c, int cycle_num,int line_num,const char* cmd) {
    if (b==0.0) {
        ostringstream ss;
        ss<<"a="<<a<<"/b="<<b;
        ss<<"divide by zero";
        math_warn(cycle_num,line_num,cmd,"Math error: division by zero",ss.str());
        return false;
    }
    c=a/b;
    return true;
}
static bool safe_sqrt(double value,double &c,int cycle_num,int line_num,const char* cmd) {
    if (value<0.0) {
        ostringstream ss;
        ss<<"value="<<value<<"<0!";
        math_warn(cycle_num,cycle_num,cmd,"Math error: sqrt of negative value",ss.str());
        return false;
    }
    c=sqrt(value);
    return true;
}
static bool deadly_error_bool=false;
static vector<string> deadly_error_text;
static int watchdog_counter=0;
static int watchdog_max=1000;
static void watchdog_reset() {
    watchdog_counter=0;
}static bool is_watchdog_okay(int cycle_num,int line_num, string cmd) {
    watchdog_counter++;
    if (watchdog_counter>=watchdog_max) {
        deadly_error_bool=true;
        string deadly_massage="ERROR: Watchdog limit exceeded! | Possible infinite loop or wrong jump. | Press ESC to exit.";
        deadly_error_text.push_back(deadly_massage);
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
static bool is_deadly_stop() {
    return deadly_error_bool;
}// ino gozashtam ager be kar omad badan estefadash konam.
enum help_menu_tabs{Overview_tab,Logger_tab,Step_tab,Safety_tab};
struct help_menu_button {
    SDL_Rect r;
    const char* text;
    help_menu_tabs tab;
};
static help_menu_button button_in_dispaly [4];
static bool helpVisible=false;
static help_menu_tabs first_helpTab=Overview_tab;

static bool* debug_mode_pointer=nullptr;
static bool* step_by_step_mode_pointer=nullptr;
static bool* ask_for_a_step_pointer=nullptr;
static void quantification_for_step_pointerns( bool* ask_for_a_step,bool* step_by_step_mode,bool* debug_mode) {
    debug_mode_pointer=debug_mode;
    ask_for_a_step_pointer=ask_for_a_step;
    step_by_step_mode_pointer=step_by_step_mode;
}
int win_h=0;
int win_w=0;
static void help_menu_g(SDL_Renderer* renderer,int W,int H) {
    helpren=renderer;
    win_h=H;
    win_w=W;
}
static bool help_menu_font_open( const char* font_path,int font_size) {
    helpfont=TTF_OpenFont(font_path,font_size);
    return (helpfont!=nullptr);
}
static void help_menu_font_close() {
    if (helpfont!=nullptr) {
        TTF_CloseFont(helpfont);
        helpfont = nullptr;
    }
}
static void info_to_tab_buttons() {
    int delt=10,L_w=170,L_h=40;
    int x=10,y=10;                              
    button_in_dispaly[0]={SDL_Rect{x,y,L_w,L_h},"Overview",Overview_tab};
    x+=L_w+delt;
    button_in_dispaly[1]={SDL_Rect{x,y,L_w,L_h},"Logger",Logger_tab};
    x+=L_w+delt;
    button_in_dispaly[2]={SDL_Rect{x,y,L_w,L_h},"Step_By_Step",Step_tab};
    x+=L_w+delt;
    button_in_dispaly[3]={SDL_Rect{x,y,L_w,L_h},"Safety",Safety_tab};
} 
static bool is_cursor_in_Rect(int mx,int my,SDL_Rect r){
    return ((mx>=r.x&&mx<r.x+r.w)&&(my>=r.y&&my<r.y+r.h));
}
static SDL_Texture* auxiliary_for_Render_Text(const char* text, const SDL_Color c,int& t_w,int& t_h){
    SDL_Surface* s=TTF_RenderUTF8_Blended(helpfont, text,c);
    if(!s) {
        return nullptr;
    }
    SDL_Texture* t=SDL_CreateTextureFromSurface(helpren,s);
    t_w=s->w;
    t_h=s->h;
    SDL_FreeSurface(s);
    return t;
}
static void write_text_left(const char* text,int x,int y) {
    const SDL_Color r{255,255,255,255};
    int T_H=0;
    int T_W=0;
    SDL_Texture* T=auxiliary_for_Render_Text(text,r,T_W,T_H);
    if(!T) {
        return;
    }
    SDL_Rect S{x,y,T_W,T_H};
    SDL_RenderCopy(helpren,T,nullptr,&S);
    SDL_DestroyTexture(T);
}
static void write_text_center(const char* text,SDL_Rect R) {
    const SDL_Color r{255,255,255,255};
    int T_H=0;
    int T_W=0;
    SDL_Texture* T=auxiliary_for_Render_Text(text,r,T_W,T_H);
    if(!T) {
        return;
    }
    SDL_Rect S{R.x+(R.w-T_W)/2,R.y+(R.h-T_H)/2,T_W,T_H};
    SDL_RenderCopy(helpren,T,nullptr,&S);
    SDL_DestroyTexture(T);
}
static int logscroll=0;
static void handling_events(SDL_Event e) {
    if (!helpVisible) {
        return;
    }
    if (e.type==SDL_MOUSEBUTTONDOWN&&e.button.button==SDL_BUTTON_LEFT) {
        int x_mouse=e.button.x;
        int y_mouse=e.button.y;
        for (int i=0;i<4;i++) {
            if (is_cursor_in_Rect(x_mouse,y_mouse,button_in_dispaly[i].r)) {
                first_helpTab=button_in_dispaly[i].tab;
                return;
            }
        }
    }
    if (e.type==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_SPACE) {
        if (first_helpTab==Step_tab&&ask_for_a_step_pointer) {
            *ask_for_a_step_pointer=true;
        }
    }

    if (e.type==SDL_MOUSEWHEEL) {
        logscroll-=e.wheel.y*5;
        logscroll=std::max(0,logscroll);
    }
}
static int last_step_cycle=-1;
static int last_step_line=-1;
static string last_step_cmd;
static string last_step_action;
static string last_step_data;
static levellog last_step_level=log_info;
static void help_for_storing_last_step(const info_log& t) {
    last_step_cycle=t.cikl;
    last_step_line=t.line;
    last_step_cmd=t.cmd;
    last_step_action=t.action;
    last_step_data=t.data;
    last_step_level=t.level;
}
static void render_overview_tab(int x,int y) {
    write_text_left("Help Menu",x,y);
    y+=26;
    write_text_left("----> Logger: black box log",x,y);
    y+=18;
    write_text_left("----> Step_By_Step: press SPACE for one command",x,y);
    y+=18;
    write_text_left("----> Safety: clamp + watchdog",x,y);
}
static void render_step_by_step_mode_tab(int x,int y) {
    write_text_left("Step-by-Step",x,y);
    y+=26;
    write_text_left("SPACE to show one command",x,y);
    y+=18;
    if (debug_mode_pointer&& step_by_step_mode_pointer) {
        write_text_left(*debug_mode_pointer?"Debug:ON":"Debug:OFF",x,y);
        y+=18;
        write_text_left(*step_by_step_mode_pointer?"Step:ON":"Step:OFF",x,y);
        y+=18;
    }
    if (last_step_line>=0) {
        ostringstream ss;
        ss.str("");
        ss.clear();
        ss<<"last cycle: "<<last_step_cycle<<"| Line: "<<last_step_line;
        string l1=ss.str();
        write_text_left(l1.c_str(),x,y);
        y+=18;
        ss.str("");
        ss.clear();
        ss<<"CMD: "<<last_step_cmd<<leveltostr(last_step_level);
        string l2=ss.str();
        write_text_left(l2.c_str(),x,y);
        y+=18;
        ss.str("");
        ss.clear();
        ss<<"Action: "<<last_step_action;
        string l3=ss.str();
        write_text_left(l3.c_str(),x,y);
        y+=18;
        if (!last_step_data.empty()) {
            ss.str("");
            ss.clear();
            ss<<"Data: "<<last_step_data;
            string l4=ss.str();
            write_text_left(l4.c_str(),x,y);
            y+=18;
        }
    }
}
static void render_safety_tab(int x,int y) {
    write_text_left("Safety",x,y);
    y+=26;
    write_text_left("Clamp: keep inside stage!",x,y);
    y+=18;
    write_text_left("Watchdog: prevent freeze!",x,y);
    y+=18;
    write_text_left("Observe the calculation error!",x,y);
}
static void render_log_tab(int x,int y,SDL_Rect panel_log) {
    write_text_left("Logger:you can scrrol with your mouse wheel",x,y);
    y+=26;
    int line_h=18;
    int max_num_og_logline=(panel_log.h-50)/line_h;
    for (int i=0;i<max_num_og_logline;i++) {
        int num_line_in_pannel=i+logscroll;
        if (num_line_in_pannel>=(int)logs.size()) {
            string s=format(logs[num_line_in_pannel]);
            write_text_left(s.c_str(),x,y+i*line_h);
        }
    }
}
static void main_help_menu_render() {
    if (!helpVisible) {
        return;
    }
    SDL_SetRenderDrawBlendMode(helpren,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(helpren,0,0,0,200);
    SDL_Rect back_ground{0,0,win_w,win_h};
    SDL_RenderFillRect(helpren,&back_ground);
    for (int i=0;i<4;i++) {
        bool avtive_tab=(button_in_dispaly[i].tab==first_helpTab);
        SDL_SetRenderDrawColor(helpren,avtive_tab?60:30,avtive_tab?60:30,avtive_tab?90:60,255);
        SDL_RenderFillRect(helpren,&button_in_dispaly[i].r);
        SDL_SetRenderDrawColor(helpren,220,220,220,255);
        SDL_RenderDrawRect(helpren,&button_in_dispaly[i].r);
        write_text_center(button_in_dispaly[i].text,button_in_dispaly[i].r);
    }
    SDL_Rect panel{10,60,win_w-20,win_h-70};
    SDL_SetRenderDrawColor(helpren,15,15,20,235);
    SDL_RenderFillRect(helpren,&panel);
    SDL_SetRenderDrawColor(helpren,220,220,220,235);
    SDL_RenderDrawRect(helpren,&panel);
    int x=panel.x+12;
    int y=panel.y+12;
    if (first_helpTab==Overview_tab) {
        render_overview_tab(x,y);
    }
    else if (first_helpTab==Step_tab) {
        render_step_by_step_mode_tab(x,y);
    }
    else if (first_helpTab==Logger_tab) {
        render_log_tab(x,y,panel);
    }else {
        render_safety_tab(x,y);
    }
}
static void render_deadly_display() {
    if (!deadly_error_bool) {
        return;
    }
    SDL_SetRenderDrawBlendMode(helpren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(helpren,0,0,0,200);
    SDL_Rect back_g{0,0,win_w,win_h};
    SDL_RenderFillRect(helpren,&back_g);
    SDL_Color white{255,255,255,255};
    int total_h=0;
    int max_W=0;
    vector<int>wide,hight;
    wide.reserve(deadly_error_text.size());
    hight.reserve(deadly_error_text.size());
    for (const auto &line:deadly_error_text) {
        int tw=0;
        int th=0;
        SDL_Texture* d=auxiliary_for_Render_Text(line.c_str(),white,tw,th);
        if (d) {
            SDL_DestroyTexture(d);
        }
        wide.push_back(tw);
        hight.push_back(th);
        total_h+=10+th;
        if (tw>max_W) {
            max_W=tw;
        }
        if (!(deadly_error_text.empty())) {
            total_h-=10;
        }
        int s=(win_h-total_h)/2;
        int y=s;
        for (size_t i=0;i<deadly_error_text.size();i++) {
            int w=0;
            int h=0;
            SDL_Texture* q=auxiliary_for_Render_Text(deadly_error_text[i].c_str(),white,w,h);
            if (!q) {
                y+=hight[i]+10;
                continue;
            }
            SDL_Rect massage{(win_w-w)/2,y,w,h};
            SDL_RenderCopy(helpren,q,nullptr,&massage);
            SDL_DestroyTexture(q);
            y+=h+10;
        }
    }
}




#endif
