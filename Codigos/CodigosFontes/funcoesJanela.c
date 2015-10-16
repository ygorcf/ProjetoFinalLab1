#ifndef _FUNCOES_JANELA_C_
#define _FUNCOES_JANELA_C_

#include <SDL2/SDL.h>
#include <Cabecalhos/tiposDadosJanela.h>
#include <stdio.h>



// Objetivo: Criar uma janela
// Parametros: Um ponteiro FILE que aponta para o arquivo onde sera salvo os 
//						 erros, o endereco da string que contem o titulo da janela, a 
//						 largura da	janela e a altura da janela
// Retorno: A janela criada ou NULL se ocorrer um erro
Janela criarJanela(FILE *arquivoErros, char *tituloJanela, int largura, 
										int altura){
	Janela jan = NULL;
  //Cria a janela
  jan = SDL_CreateWindow(tituloJanela, // Titulo da janela
													SDL_WINDOWPOS_UNDEFINED, // Posicao X na tela
													SDL_WINDOWPOS_UNDEFINED, // Posicao Y na tela
													largura, // Largura da janela, em pixels
													altura, // Altura da janela, em pixels
													SDL_WINDOW_SHOWN); // Como vai ser a janela
	
	//Verifica se ocorreu um erro ao criar a janela
	if(jan == NULL)
		fprintf(arquivoErros, 
						"Erro na funcao 'SDL_CreateWindow' de 'criarJanela': %s\n", 
						SDL_GetError());
  
	return jan;					
}


// Objetivo: Criar um painel
// Parametros: Um ponteiro FILE que aponta para o arquivo onde sera salvo os 
//						 erros, a janela onde ficara o painel
// Retorno: O painel criado ou NULL se ocorrer um erro
Painel criarPainel(FILE *arquivoErros, Janela janela){
	// Cria a cor branca
	Cor branco;
	branco.r = 255;
	branco.g = 255;
	branco.b = 255;
	branco.opacidade = 255;
	Painel painel = NULL;
  painel = SDL_CreateRenderer(janela, // A janela onde ficara o painel
														-1, // O index do driver de renderizacao ou -1 para
																//	o primeiro driver
														SDL_RENDERER_ACCELERATED); // O tipo de rederizacao
	
	//Verifica se ocorreu um erro ao criar o painel
	if(painel == NULL)
		fprintf(arquivoErros, 
						"Erro na funcao 'SDL_CreateRenderer' de 'criarPainel': %s\n", 
						SDL_GetError());
	
	// Pinta o fundo do painel com a cor branca e verifica se ocorreu um erro ao 
	//	pintar o fundo
	if(alteraCorFundoPainel(arquivoErros, painel, branco) != 0){
  	fprintf(arquivoErros, 
						"Erro na funcao 'alteraCorFundoPainel' de 'criarPainel': %s\n", 
						SDL_GetError());
		return NULL;
	}
	
	return painel;
}



// Objetivo: Alterar a cor de fundo do painel
// Parametros: Um ponteiro FILE que aponta para o arquivo onde sera salvo os 
//						 erros, o painel que mudara a cor de fundo, a nova cor que 
//						 ficara no fundo do painel
// Retorno: 0 - Se a funcao executar com sucesso
//					1 - Se ocorrer um erro
int alteraCorFundoPainel(FILE *arquivoErros, Painel painelAlterarCor, 
													Cor novaCor){
	// Define a cor do fundo do painel e verifica se ocorreu um erro ao definir a 
	//	cor
  if(SDL_SetRenderDrawColor(painelAlterarCor, 
														novaCor.r, 
														novaCor.g, 
														novaCor.b, 
														novaCor.opacidade) != 0){
  	fprintf(arquivoErros, 
						"Erro na funcao 'SDL_SetRenderDrawColor' de 'alteraCorFundoPainel': %s\n", 
						SDL_GetError());
		return 1;
	}
  // Pinta o fundo do painel com a nova cor e verifica se ocorreu um erro ao 
  // pinta-lo com essa cor
  if(SDL_RenderClear(painelAlterarCor) != 0){
  	fprintf(arquivoErros, 
						"Erro na funcao 'SDL_RenderClear' de 'alteraCorFundoPainel': %s\n", 
						SDL_GetError());
		return 1;
	}
	
	return 0;
}



// Objetivo: Abrir uma fonte
// Parametros: Um ponteiro FILE que aponta para o arquivo onde sera salvo os 
//						 erros, o endereco de uma string que contem o local onde a fonte 
//						 esta armazenada e o tamanho da fonte
// Retorno: A fonte ou NULL se ocorrer um erro
Fonte abrirFonte(FILE *arquivoErros, char *localFonte, int tamanhoFonte){
	Fonte fonte = NULL;
	
	// Abre a fonte
	fonte = TTF_OpenFont(localFonte, // Local onde esta a fonte
												tamanhoFonte); // Tamanho da fonte
	
	// Verifica se ocorreu um erro ao abrir a fonte
	if(fonte == NULL)
		fprintf(arquivoErros, 
						"Erro na funcao 'TTF_OpenFont' de 'abrirFonte': %s\n", 
						TTF_GetError());
	
	return fonte;
}



// Objetivo: Transformar um texto em uma superficie
// Parametros: Um ponteiro FILE que aponta para o arquivo onde sera salvo os 
//							erros, a fonte do texto, o endereco da string que contem o 
//							texto e a cor do texto
// Retorno: A superficie do texto ou NULL se ocorrer um erro
Superficie textoParaSuperficie(FILE *arquivoErros, Fonte fonteTexto, 
																char *texto, Cor corTexto){
	Superficie superficeTexto = NULL;
	SDL_Color colorText = {corTexto.r, corTexto.g, corTexto.b, 
													corTexto.opacidade};
	
	//Transforma o texto em uma superficie
	superficeTexto = TTF_RenderText_Solid(fonteTexto, texto, colorText);
	
	// Verifica se ocorreu um erro ao transformar o text em superficie
	if(superficeTexto == NULL) 
		fprintf(arquivoErros, 
						"Erro na funcao 'TTF_RenderText_Solid' de 'textoParaSuperficie': %s\n", 
						TTF_GetError());
	
	return superficeTexto;
}



// Objetivo: Transformar uma superficie em textura
// Parametros: Um ponteiro FILE que aponta para o arquivo onde sera salvo os 
//							erros, o painel onde ficara a superficie e a superficie que 
//							sera transformada
// Retorno: A textura criada ou NULL se ocorrer um erro
Textura superficieParaTextura(FILE *arquivoErros, Painel painelDestino, 
															 Superficie superficieTransformar){
	Textura novaTextura = NULL;
	
	// Cria uma textura apartir da superficie
	novaTextura = SDL_CreateTextureFromSurface(painelDestino, 
																							superficieTransformar);
	
	// Verifica se ocorreu um erro ao criar a textura
	if(novaTextura == NULL) 
		fprintf(arquivoErros, 
						"Erro na funcao 'SDL_CreateTextureFromSurface' de 'superficieParaTextura': %s\n", 
						SDL_GetError());
	
	return novaTextura;
}



// Objetivo: Limpar a memoria usada pela superficie
// Parametro: A superficie a ser limpa
void limparSuperficie(Superficie superficieLimpar){
	// Limpa a superficie
	SDL_FreeSurface(superficieLimpar);
}



// Objetivo: Copiar uma parte ou toda a textura para um painel
// Parametros: Um ponteiro FILE que aponta para o arquivo onde sera salvo os 
//							erros, o painel onde ficara a textura, a textura que sera 
//							copiada para o painel e o retangulo com o tamanho que sera 
//							usado pela textura no painel
int copiarTexturaPainel(FILE *arquivoErros, Painel painelDestino, 
												 Textura texturaCopiar, Retangulo retanguloTextura){
	int res = 0;
	
	// Copia a textura para o painel
	res = SDL_RenderCopyEx(painelDestino, // O painel onde ficara a textura
													texturaCopiar, // A textura a ser copiada
													NULL, // O tamanho que sera copiado da textura ou
																//	NULL para toda textura
													&retanguloTextura, // O tamanho que sera utilizado
																						 //	 pela textura no painel
													0, // O angulo de rotacao que sera aplicado na 
														 //	 textura
													NULL, // O ponto na textura onde sera aplicada a 
																//	rotacao ou NULL para o centro
													SDL_FLIP_NONE); // O valor informando se ocorrera um
																					// giro na textura
	
	// Verifica se ocorreu um erro ao copiar a textura
	if(res != 0)
		fprintf(arquivoErros, 
						"Erro na funcao 'SDL_RenderCopyEx' de 'copiarTexturaPainel': %s\n", 
						SDL_GetError());
	
	return res;
}



// Objetivo: Atualizar um painel
// Parametro: O painel a ser atualizado
void atualizarPainel(Painel painelAtualizar){
	SDL_RenderPresent(painelAtualizar);
}

#endif /* _FUNCOES_JANELA_C_ */
