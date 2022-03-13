#ifndef __G4MIX_CONSOLE
#define __G4MIX_CONSOLE
#include <iostream>
#include <ncurses.h>
#include <vector>

class ConsoleCurses{
    private:
    WINDOW * logw;
    std::vector<std::pair<void*,WINDOW*>> joyWindows;

    public:
    ConsoleCurses();
    ~ConsoleCurses();

    void addLog(std::string s);
    WINDOW* joyWindow(void* joy);
    void dropJoy(void* joy);

    WINDOW* clearLine(WINDOW* w, int y);

    ConsoleCurses& operator<<(std::string txt);
    ConsoleCurses& operator<<(char c);
    ConsoleCurses& operator<<(char* str);
    ConsoleCurses& operator<<(int v);
    ConsoleCurses& operator<<(uint32_t v);
};

#endif