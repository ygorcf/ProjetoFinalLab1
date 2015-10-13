/*#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_W 640 //tamanho da janela que sera criada
#define SCREEN_H 480

int main( int argc, char* args[] )
{
    SDL_Event event; //um evento enviado pela SDL
    int quit = 0; //devemos encerrar o programa?

    SDL_Init(SDL_INIT_VIDEO); //inicializar a SDL
    TTF_Init();
    SDL_Window* janela;  
    //janela = SDL_CreateWindow("Primeira janela", 100, 100, 320, 240, 0);
    SDL_Window *screen = SDL_CreateWindow("My Game Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_SHOWN);
//SDL_Surface *screen;
SDL_Color color={0,0,0};
SDL_Surface *text_surface;

TTF_Font* sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

//SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

TTF_RenderText_Solid(sans, "OLA, mundo!", color);
    while(!quit) //rodar enquanto nao for para encerrar :)
    {
        while(SDL_PollEvent(&event)) //checar eventos
        {
            if(event.type == SDL_QUIT) //fechar a janela?
            {
                quit = 1; //sair do loop principal
            }
        }

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
    }*

		TTF_Quit();
    SDL_Quit(); //encerrar a SDL

    return 0;   
}*/
