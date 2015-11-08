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
#define INFO_IMPLEMENTANDO(jan) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Nao implementado", "Funcionalidade ainda nao implementada", jan);
#define ERRO_CAMPO_NULO(jan) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Campos Nulos", "Um ou mais campos estao nulos", jan);

#define LOCAL_ARQUIVO_PILOTOS "Dados/Pilotos.guyg"
#define LOCAL_ARQUIVO_PILOTOS_TMP "Dados/PilotosTmp.guyg"
#define LOCAL_ARQUIVO_CIRCUITOS "Dados/Circuitos.guyg"
#define LOCAL_ARQUIVO_MELHORES_VOLTAS "Dados/MelhoresVoltas.guyg"
#define LOCAL_ARQUIVO_MELHORES_VOLTAS_TMP "Dados/MelhoresVoltasTmp.guyg"

#define TAM_NOME 100
#define TAM_PAIS 50
#define TAM_DATA 11
#define TAM_TEMPO 10


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
	int ativo;
	int ocorreuErro;
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
	CLICADO_ALTERA_CIRCUITO,
	CLICADO_MELHORES_VOLTAS,
	CLICADO_NOVA_MELHOR_VOLTA,
	CLICADO_PILOTO_MELHOR_VOLTA,
	CLICADO_CIRCUITO_MELHOR_VOLTA,
	CLICADO_TABELA_MELHORES_VOLTAS,
	CLICADO_ALTERA_MELHOR_VOLTA,
	CLICADO_EXCLUI_MELHOR_VOLTA,
	CLICADO_RELATORIOS,
	CLICADO_RELATORIO_1,
	CLICADO_RELATORIO_2,
	CLICADO_RELATORIO_3,
	CLICADO_RELATORIO_4,
	CLICADO_RELATORIO_5,
	CLICADO_RELATORIO_6
} ComponenteClicado;

typedef struct {
	unsigned int id;
	char nome[TAM_NOME];
	unsigned int idade;
	char sexo;
	char paisOrigem[TAM_PAIS];
} Piloto;

typedef struct {
	unsigned int codigo;
	char nome[TAM_NOME];
	char pais[TAM_PAIS];
	double tamanho;
	char menorTempo[TAM_TEMPO];
	unsigned int idPiloto;
} Circuito;

typedef struct {
	unsigned int id;
	unsigned int idPiloto;
	unsigned int idCircuito;
	char nomeEquipe[TAM_NOME];
	char data[TAM_DATA];
	char tempo[TAM_TEMPO];
} MelhorVolta;


#endif
