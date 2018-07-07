class SDLUtil{
  public:
    static bool Init(){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
          cout << "CODIGO: " << SDL_GetError() << endl;
          Termina();
          return false;
        }
        return true;
    }

    static void Termina(string motivo = ""){
      if(motivo!="") cout << "[FATAL] " << motivo << endl;
        SDL_Quit();
    }
};
