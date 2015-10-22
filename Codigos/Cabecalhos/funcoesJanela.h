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
															Fonte fonteTexto);
Superficie criarSuperficie(int largura, int altura);
int pintarSuperficie(Superficie superficiePintar, Cor corPintar);
Componente pintarRetanguloPainel(int posX, int posY, int largura, int altura, Cor cor, 
																	Painel painelDestino);
Componente pintarRetanguloCBordasPainel(int posX, int posY, int largura, int altura, 
																	int larguraBorda, Cor corBorda, Cor corFundo, 
																	Painel painelDestino);
Componente pintarTabelaPainel(int posX, int posY, int largura, int altura, int larguraBorda, 
															 Cor corBorda, Cor corFundo, int qtdColunas, int qtdLinhas, 
															 Painel painelDestino);
Componente pintarDadoTabela(Componente tabelaDestino, int linhaTabela, int colunaTabela, 
														 int espacamentoCelula, char *dado);
Componente retirarUltimaLetraTextoPainel(char *texto, Componente componenteTexto);
Painel limparPainel(Painel painelLimpar, Janela janelaPertencente);
int pintarMenuPrincipal(Janela janela, Painel painelDestino, Cor corFundo, Cor corPrincipal);
int pintarMenuPilotos(Janela janela, Painel painelDestino, Cor corFundo, Cor corPrincipal);
int pintarMenuNovoPiloto(Janela janela, Painel painelDestino, Cor corFundo, Cor corPrincipal);

#include <CodigosFontes/funcoesJanela.c>

#endif
