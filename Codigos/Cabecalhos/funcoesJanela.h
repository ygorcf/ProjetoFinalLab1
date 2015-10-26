#ifndef _FUNCOES_JANELA_H_
#define _FUNCOES_JANELA_H_


Janela criarJanela(char *tituloJanela, int largura, int altura);
Painel criarPainel(Janela janela);
int alteraCorFundoPainel(Painel painelAlterarCor, Cor novaCor);
Fonte abrirFonte(char *localFonte, int tamanhoFonte);
Superficie textoParaSuperficie(char *texto, Fonte fonteTexto);
Textura superficieParaTextura(Painel painelDestino, Superficie superficieTransformar);
void limparSuperficie(Superficie superficieLimpar);
int copiarTexturaPainel(Painel painelDestino, Textura texturaCopiar, 
												 Retangulo retanguloTextura);
void atualizarPainel(Painel painelAtualizar);
Componente pintarTextoPainel(char *textoPintar, Painel painelDestino, int posX, int posY, 
															Fonte fonteTexto, Janela janela);
Superficie criarSuperficie(int largura, int altura);
int pintarSuperficie(Superficie superficiePintar, Cor corPintar);
Componente pintarRetanguloPainel(int posX, int posY, int largura, int altura, Cor cor, 
																	Painel painelDestino);
Componente pintarTabelaPainel(int posX, int posY, int largura, int altura, int larguraBorda, 
															 Cor corBorda, Cor corFundo, int qtdColunas, int qtdLinhas, 
															 Painel painelDestino);
Componente pintarDadoTabela(Componente tabelaDestino, int linhaTabela, int colunaTabela, 
														 int espacamentoCelula, char *dado);
Componente retirarUltimaLetraTextoPainel(char *texto, Componente componenteTexto);
int limparPainel(Painel painelLimpar);
int checarEventoMenuPrincipal(Janela janela, Painel painelDestino);
int checarEventoMenuPilotos(Janela janela, Painel painelDestino);
int checarEventoMenuNovoPiloto(Janela janela, Painel painelDestino);
int verificarCliqueDentroRetangulo(Retangulo rect);
int atualizarBordaComponente(Componente *compAtualizar);

#include <CodigosFontes/funcoesJanela.c>

#endif
