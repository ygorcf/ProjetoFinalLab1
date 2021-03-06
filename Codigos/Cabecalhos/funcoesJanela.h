#ifndef _FUNCOES_JANELA_H_
#define _FUNCOES_JANELA_H_

Janela criarJanela(char *tituloJanela, int largura, int altura);
Painel criarPainel(Janela janela);
int alteraCorFundoPainel(Painel painelAlterarCor, Cor novaCor);
Fonte abrirFonte(char *localFonte, int tamanhoFonte);
Superficie textoParaSuperficie(char *texto, Fonte fonteTexto);
Textura superficieParaTextura(Painel painelDestino, Superficie superficieTransformar);
void limparMemSuperficie(Superficie superficieLimpar);
int copiarTexturaPainel(Painel painelDestino, Textura texturaCopiar, 
												 Retangulo retanguloTextura);
void atualizarPainel(Painel painelAtualizar);
Retangulo pintarTextoPainel(char *textoPintar, int posX, int posY, Fonte fonteTexto, 
															Janela janelaDestino);
Superficie criarSuperficie(int largura, int altura);
int pintarSuperficie(Superficie superficiePintar, Cor corPintar);
Componente pintarRetanguloPainel(int posX, int posY, int largura, int altura, Cor cor, 
																	Painel painelDestino);
Componente pintarTabelaPainel(int posX, int posY, int largura, int altura, Cor corBorda, 
                               int qtdColunas, int qtdLinhas, Painel painelDestino);
Componente pintarDadoTabela(Componente tabelaDestino, int linhaTabela, int colunaTabela, 
														 char *dado, Janela janelaDestino);
Componente retirarUltimaLetraTextoPainel(char *texto, Componente componenteTexto);
int limparPainel(Painel painelLimpar);
int verificarCliqueDentroRetangulo(Retangulo rect);
int atualizarBordaComponente(Componente *compAtualizar);
//void limparMemPainel(Painel painelLimpar);
int manipularCampoTexto(SDL_Event *e, Componente *c, char *txt, Janela j, int min, int max, int tipo);
void inicializarComponente(Componente *componenteInicializar, Painel painelDestino);

#include <CodigosFontes/funcoesJanela.c>

#endif
