#include "tela.hpp"

SDL_Texture *texTarget; // tmp
bool rendered = false;

TTF_Font *FONT_IFACE_04B30_20, *FONT_IFACE_04B30_12; //this opens a font style and sets a size

static int OnLoop(void* classe);

Tela::Tela(int Width, int Heigth, int FrameRate){
  this->WIN_WIDTH = Width;
  this->WIN_HEIGHT = Heigth;
  this->FPS = new Frequent(FrameRate);
}

bool Tela::Init(){

  TTF_Init();
  FONT_IFACE_04B30_20 = TTF_OpenFont("res/04B30.TTF", 20);
  FONT_IFACE_04B30_12 = TTF_OpenFont("res/04B30.TTF", 12);

  this->Janela = SDL_CreateWindow("G4MIXED_REALITY", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->WIN_WIDTH, this->WIN_HEIGHT, SDL_WINDOW_OPENGL);
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

  // TEXTURE
  //Put your own bmp image here

	SDL_Surface *bmpSurf = SDL_LoadBMP("res/Aurora.bmp");
	SDL_Texture *bmpTex = SDL_CreateTextureFromSurface(this->Render, bmpSurf);
	SDL_FreeSurface(bmpSurf);

  texTarget = SDL_CreateTexture(this->Render, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, this->WIN_WIDTH, this->WIN_HEIGHT);
	
	
	SDL_SetRenderTarget(this->Render, texTarget); //Now render to the texture

	SDL_RenderClear(this->Render);
	SDL_RenderCopy(this->Render, bmpTex, NULL, NULL);
	
	SDL_SetRenderTarget(this->Render, NULL); //Detach the texture

  SDL_SetRenderDrawColor(this->Render, 0, 0, 0, 0);

  this->ready = true;

  this->thread = SDL_CreateThread(OnLoop, "TelaLoop", (void *)this);

  //std::thread(OnLoop, (void*) this);

  //this->renderizer = new Renderizador(this->Render);

  this->renderizadores = std::vector<Renderizador*>(2);

  renderizadores[0] = new Renderizador(this);
  renderizadores[0]->setLoop(
    [](Tela* tela)-> void {
      SDL_RenderCopyEx(tela->Render, texTarget, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
    }
  );

  renderizadores[1] = new Renderizador(this);
  renderizadores[1]->setLoop(
    [](Tela* tela)-> void {
      tela->drawTxt( std::to_string(tela->FPS->getIPS()) + " FPS",
        FONT_IFACE_04B30_20,
        0, 20 );

      tela->drawTxt( std::to_string(tela->FPS->getPeriod()) + " ms",
        FONT_IFACE_04B30_20,
        0, 40 );
    }
  );
  
  //this->thread.join();

  return true;
}

static int OnLoop(void* classe) {
  
  while( true ){
    Tela *self = (Tela*) classe;
    if(!self->ready) break;

    SDL_RenderClear(self->Render);

    if(self->FPS->isReady()){
      for (auto& th : self->renderizadores) {
          int x;
          SDL_WaitThread(th->doRender(), &x);
      }
      

      

      // SDLUtil::LOG_Debug( std::to_string(this->FPS->getIPS()) + " FPS"  );
      // SDLUtil::LOG_Debug( std::to_string(this->FPS->getPeriod()) + " ms"  );
      SDL_RenderPresent(self->Render);
    }
    contin:;
  }
  return 0;
}

void Tela::OnEvent(SDL_Event* Evento){
  switch(Evento->type){
    case SDL_QUIT:
      this->ready = false;
      SDL_DestroyRenderer(this->Render);
      SDL_DestroyWindow(this->Janela);
      break;
    default: break;
  }
}


void Tela::drawTxt(std::string txt, TTF_Font* fonte , int x, int y){
  
  if (fonte == nullptr) {SDLUtil::LOG_Debug(TTF_GetError());exit;}
  SDL_Color White = {255, 255, 255, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fonte, txt.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

  SDL_Texture* Message = SDL_CreateTextureFromSurface(this->Render, surfaceMessage); //now you can convert it into a texture

  SDL_Rect Message_rect; //create a rect
  Message_rect.x = x;  //controls the rect's x coordinate 
  Message_rect.y = y; // controls the rect's y coordinte
  Message_rect.w = surfaceMessage->w; // controls the width of the rect
  Message_rect.h = surfaceMessage->h; // controls the height of the rect


  //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

  //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

  SDL_RenderCopy(this->Render, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
  
  //Don't forget to free your surface and texture
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
}
