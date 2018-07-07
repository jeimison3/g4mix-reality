class Perifericos{
  private:
    Tela* tela = (Tela*) new Tela();
    bool telaInit = false;

    Joystick* controle = (Joystick*) new Joystick();
    bool controleInit = false;

  public:
    Tela* pTela(){ return this->tela; }
    Joystick* pControle(){ return this->controle; }

    Perifericos(){
      bool resu=true;
      do{
        if(resu==false) SDL_Delay(500);
        resu = Init();
      } while(!resu);
    }

    bool Init(){
      if(!this->telaInit) this->telaInit = tela->Init();
      if(!this->controleInit) this->controleInit = controle->Init();

      if(!this->telaInit) cout << "[Tela] Janela ou renderizador apresentando falhas." << endl;
      if(!this->controleInit) cout << "[Controle] Controle não encontrado." << endl;

      bool resumo = this->telaInit && this->controleInit;

      if(!resumo) cout << "[Perif.] Repetindo." << endl;
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
