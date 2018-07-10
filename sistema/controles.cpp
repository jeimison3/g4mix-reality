class Joystick{
  private:
    SDL_Joystick* Controle;
    bool WORKING = false;

    vector<Botao> Botoes;
    vector<Point2f> Analogicos;
    vector<int> Hats;
    vector<Point2f> Balls;

    Uint32 _DEBUG_timeout =  SDL_GetTicks();
    int _DEBUG_maxButtonShow = 0;

  public:
    Joystick(){  }
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

    bool Init(){

      if( SDL_NumJoysticks() == 0 ) return false;
      this->setup();
      this->WORKING = isWorking();

      return this->WORKING;
    }

    bool setup(){
      bool FOUND = false;
      cout << "Disponiveis: " << SDL_NumJoysticks() << endl;
      for(int i = 0; i < SDL_NumJoysticks(); i++) {
        if(!FOUND){
          cout << "Joy ID=" << i << ", Nome=" << SDL_JoystickNameForIndex(i) << endl;
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

    void setup_vars(){
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

      cout << "Botoes: " << botoes << " | Axes: " << axes << " | Hats: " << hats << " | Balls: " << balls << endl;
    }

    void OnLoop(){
      bool hasJoy = SDL_NumJoysticks() > 0;
      if( !isWorking() && hasJoy ){
        cout << "Buscando...  Resultado= ";
        this->setup();
        if(isWorking()) cout << "Sucesso!"; else cout << "Falha.";
        cout << endl;
      }
      this->WORKING = isWorking();

      //Rotina de exibir estado dos botões:

      if(SDL_TICKS_PASSED(SDL_GetTicks(),this->_DEBUG_timeout)){
        this->_DEBUG_timeout = SDL_GetTicks() + 100; //ms
        _debug_TablesStatus();
      }

    }

    void OnEvent(SDL_Event* Evento){
      switch (Evento->type) {

        case SDL_JOYBUTTONDOWN:{
          int btn = Evento->jbutton.button;

          if(btn>_DEBUG_maxButtonShow) _DEBUG_maxButtonShow = btn;

          Botoes[btn].press=true;
          //cout << "BTN(" << btn << ") V= PRESSIONADO" << endl;
          break;
        }
        case SDL_JOYBUTTONUP:{
          int btn = Evento->jbutton.button;
          Botoes[btn].press=false;
          //cout << "BTN(" << btn << ") V= LIBERADO" << endl;
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
          //cout << "ANALÓG(" << AX_ID << "," << AX_DIM << ") " << " V= " << V << endl;
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
        //  cout << "EVT: " << Evento->type << endl;
      }
    }

    void _debug_TablesStatus(){
      if(isWorking()){
        //Botoes.reserve(botoes);
        //Analogicos.reserve(axes);
        cout << "Botões:" << endl;
        for (int i = 0; i < _DEBUG_maxButtonShow+1; i++) {
          string STATUS = Botoes[i].press?"PRESSIONADO":"LIVRE";
          cout << "\tBTN_" << i << " STATUS: " << STATUS << endl;
        }

        cout << endl << "Analógicos:" << endl;
        for (int i = 0; i < Analogicos.size(); i++) {
          int valorX = round(Analogicos[i].x * 100),
          valorY = round(Analogicos[i].y * 100);
          cout << "\tAN_" << i << endl;
          cout << "\t\tX= " << valorX << endl << "\t\tY= " << valorY << endl;
        }

        cout << endl << "Hats:" << endl;
        for (int i = 0; i < Hats.size(); i++) {
          int V = Hats[i];
          string HAT_STATUS="ERRO";
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
          cout << "\tHAT_" << i << " STATUS: " << HAT_STATUS << endl;
        }

        cout << endl << "Balls:" << endl;
        for (int i = 0; i < Balls.size(); i++) {
          int valorX = round(Balls[i].x * 100),
          valorY = round(Balls[i].y * 100);
          cout << "\tBALL_" << i << endl;
          cout << "\t\tX= " << valorX << endl << "\t\tY= " << valorY << endl;
        }

        cout << "HATS: " << SDL_JoystickNumHats(this->Controle) << endl;
        cout << "BALLS: " << SDL_JoystickNumBalls(this->Controle) << endl;
      }
    }


};
