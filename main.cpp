#include <iostream>
#include <SDL.h>

using namespace std;

#include "sdlutil.cpp"

int main(){
    iniciaSDL();
    
    /*SDL_Window* window = SDL_CreateWindow("A Window",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
    SDL_WINDOW_SHOWN); // SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN */
    
    SDL_Window* wind;
    SDL_Renderer* ren;    
    if (!constroiInterface(wind,ren)) terminaSDL();
    
    
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    
    
    bool encerrar = false;
    do{
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                encerrar=true;
            }
        }
    }while(!encerrar);
    
    
    
    terminaSDL();
    return 0;
}
