#include "sdlutil.hpp"

SDLUtilClass * SDLUtil;

SDLUtilClass::SDLUtilClass(){
  this->cout = new ConsoleCurses();
}

SDLUtilClass::~SDLUtilClass(){
  SDLUtil->Termina("EndClass.");
}

bool SDLUtilClass::setup(){
  SDLUtil = new SDLUtilClass();
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    *SDLUtil->cout << "CODIGO: " << SDL_GetError();
    SDLUtil->Termina("cannot SDL_INIT_EVERYTHING");
    return false;
  }
  
  return true;
}

void SDLUtilClass::Termina(std::string motivo){
  SDL_Quit();
  if(motivo!="") std::cout << "[FATAL] " << motivo << std::endl;
}