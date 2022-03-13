#ifndef __SDLKIT_SDLUtil
#define __SDLKIT_SDLUtil

#include <iostream>
#include "SDL2/SDL.h"
#include "console.hpp"

class SDLUtilClass {
  private:
  public:
    ConsoleCurses * cout;
    SDLUtilClass();
    ~SDLUtilClass();
    static bool setup();
    void Termina(std::string motivo = "");
};

extern SDLUtilClass * SDLUtil;

#endif