#ifndef _TIPOS_DADOS_JANELA_H_
#define _TIPOS_DADOS_JANELA_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define FONTE_TEXTO_PRINCIPAL (Fonte)abrirFonte("Ubuntu-M.ttf", 16)
#define FONTE_TITULO_PRINCIPAL (Fonte)abrirFonte("Ubuntu-B.ttf", 26)
//#define BRANCO (Cor){255,255,255}
#define COR_PRINCIPAL (Cor){178, 34, 34, 255}
#define COR_SELECIONADO (Cor){255, 99, 71, 255}
#define COR_TABELA (Cor){128, 0, 0, 255}
#define COR_FUNDO (Cor){255, 255, 255, 255}
#define COR_FONTE_PRINCIPAL (SDL_Color){178, 34, 34, 255}

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

typedef enum componentesClique {
	CLICADO_FECHAR,
	CLICADO_SAIR,
	CLICADO_VOLTAR,
	CLICADO_PILOTOS,
	CLICADO_NOVO_PILOTO,
	CLICADO_PAIS_PILOTO,
	CLICADO_TABELA_PILOTOS,
	CLICADO_ALTERA_PILOTO,
	CLICADO_EXCLUI_PILOTO,
	CLICADO_CIRCUITOS,
	CLICADO_NOVO_CIRCUITO,
	CLICADO_PAIS_CIRCUITO,
	CLICADO_TABELA_CIRCUITOS,
	CLICADO_ALTERA_CIRCUITO
} ComponenteClicado;

typedef struct {
	unsigned int id;
	char nome[255];
	unsigned int idade;
	char sexo;
	char paisOrigem[255];
} Piloto;

typedef struct {
	unsigned int codigo;
	char nome[255];
	char pais[255];
	unsigned int tamanho;
	char menorTempo[255];
}Circuito;

#endif
