#include "joystick.hpp"

Joystick::Joystick(){
  this->WORKING = false;
  this->_DEBUG_timeout =  SDL_GetTicks();
  this->_DEBUG_maxButtonShow = 0;
}

SDL_Joystick* Joystick::pControle(){ return this->Controle; }

bool Joystick::isWorking(){ return SDL_JoystickGetAttached(this->Controle); }

/*
SDL_JOYSTICK_POWER_
UNKNOWN | EMPTY | LOW | MEDIUM | FULL | WIRED | MAX
*/
SDL_JoystickPowerLevel Joystick::joystickPower(){
  if(isWorking()) return SDL_JoystickCurrentPowerLevel(this->Controle);
  else return SDL_JOYSTICK_POWER_UNKNOWN;
}

bool Joystick::Init(){

  if( SDL_NumJoysticks() == 0 ) return false;
  this->setup();
  this->WORKING = isWorking();

  return this->WORKING;
}

bool Joystick::setup(){
  bool FOUND = false;
  std::cout << "Disponiveis: " << SDL_NumJoysticks() << std::endl;
  for(int i = 0; i < SDL_NumJoysticks(); i++) {
    if(!FOUND){
      std::cout << "Joy ID=" << i << ", Nome=" << SDL_JoystickNameForIndex(i) << std::endl;
      this->Controle = SDL_JoystickOpen(i);
      if(this->Controle){
        FOUND=isWorking();
        this->WORKING=true;
        setup_vars();
      } else this->WORKING=false;
    } else break;
  }
  return FOUND;
}

void Joystick::setup_vars(){
  _DEBUG_maxButtonShow=0;
  Botoes.clear();
  Analogicos.clear();
  Hats.clear();
  Balls.clear();

  int botoes = SDL_JoystickNumButtons(this->Controle);
  int axes = ceil( SDL_JoystickNumAxes(this->Controle) / 2 );
  int hats = SDL_JoystickNumHats(this->Controle);
  int balls = SDL_JoystickNumBalls(this->Controle);

  Hats.resize(hats);
  for(unsigned i=0;i<hats;i++) Hats[i]=0;

  Balls.resize(balls);
  for(unsigned i=0;i<balls;i++) {Balls[i].x=0;Balls[i].y=0;}

  Botoes.resize(botoes);
  for(unsigned i=0;i<botoes;i++) Botoes[i].press=false;

  Analogicos.resize(axes);
  for(unsigned i=0;i<axes;i++) {Analogicos[i].x=0;Analogicos[i].y=0;}

  std::cout << "Botoes: " << botoes << " | Axes: " << axes << " | Hats: " << hats << " | Balls: " << balls << std::endl;
}

void Joystick::OnLoop(){
  bool hasJoy = SDL_NumJoysticks() > 0;
  if( !isWorking() && hasJoy ){
    std::cout << "Buscando...  Resultado= ";
    this->setup();
    if(isWorking()) std::cout << "Sucesso!"; else std::cout << "Falha.";
    std::cout << std::endl;
  }
  this->WORKING = isWorking();

  //Rotina de exibir estado dos botões:

  if(SDL_TICKS_PASSED(SDL_GetTicks(),this->_DEBUG_timeout)){
    this->_DEBUG_timeout = SDL_GetTicks() + 100; //ms
    _debug_TablesStatus();
  }

}

void Joystick::OnEvent(SDL_Event* Evento){
  switch (Evento->type) {

    case SDL_JOYBUTTONDOWN:{
      int btn = Evento->jbutton.button;

      if(btn>_DEBUG_maxButtonShow) _DEBUG_maxButtonShow = btn;

      Botoes[btn].press=true;
      //std::cout << "BTN(" << btn << ") V= PRESSIONADO" << std::endl;
      break;
    }
    case SDL_JOYBUTTONUP:{
      int btn = Evento->jbutton.button;
      Botoes[btn].press=false;
      //std::cout << "BTN(" << btn << ") V= LIBERADO" << std::endl;
      break;
    }

    case SDL_JOYAXISMOTION:{
      float V_MAX = Evento->jaxis.value>=0?SDL_JOYSTICK_AXIS_MAX:-SDL_JOYSTICK_AXIS_MIN;
      float V = (Evento->jaxis.value)/(V_MAX*1.0);
      int AXIS_REAL_ID = Evento->jaxis.axis;
      int AX_ID = floor(AXIS_REAL_ID/2);
      int AX_DIM = AXIS_REAL_ID - AX_ID*2;
      if(AX_DIM == 0)
        Analogicos[AX_ID].x = V;
      else
        Analogicos[AX_ID].y = V;
      break;
      //std::cout << "ANALÓG(" << AX_ID << "," << AX_DIM << ") " << " V= " << V << std::endl;
    }
    case SDL_JOYHATMOTION:{
      int ID_HAT=Evento->jhat.hat;
      Hats[ID_HAT]=Evento->jhat.value;
      break;
    }

    case SDL_JOYBALLMOTION:{
      float V_MAX_X = Evento->jball.xrel>=0?SDL_JOYSTICK_AXIS_MAX:-SDL_JOYSTICK_AXIS_MIN;
      float V_MAX_Y = Evento->jball.yrel>=0?SDL_JOYSTICK_AXIS_MAX:-SDL_JOYSTICK_AXIS_MIN;

      int ID_BALL=Evento->jball.ball;

      V_MAX_X = Evento->jball.xrel;// / V_MAX_X*1.0;
      V_MAX_Y = Evento->jball.yrel;// / V_MAX_Y*1.0;

      Balls[ID_BALL].x = V_MAX_X;
      Balls[ID_BALL].y = V_MAX_Y;

      break;
    }
    default: break;
    //  std::cout << "EVT: " << Evento->type << std::endl;
  }
}

void Joystick::_debug_TablesStatus(){
  if(isWorking()){
    //Botoes.reserve(botoes);
    //Analogicos.reserve(axes);
    std::cout << "Botões:" << std::endl;
    for (int i = 0; i < _DEBUG_maxButtonShow+1; i++) {
      std::string STATUS = Botoes[i].press?"PRESSIONADO":"LIVRE";
      std::cout << "\tBTN_" << i << " STATUS: " << STATUS << std::endl;
    }

    std::cout << std::endl << "Analógicos:" << std::endl;
    for (int i = 0; i < Analogicos.size(); i++) {
      int valorX = round(Analogicos[i].x * 100),
      valorY = round(Analogicos[i].y * 100);
      std::cout << "\tAN_" << i << std::endl;
      std::cout << "\t\tX= " << valorX << std::endl << "\t\tY= " << valorY << std::endl;
    }

    std::cout << std::endl << "Hats:" << std::endl;
    for (int i = 0; i < Hats.size(); i++) {
      int V = Hats[i];
      std::string HAT_STATUS="ERRO";
      switch (Hats[i]) {
        case SDL_HAT_CENTERED: HAT_STATUS="CENTRO";break;
        case SDL_HAT_UP: HAT_STATUS="CIMA";break;
        case SDL_HAT_RIGHT: HAT_STATUS="DIREITA";break;
        case SDL_HAT_DOWN: HAT_STATUS="BAIXO";break;
        case SDL_HAT_LEFT: HAT_STATUS="ESQUERDA";break;
        case SDL_HAT_RIGHTUP: HAT_STATUS="DIREITA_CIMA";break;
        case SDL_HAT_RIGHTDOWN: HAT_STATUS="DIREITA_BAIXO";break;
        case SDL_HAT_LEFTUP: HAT_STATUS="ESQUERDA_CIMA";break;
        case SDL_HAT_LEFTDOWN: HAT_STATUS="ESQUERDA_BAIXO";
      }
      std::cout << "\tHAT_" << i << " STATUS: " << HAT_STATUS << std::endl;
    }

    std::cout << std::endl << "Balls:" << std::endl;
    for (int i = 0; i < Balls.size(); i++) {
      int valorX = round(Balls[i].x * 100),
      valorY = round(Balls[i].y * 100);
      std::cout << "\tBALL_" << i << std::endl;
      std::cout << "\t\tX= " << valorX << std::endl << "\t\tY= " << valorY << std::endl;
    }

    std::cout << "HATS: " << SDL_JoystickNumHats(this->Controle) << std::endl;
    std::cout << "BALLS: " << SDL_JoystickNumBalls(this->Controle) << std::endl;
  }
}

