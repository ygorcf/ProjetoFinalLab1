#ifndef _TIPOS_DADOS_JANELA_H_
#define _TIPOS_DADOS_JANELA_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define FONTE_TEXTO_PRINCIPAL (Fonte)abrirFonte("Ubuntu-M.ttf", 16)
#define FONTE_TITULO_PRINCIPAL (Fonte)abrirFonte("Ubuntu-B.ttf", 26)
#define BRANCO (Cor){255,255,255}
#define COR_PRINCIPAL (Cor){178, 34, 34, 255}
#define COR_FUNDO (Cor){255,255,255}

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

typedef struct {
	Painel painelPertencente;
	Retangulo area;
	Retangulo areaAux;
} Componente;

#endif
