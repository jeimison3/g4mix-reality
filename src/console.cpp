#include "console.hpp"
#include "exceptions.h"
#include "joystick.hpp"
#include <string>

// #define _DEBUG_COUT

ConsoleCurses::ConsoleCurses(){
    
    initscr();
    start_color();
    int rows,cols;
    getmaxyx(stdscr,rows,cols);

    this->logw = newwin(8, cols, rows-8, 0);
    box(this->logw, 0 , 0);

    wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(this->logw, '*', '*', '*', '*', '*', '*', '*', '*');
    mvwprintw(this->logw, 1, 0, "Log iniciado.\n");
    scrollok(this->logw, true);
    
    wrefresh(stdscr);
    wrefresh(this->logw);
    // newwin(nlines, ncols, y0, x0);
}

void ConsoleCurses::dropJoy(void* joyv){
    for(int i=0; i < this->joyWindows.size(); i++){
        if(this->joyWindows[i].first == joyv){
            // for(int i=0; i<getmaxy(this->joyWindows[i].second); i++)
            //     this->clearLine(this->joyWindows[i].second, i);

            delwin(this->joyWindows[i].second);
            this->joyWindows.erase(this->joyWindows.begin()+i);
        }
    }
}

WINDOW* ConsoleCurses::joyWindow(void* joyv){
    Joystick * joy = (Joystick*)joyv;
    
    for(int i=0; i < this->joyWindows.size(); i++){
        if(this->joyWindows[i].first == joyv)
            return this->joyWindows[i].second;
    }

    int rows,cols;
    getmaxyx(stdscr,rows,cols);
    int qtdJoys = this->joyWindows.size();
    int colsJoy = 7*3;
    // [001: O ]
    // NLINES, NCOLS, y, x
    WINDOW* newW = newwin(rows - getmaxy(this->logw), colsJoy, 0, qtdJoys*colsJoy);
    
    wprintw(newW, (std::string(SDL_JoystickName(joy->pControle()))+"\n").c_str());
    // mvwprintw(newW, 0, 0, );

    this->joyWindows.push_back( std::pair<void*,WINDOW*>(joyv, newW) );
    return newW;
}


WINDOW* ConsoleCurses::clearLine(WINDOW* w, int y){
    int C = getmaxx(w);
    for(int j=0;j<C; j++){
        mvwdelch(w, y, j);
    }
    return w;
}

ConsoleCurses& ConsoleCurses::operator<<(std::string s){
    if(!this->logw) {FUNCTION_WARN("LogWindow nao instanciado.", *this)}
    #ifndef _DEBUG_COUT
    // const char * carac = s.c_str();

    // wmove(this->logw, getcury(this->logw), 0);
    // while(*carac){
    //     if(*carac == '\n') wmove(this->logw, getcury(this->logw)+1, 0);
    //     waddch(this->logw, *carac);
    //     carac++;
    // }
    if(getcury(this->logw) >= getmaxy(this->logw)-1){
        wclear(this->logw);
        wborder(this->logw, '*', '*', '*', '*', '*', '*', '*', '*');
        wmove(this->logw, 1,0);
    }
    wprintw(this->logw, s.c_str());
    wrefresh(this->logw);
    #else
    std::cout << s;
    #endif

    return *this;
}
ConsoleCurses& ConsoleCurses::operator<<(char c){
    if(!this->logw) {FUNCTION_WARN("LogWindow nao instanciado.", *this)}
    #ifndef _DEBUG_COUT
    char s[2] = {c, '\0'};
    wprintw(this->logw, s);
    wrefresh(this->logw);
    #else
    std::cout << c;
    #endif

    return *this;
}

ConsoleCurses& ConsoleCurses::operator<<(char* str){
    if(!this->logw) {FUNCTION_WARN("LogWindow nao instanciado.", *this)}
    #ifndef _DEBUG_COUT
    if(getcury(this->logw) >= getmaxy(this->logw)-1){
        wclear(this->logw);
        wborder(this->logw, '*', '*', '*', '*', '*', '*', '*', '*');
        wmove(this->logw, 1,0);
    }
    wprintw(this->logw, str);
    wrefresh(this->logw);
    #else
    std::cout << str;
    #endif

    return *this;
}

ConsoleCurses& ConsoleCurses::operator<<(int v){
    if(!this->logw) {FUNCTION_WARN("LogWindow nao instanciado.", *this)}
    #ifndef _DEBUG_COUT
    wprintw(this->logw, std::to_string(v).c_str());
    wrefresh(this->logw);
    #else
    std::cout << v;
    #endif

    return *this;
}

ConsoleCurses& ConsoleCurses::operator<<(uint32_t v){
    if(!this->logw) {FUNCTION_WARN("LogWindow nao instanciado.", *this)}
    #ifndef _DEBUG_COUT
    wprintw(this->logw, std::to_string(v).c_str());
    wrefresh(this->logw);
    #else
    std::cout << v;
    #endif

    return *this;
}

ConsoleCurses::~ConsoleCurses(){
    std::cout << "LIBERANDO NCURSES";
    delwin(this->logw);
    delwin(stdscr);
}
