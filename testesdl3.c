#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <conio.c>

#define TRUE 1
#define FALSE 0


int main( int argc, char* args[] ){	
  SDL_Window* janela; // Ponteiro para a janela
	SDL_Renderer *renderer;
	TTF_Font *font;
	SDL_Surface *text_surface;
	SDL_Texture *texturaTexto;
	SDL_Color color={128, 128, 128, 255};
  
	SDL_Rect rectTexto;	
	SDL_Rect sourceR;
	
  sourceR.x = 0;
  sourceR.y = 0;
  sourceR.w = 16;
  sourceR.h = 16;
	
  int quit = 0; // Devemos encerrar o programa?

  if(SDL_Init(SDL_INIT_VIDEO) != 0){ // Inicializar a SDL
		printf("Erro ao inicializar a SDL. %s\n", SDL_GetError()); // Caso der erro ao inicializala, mostra esse erro
		exit(1); // Encerra Execucao
	}
    
	if(TTF_Init() != 0){ // Inicializar a TTF
		printf("Erro ao inicializar a SDL. %s\n", TTF_GetError()); // Caso der erro ao inicializala, mostra esse erro
		exit(1); // Encerra Execucao
	}
	
	//janela = SDL_CreateWindow("Primeira janela", 100, 100, 320, 240, 0);
  //Cria a janela
  janela = SDL_CreateWindow("My Game Window", // Titulo da janela
														SDL_WINDOWPOS_UNDEFINED, // Posicao X na tela
														SDL_WINDOWPOS_UNDEFINED, // Posicao Y na tela
														640, 480, // Largura e altura da janela, em pixels
														SDL_WINDOW_SHOWN); // Como vai ser a janela
		
		
  renderer = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
	
	
/*-------------------------------------------------------------------------*/
  
	
		
font=TTF_OpenFont("arial.ttf", 36);
if(font == NULL) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
}

	text_surface = TTF_RenderText_Solid(font,"Hello World!",color);


if(text_surface == NULL) {
	printf("\nTTF_RenderText_Solid Error:  %s\n", SDL_GetError());
  exit(1);
}
	texturaTexto = SDL_CreateTextureFromSurface( renderer, text_surface );
	
if(texturaTexto == NULL) {
	printf("\nSDL_CreateTextureFromSurface Error:  %s\n", SDL_GetError());
  exit(1);
}
  int mWidth = text_surface->w;
  int mHeight = text_surface->h;
	
  SDL_FreeSurface(text_surface);
  SDL_Rect renderQuad = { 480 - mWidth - 50, 50, mWidth, mHeight };
  //SDL_BlitSurface(text_surface,NULL,screen,NULL);
  //perhaps we can reuse it, but I assume not for simplicity.
  //SDL_SetRenderTarget(renderer, texturaTexto);
	SDL_RenderCopyEx(renderer, texturaTexto, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
	/*printf("%d\n", SDL_QueryTexture( texturaTexto, NULL, NULL, &rectTexto.w, &rectTexto.h ));
	rectTexto.x = 0;
	rectTexto.y = 0;
	printf("%d - %d - %d - %d\n", rectTexto.w, rectTexto.h, rectTexto.x, rectTexto.y);

	SDL_RenderClear( renderer );

	// Render our text objects ( like normal )
	SDL_RenderCopy( renderer, texturaTexto, &sourceR, &rectTexto );*/
///SDL_Surface *screen;

SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

//SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

//TTF_RenderText_Solid(sans, "OLA, mundo!", color);*
  SDL_Event event; //um evento enviado pela SDL
    while(!quit) //rodar enquanto nao for para encerrar :)
    {
        while(SDL_PollEvent(&event)) //checar eventos
        {
            if(event.type == SDL_QUIT) //fechar a janela?
            {
                quit = 1; //sair do loop principal
            }
        }
        //SDL_Delay(3000);
				SDL_RenderPresent( renderer);
        //SDL_Flip(screen); //atualizar a tela
        //SDL_UpdateWindowSurface(janela);
    }
    /*SDL_Delay(3000);  
  
    SDL_DestroyWindow(janela);
    /*screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE); //criar uma janela 640x480x16bits

    while(!quit) //rodar enquanto nao for para encerrar :)
    {
        while(SDL_PollEvent(&event)) //checar eventos
        {
            if(event.type == SDL_QUIT) //fechar a janela?
            {
                quit = 1; //sair do loop principal
            }
        }

        SDL_Flip(screen); //atualizar a tela
    }*/

		TTF_Quit();
    SDL_Quit(); //encerrar a SDL

    return 0;   
}
