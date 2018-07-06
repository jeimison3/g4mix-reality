bool iniciaSDL(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        cout << "Erro SDL_Init: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

void terminaSDL(){
    SDL_Quit();
}

bool constroiInterface(SDL_Window* Janela, SDL_Renderer* Render){
    Janela = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    Render = SDL_CreateRenderer(Janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (Render == nullptr){
        SDL_DestroyWindow(Janela);
        cout << "Erro SDL_CreateRenderer: " << SDL_GetError() << endl;
        return false;
    }
    
    return true;
}

