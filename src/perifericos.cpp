#include "perifericos.hpp"
#include <string>

Tela* Perifericos::pTela(){ return this->tela; }
Joystick* Perifericos::pControle(){ return this->controle; }

Perifericos::Perifericos(){

  this->tela = (Tela*) new Tela(640, 480, 60);
  this->telaInit = false;

  this->controle = (Joystick*) new Joystick();
  this->controleInit = false;

  //Inicializa periféricos
  Uint32 timeout = SDL_GetTicks(); //Inicializa tempo para repetição
  bool resu=true;
  do{
    SDL_JoystickUpdate();
    if(SDL_TICKS_PASSED(SDL_GetTicks(),timeout)){
      timeout = SDL_GetTicks()+100; //Verificando a cada 100ms
      resu = Init(); //Reiniciando periféricos
    }
  } while(!resu);
}

bool Perifericos::Init(){
  
  if(!this->telaInit) this->telaInit = tela->Init();
  if(!this->controleInit) this->controleInit = controle->Init();

  if(!this->telaInit) *SDLUtil->cout << "[Tela] Janela ou renderizador apresentando falhas.\n";
  if(!this->controleInit) *SDLUtil->cout << "[Controle] Controle não encontrado.\n";

  bool resumo = this->telaInit && this->controleInit;

  if(!resumo) *SDLUtil->cout << "[Perif.] Repetindo." << " Joysticks= " << std::to_string(SDL_NumJoysticks()) << '\n';
  else *SDLUtil->cout << "[Perif.] Inicializado.\n";

  return resumo;
}

void Perifericos::OnLoop(){
  //if(this->telaInit) this->tela->OnLoop();
  if(this->controleInit) this->controle->OnLoop();
}

void Perifericos::OnEvent(SDL_Event* Evento){
  if(this->telaInit) this->tela->OnEvent(Evento);
  if(this->controleInit) this->controle->OnEvent(Evento);
}

