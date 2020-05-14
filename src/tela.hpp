#ifndef __SDLKIT_TELA
#define __SDLKIT_TELA

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "sdlutil.hpp"
#include "Frequent.hpp"

class Tela{
  private:
      int WIN_HEIGHT, WIN_WIDTH;
      SDL_Window* Janela;
      SDL_Renderer* Render;
      Frequent* FPS;

  public:
    Tela(int Width, int Heigth, int FrameRate);
    bool Init();
    void OnLoop();
    void OnEvent(SDL_Event* Evento);
    void drawTxt(std::string txt, TTF_Font* fonte, int x, int y, int w, int h);
};

#endif