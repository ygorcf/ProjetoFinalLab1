#ifndef _TIPOS_DADOS_JANELA_H_
#define _TIPOS_DADOS_JANELA_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef SDL_Window *Janela;
typedef SDL_Renderer *Painel;
typedef TTF_Font *Fonte;
typedef SDL_Surface *Superficie;
typedef SDL_Texture *Textura;
typedef SDL_Rect Retangulo;

typedef struct {
	int r;
	int g;
	int b;
	int opacidade;
} Cor;

#endif
