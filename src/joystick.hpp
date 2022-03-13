// #include <iostream>
#ifndef __SDLKIT_JOYSTICK
#define __SDLKIT_JOYSTICK

#include <iostream>
#include <vector>
#include <string>
#include "SDL2/SDL.h"
#include "classes.h"
#include "sdlutil.hpp"
#include "console.hpp"

class Joystick{
  private:
    SDL_Joystick* Controle;
    bool WORKING;

    std::vector<Botao> Botoes;
    std::vector<Point2f> Analogicos;
    std::vector<int> Hats;
    std::vector<Point2f> Balls;

    Uint32 _DEBUG_timeout;
    int _DEBUG_maxButtonShow;

  public:
    Joystick();
    SDL_Joystick* pControle();

    void dumpInConsole(ConsoleCurses * cc);

    bool isWorking();

    /*
    SDL_JOYSTICK_POWER_
    UNKNOWN | EMPTY | LOW | MEDIUM | FULL | WIRED | MAX
    */
    SDL_JoystickPowerLevel joystickPower();

    bool Init();

    bool setup();

    void setup_vars();

    void OnLoop();

    void OnEvent(SDL_Event* Evento);

    void _debug_TablesStatus();


};

#endif