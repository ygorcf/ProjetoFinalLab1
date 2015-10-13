#ifndef _FUNCOES_JANELA_H_
#define _FUNCOES_JANELA_H_

Janela criarJanela(FILE *arquivoErros, char *tituloJanela, int largura, 
										int altura);
Painel criarPainel(FILE *arquivoErros, Janela janela);
int alteraCorFundoPainel(FILE *arquivoErros, Painel painelAlterarCor, 
													Cor novaCor);
Fonte abrirFonte(FILE *arquivoErros, char *localFonte, int tamanhoFonte);
Superficie textoParaSuperficie(FILE *arquivoErros, Fonte fonteTexto, 
																char *texto, Cor corTexto);
Textura superficieParaTextura(FILE *arquivoErros, Painel painelDestino, 
															 Superficie superficieTransformar);
void limparSuperficie(Superficie superficieLimpar);
int copiarTexturaPainel(FILE *arquivoErros, Painel painelDestino, 
												 Textura texturaCopiar, Retangulo retanguloTextura);
void atualizarPainel(Painel painelAtualizar);

#include <CodigosFontes/funcoesJanela.c>

#endif
