class Perifericos{
  private:
    Tela* tela = (Tela*) new Tela();
    bool telaInit = false;

    Joystick* controle = (Joystick*) new Joystick();
    bool controleInit = false;

    Uint32 timeout =  SDL_GetTicks();

  public:
    Tela* pTela(){ return this->tela; }
    Joystick* pControle(){ return this->controle; }

    Perifericos(){
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

    bool Init(){
      if(!this->telaInit) this->telaInit = tela->Init();
      if(!this->controleInit) this->controleInit = controle->Init();

      if(!this->telaInit) cout << "[Tela] Janela ou renderizador apresentando falhas." << endl;
      if(!this->controleInit) cout << "[Controle] Controle não encontrado." << endl;

      bool resumo = this->telaInit && this->controleInit;

      if(!resumo) cout << "[Perif.] Repetindo." << " SZ= " << SDL_NumJoysticks() << endl;
      else cout << "[Perif.] Inicializado." << endl;

      return resumo;
    }

    void OnLoop(){
      if(this->telaInit) this->tela->OnLoop();
      if(this->controleInit) this->controle->OnLoop();
    }

    void OnEvent(SDL_Event* Evento){
      if(this->telaInit) this->tela->OnEvent(Evento);
      if(this->controleInit) this->controle->OnEvent(Evento);
    }
};
