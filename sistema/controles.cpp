class Joystick{
  private:
    SDL_Joystick* Controle;
    
    bool WORKING = false;

  public:
    SDL_Joystick* pControle(){ return this->Controle; }

    bool isWorking(){ return SDL_JoystickGetAttached(this->Controle); }

    /*
    SDL_JOYSTICK_POWER_
    UNKNOWN | EMPTY | LOW | MEDIUM | FULL | WIRED | MAX
    */
    SDL_JoystickPowerLevel joystickPower(){
      if(isWorking()) return SDL_JoystickCurrentPowerLevel(this->Controle);
      else return SDL_JOYSTICK_POWER_UNKNOWN;
    }

    bool setupController(){
      bool FOUND = false;
      cout << "Disponiveis: " << SDL_NumJoysticks() << endl;
      for(int i = 0; i < SDL_NumJoysticks(); i++) {
        if(!FOUND){
          cout << "Joy ID=" << i << ", Nome=" << SDL_JoystickNameForIndex(i) << endl;
          this->Controle = SDL_JoystickOpen(i);
          if(this->Controle){
            this->WORKING=true;
          } else this->WORKING=false;
          FOUND=isWorking();
        } else break;
      }
      return FOUND;
    }

    bool Init(){

      if( SDL_NumJoysticks() == 0 ) return false;

      this->WORKING = setupController();

      return this->WORKING;
    }

    void OnLoop(){
      bool hasJoy = SDL_NumJoysticks() > 0;

      if( !isWorking() && hasJoy ){
        cout << "Buscando...  Resultado= ";
        setupController();
        if(isWorking()) cout << "Sucesso!"; else cout << "Falha.";
        cout << endl;
      }

      this->WORKING = isWorking();
    }

    void OnEvent(SDL_Event* Evento){
      switch (Evento->type) {

        case SDL_JOYBUTTONDOWN:{
          int btn = Evento->jbutton.button;
          cout << "BTN(" << btn << ") V= PRESSIONADO" << endl;
          break;
        }
        case SDL_JOYBUTTONUP:{
          int btn = Evento->jbutton.button;
          cout << "BTN(" << btn << ") V= LIBERADO" << endl;
          break;
        }

        case SDL_JOYAXISMOTION:{
          float V = Evento->jaxis.value>=0?SDL_JOYSTICK_AXIS_MAX:-SDL_JOYSTICK_AXIS_MIN;
          V = Evento->jaxis.value/V*1.0;
          cout << "ANALÓG(" << (int)(Evento->jaxis.axis) << ") " << " V= " << V << endl;
        }

      }
    }


};
