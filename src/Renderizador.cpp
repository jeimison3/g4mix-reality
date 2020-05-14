//#include "Renderizador.hpp"
#include "tela.hpp"

static int OnLoop(void* thr);

Renderizador::Renderizador(Tela* tela){
    this->tela = tela;
}

SDL_Thread *Renderizador::doRender(){
    return SDL_CreateThread(OnLoop, "Renderer", (void *) this);
}

void Renderizador::setLoop(std::function<void(Tela*)> func){
    this->func = func;
}

static int OnLoop(void* thr){
    Renderizador *self = (Renderizador*) thr;
    if(self->func != nullptr)
        self->func(self->tela);
        //std::terminate();
    return 0;
}