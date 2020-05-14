#ifndef __SDLKIT_RENDER
#define __SDLKIT_RENDER

#include "SDL2/SDL.h"
#include <functional>
#include <thread>
#include "tela.hpp"

class Renderizador{
  protected:
  private:

  public:
    std::function<void(SDL_Renderer*, Tela*)> func = nullptr;
    SDL_Renderer* rend;
    Renderizador(SDL_Renderer* rend, Tela* tela);
    void setLoop(std::function<void(SDL_Renderer*)> func);
    std::thread doRender();
};

#endif