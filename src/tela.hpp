#ifndef __SDLKIT_TELA
#define __SDLKIT_TELA

#include "SDL2/SDL.h"
#include "sdlutil.hpp"

class Tela{
  private:
      SDL_Window* Janela;
      SDL_Renderer* Render;

  public:
    Tela();
    bool Init();
    void OnLoop();
    void OnEvent(SDL_Event* Evento);
};

#endif