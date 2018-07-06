bool iniciaSDL(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
        cout << "Erro SDL_Init: " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

void terminaSDL(){
    SDL_Quit();
}
