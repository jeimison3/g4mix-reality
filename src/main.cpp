#include <iostream>
#include <vector>

using namespace std;

#include <SDL2/SDL.h>

#include "classes.h"
#include "sdlutil.hpp"

#include "joystick.hpp"
#include "tela.hpp"

#include "perifericos.hpp"

int main(){
    //Inicializa módulos do SDL:

    // 1
    SDLUtil::Init();

    // 2
    Perifericos* perif = new Perifericos();

    bool _VAR_SDL_INTERRUPT = false;
    while(!_VAR_SDL_INTERRUPT){

      bool encerrar = false;

        perif->OnLoop();

        SDL_Event e;
        while(SDL_PollEvent(&e)){
          perif->OnEvent(&e);
            switch(e.type){
                case SDL_KEYDOWN:
                    cout << "UCODE: " << e.key.keysym.scancode << endl;
                    break;

                case SDL_QUIT:
                    _VAR_SDL_INTERRUPT = true;
                    break;
            }
        }

    }



      SDLUtil::Termina("SDLKIT terminado");
    return 0;
}
