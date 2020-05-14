#ifndef __SDLKIT_SDLUtil
#define __SDLKIT_SDLUtil

#include <iostream>
#include "SDL2/SDL.h"

class SDLUtil{
  public:
    static bool Init();
    static void Termina(std::string motivo = "");
    static void LOG_Debug(std::string text = "");
};

#endif