#ifndef _FUNCOES_JANELA_H_
#define _FUNCOES_JANELA_H_


Janela criarJanela(char *tituloJanela, int largura, int altura);
Painel criarPainel(Janela janela);
int alteraCorFundoPainel(Painel painelAlterarCor, Cor novaCor);
Fonte abrirFonte(char *localFonte, int tamanhoFonte);
Superficie textoParaSuperficie(Fonte fonteTexto, char *texto, Cor corTexto);
Textura superficieParaTextura(Painel painelDestino, Superficie superficieTransformar);
void limparSuperficie(Superficie superficieLimpar);
int copiarTexturaPainel(Painel painelDestino, Textura texturaCopiar, 
												 Retangulo retanguloTextura);
void atualizarPainel(Painel painelAtualizar);
Componente pintarTextoPainel(char *textoPintar, Painel painelDestino, int posX, 
															int posY, Fonte fonteTexto, Cor corFonte);
Superficie criarSuperficie(int largura, int altura);
int pintarSuperficie(Superficie superficiePintar, Cor corPintar);
Componente pintarRetanguloPainel(int posX, int posY, int largura, int altura, Cor cor, 
																	Painel painelDestino);
Componente pintarRetanguloCBordasPainel(int posX, int posY, int largura, int altura, 
																	int larguraBorda, Cor corBorda, Cor corFundo, 
																	Painel painelDestino);

#include <CodigosFontes/funcoesJanela.c>

#endif
