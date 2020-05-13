#ifndef __SDLKIT_PERIFERICOS
#define __SDLKIT_PERIFERICOS

#include <iostream>

#include "SDL2/SDL.h"
#include "tela.hpp"
#include "joystick.hpp"

class Perifericos{
  private:
    Tela* tela;
    bool telaInit;

    Joystick* controle;
    bool controleInit = false;

    Uint32 timeout;

  public:
    Tela* pTela();
    Joystick* pControle();

    Perifericos();

    bool Init();

    void OnLoop();

    void OnEvent(SDL_Event* Evento);
};

#endif