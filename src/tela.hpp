#ifndef __SDLKIT_TELA
#define __SDLKIT_TELA

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include <thread>
#include <vector>
#include "sdlutil.hpp"
#include "Frequent.hpp"
#include <functional>
//#include "Renderizador.hpp"

class Renderizador;

class Tela{
  protected:
      //std::thread thread;
      SDL_Thread *thread;

      

  public:
    std::vector<Renderizador*> renderizadores;

    bool ready = false;
    int WIN_HEIGHT, WIN_WIDTH;
    SDL_Window* Janela;
    SDL_Renderer* Render;
    Frequent* FPS;

    Tela(int Width, int Heigth, int FrameRate);
    bool Init();
    void OnEvent(SDL_Event* Evento);
    void drawTxt(std::string txt, TTF_Font* fonte, int x, int y);
};

class Renderizador{
  protected:
  private:

  public:
    Tela* tela;
    std::function<void(Tela*)> func = nullptr;
    Renderizador(Tela* tela);
    void setLoop(std::function<void(Tela*)> func);
    SDL_Thread* doRender();
};

#endif