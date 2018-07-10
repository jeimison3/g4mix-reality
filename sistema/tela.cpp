class Tela{
  private:
      SDL_Window* Janela;
      SDL_Renderer* Render;

  public:

    Tela(){}

    bool Init(){
      this->Janela = SDL_CreateWindow("G4MIXED_REALITY", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
      if(this->Janela == NULL){
        SDLUtil::Termina( "Não foi possível criar a janela da aplicação." );
        return false;
      }

      this->Render = SDL_CreateRenderer(this->Janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

      if (this->Render == nullptr){
          SDL_DestroyWindow(this->Janela);
          SDLUtil::Termina( "Não foi possível renderizar a cena." );
          return false;
      }

      return true;
    }

    void OnLoop(){

    }

    void OnEvent(SDL_Event* Evento){

    }
};
