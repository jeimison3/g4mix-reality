#include "sdlutil.hpp"

bool SDLUtil::Init(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
      std::cout << "CODIGO: " << SDL_GetError() << std::endl;
      Termina();
      return false;
    }
    return true;
}

void SDLUtil::Termina(std::string motivo){
  if(motivo!="") std::cout << "[FATAL] " << motivo << std::endl;
    SDL_Quit();
}