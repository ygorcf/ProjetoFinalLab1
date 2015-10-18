#ifndef _FUNCOES_JANELA_C_
#define _FUNCOES_JANELA_C_

#include <Cabecalhos/tiposDadosJanela.h>
#include <stdio.h>



// Objetivo: Criar uma janela
// Parametros: O endereco da string que contem o titulo da janela, a largura da	janela e 
//							a altura da janela
// Retorno: A janela criada ou NULL se ocorrer um erro
Janela criarJanela(char *tituloJanela, int largura, int altura){
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
		salvarErro(rsprintf("Erro na funcao 'SDL_CreateWindow' de 'criarJanela': %s\n", 
						SDL_GetError()));
  
	return jan;					
}


// Objetivo: Criar um painel
// Parametro: A janela onde ficara o painel
// Retorno: O painel criado ou NULL se ocorrer um erro
Painel criarPainel(Janela janela){
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
		salvarErro(rsprintf("Erro na funcao 'SDL_CreateRenderer' de 'criarPainel': %s\n", 
						SDL_GetError()));
	
	// Pinta o fundo do painel com a cor branca e verifica se ocorreu um erro ao 
	//	pintar o fundo
	if(alteraCorFundoPainel(painel, branco) != 0){
  	salvarErro(rsprintf("Erro na funcao 'alteraCorFundoPainel' de 'criarPainel': %s\n", 
						SDL_GetError()));
		return NULL;
	}
	
	return painel;
}



// Objetivo: Alterar a cor de fundo do painel
// Parametros: O painel que mudara a cor de fundo, a nova cor que ficara no fundo do 
//							painel
// Retorno: 0 - Se a funcao executar com sucesso
//					1 - Se ocorrer um erro
int alteraCorFundoPainel(Painel painelAlterarCor, Cor novaCor){
	// Define a cor do fundo do painel e verifica se ocorreu um erro ao definir a 
	//	cor
  if(SDL_SetRenderDrawColor(painelAlterarCor, 
														novaCor.r, 
														novaCor.g, 
														novaCor.b, 
														novaCor.opacidade) != 0){
  	salvarErro(rsprintf("Erro na funcao 'SDL_SetRenderDrawColor' de 'alteraCorFundoPainel': %s\n", 
						SDL_GetError()));
		return 1;
	}
  // Pinta o fundo do painel com a nova cor e verifica se ocorreu um erro ao 
  // pinta-lo com essa cor
  if(SDL_RenderClear(painelAlterarCor) != 0){
  	salvarErro(rsprintf("Erro na funcao 'SDL_RenderClear' de 'alteraCorFundoPainel': %s\n", 
						SDL_GetError()));
		return 1;
	}
	
	return 0;
}



// Objetivo: Abrir uma fonte
// Parametros: O endereco de uma string que contem o local onde a fonte esta armazenada 
//							e o tamanho da fonte
// Retorno: A fonte ou NULL se ocorrer um erro
Fonte abrirFonte(char *localFonte, int tamanhoFonte){
	Fonte fonte = NULL;
	
	// Abre a fonte
	fonte = TTF_OpenFont(localFonte, // Local onde esta a fonte
												tamanhoFonte); // Tamanho da fonte
	
	// Verifica se ocorreu um erro ao abrir a fonte
	if(fonte == NULL)
		salvarErro(rsprintf("Erro na funcao 'TTF_OpenFont' de 'abrirFonte': %s\n", 
						TTF_GetError()));
	
	return fonte;
}



// Objetivo: Transformar um texto em uma superficie
// Parametros: A fonte do texto, o endereco da string que contem o texto e a cor do texto
// Retorno: A superficie do texto ou NULL se ocorrer um erro
Superficie textoParaSuperficie(Fonte fonteTexto, char *texto, Cor corTexto){
	Superficie superficeTexto = NULL;
	SDL_Color colorText = {corTexto.r, corTexto.g, corTexto.b, 
													corTexto.opacidade};
	
	//Transforma o texto em uma superficie
	superficeTexto = TTF_RenderText_Solid(fonteTexto, texto, colorText);
	
	// Verifica se ocorreu um erro ao transformar o text em superficie
	if(superficeTexto == NULL) 
		salvarErro(rsprintf("Erro na funcao 'TTF_RenderText_Solid' de 'textoParaSuperficie': %s\n", 
						TTF_GetError()));
	
	return superficeTexto;
}



// Objetivo: Transformar uma superficie em textura
// Parametros: O painel onde ficara a superficie e a superficie que sera transformada
// Retorno: A textura criada ou NULL se ocorrer um erro
Textura superficieParaTextura(Painel painelDestino, Superficie superficieTransformar){
	Textura novaTextura = NULL;
	
	// Cria uma textura apartir da superficie
	novaTextura = SDL_CreateTextureFromSurface(painelDestino, 
																							superficieTransformar);
	
	// Verifica se ocorreu um erro ao criar a textura
	if(novaTextura == NULL) 
		salvarErro(rsprintf("Erro na funcao 'SDL_CreateTextureFromSurface' de 'superficieParaTextura': %s\n", 
						SDL_GetError()));
	
	return novaTextura;
}



// Objetivo: Limpar a memoria usada pela superficie
// Parametro: A superficie a ser limpa
void limparSuperficie(Superficie superficieLimpar){
	// Limpa a superficie
	SDL_FreeSurface(superficieLimpar);
}



// Objetivo: Copiar uma parte ou toda a textura para um painel
// Parametros: O painel onde ficara a textura, a textura que sera copiada para o painel 
//							e o retangulo com o tamanho que sera 
//							usado pela textura no painel
// Retorno: 0 - Se a textura foi copiada para o painel com sucesso ou o codigo do erro 
//					 que ocorreu
int copiarTexturaPainel(Painel painelDestino, Textura texturaCopiar, 
												 Retangulo retanguloTextura){
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
		salvarErro(rsprintf("Erro na funcao 'SDL_RenderCopyEx' de 'copiarTexturaPainel': %s\n", 
						SDL_GetError()));
	
	return res;
}



// Objetivo: Atualizar um painel
// Parametro: O painel a ser atualizado
void atualizarPainel(Painel painelAtualizar){
	SDL_RenderPresent(painelAtualizar);
}



// Objetivo: Pintar no painel um texto
// Parametros: O endereco da string que contem o texto que será pintado, o painel de 
//							destino e a posicao X e Y de onde ficara o texto, a fonte do texto
//							e a cor do texto
// Retorno: A estrutura Componente contendo todos os dados do texto
Componente pintarTextoPainel(char *textoPintar, Painel painelDestino, int posX, 
															int posY, Fonte fonteTexto, Cor corFonte){
	Componente componenteTexto;
	int copiadaSucesso = 0;
	
	// Define o painel de destino na estrutura do componente
	componenteTexto.painelPertencente = painelDestino;
	
	// Transforma o texto em superficie e atribui a superficie na estrutura
	componenteTexto.superficie = textoParaSuperficie(fonteTexto, textoPintar, corFonte);
	
	// Verifica se ocorreu um erro ao criar a superficie
	if(componenteTexto.superficie == NULL)
		salvarErro("Erro na funcao 'textoParaSuperficie' de 'pintarTextoPainel'\n");
	
	// Define as coordenadas da area ocupada pelo texto dentro do painel
	componenteTexto.area.x = posX;
	componenteTexto.area.y = posY;
	componenteTexto.area.h = componenteTexto.superficie->h;
	componenteTexto.area.w = componenteTexto.superficie->w;
	
	// Cria a textura do texto apartir da superficie
	componenteTexto.textura = superficieParaTextura(componenteTexto.painelPertencente, 
																	 componenteTexto.superficie);
	
	// Verifica se ocorreu um erro ao criar a textura
	if(componenteTexto.textura == NULL)
		salvarErro("Erro na funcao 'superficieParaTextura' de 'pintarTextoPainel'\n");
	
	// Copia a textura para o painel
	copiadaSucesso = copiarTexturaPainel(componenteTexto.painelPertencente, 
																			 componenteTexto.textura, componenteTexto.area);
	
	// Verifica se ocorreu um erro ao copiar a textura para o painel
	if(!copiadaSucesso)
		salvarErro("Erro na funcao 'copiarTexturaPainel' de 'pintarTextoPainel'\n");
		
	return componenteTexto;
}



// Objetivo: Criar uma nova superficie
// Parametros: A largura e a altura da superficie
// Retorno: A superficie criada ou NULL se ocorrer um erro
Superficie criarSuperficie(int largura, int altura){
	Superficie super;
	
	// Cria a superficie no formato RGB
	super = SDL_CreateRGBSurface(0, // Tipo de superficie
															 largura, // largura da superficie
															 altura, // Altura da superficie
															 32, // Quantidade de bites nas mascaras RGB
															 0, // Mascara R
															 0, // Mascara G
															 0, // Mascara B
															 0); // Mascara A
	
	// Verificar se ocorreu um erro ao criar a superficie
	if(super == NULL)	
		salvarErro(rsprintf("Erro na funcao 'SDL_CreateRGBSurface' de 'criarSuperficie': %s\n", 
						SDL_GetError()));
	
	return super;
}



// Objetivo: Pintar toda uma superficie com uma cor
// Parametros: A superficie a ser pintada e a cor a ser pintada
// Retorno: 0 - Se a superficie foi pintada com sucesso ou o codigo de erro
int pintarSuperficie(Superficie superficiePintar, Cor corPintar){
	int ret = 0;
	
	// Pinta a superficie
	ret = SDL_FillRect(superficiePintar, // A superficie a ser pintada
											NULL, // Retangulo com as coordenadas do quadrado a ser pintado ou
														// NULL para toda a superficie
											SDL_MapRGB( // Pega o valor inteiro da cor a ser pintada no mesmo 
																	//formato de bits da superficie
																	superficiePintar->format, // Pega o formato de bits da 
																														//superficie
																	corPintar.r, // Cor vermelha
																	corPintar.g, // Cor verde
																	corPintar.b)); // Cor azul
	
	// Verifica se ocorreu erro ao pintar a superficie
	if(ret != 0)
		salvarErro(rsprintf("Erro na funcao 'SDL_FillRect' de 'pintarSuperficie': %s\n", 
						SDL_GetError()));
	
	return ret;
}



// Objetivo: Pintar um retangulo no painel
// Parametros: As coordenadas X e Y onde o retangulo sera pintado no painel, a largura e 
//							altura do retangulo, a cor do retangulo a ser pintado e o painel onde o 
//							retangulo sera pintado
// Retorno: A estrutura Componente contendo todos os dados do retangulo ou se ocorrer 
//					 um erro, o atributo da estrutura que ocorreu um erro sera NULL
Componente pintarRetanguloPainel(int posX, int posY, int largura, int altura, Cor cor, 
																	Painel painelDestino){
	Componente comp;
	comp.painelPertencente = painelDestino;
	comp.area.x = posX;
	comp.area.y = posY;
	comp.area.w = largura;
	comp.area.h = altura;
		
	// Criada superficie
	comp.superficie = criarSuperficie(comp.area.w, comp.area.h);
	
	// Verifica se ocorreu erro ao pintar a superficie
	if(comp.superficie == NULL){
		salvarErro("Erro na funcao 'criarSuperficie' de 'pintarRetanguloPainel'\n");
		return comp;
	}
	
	
	// Pinta a superficie e verifica se ocorreu erro quando ela foi pintada
	if(pintarSuperficie(comp.superficie, cor) != 0){
		salvarErro("Erro na funcao 'pintarSuperficie' de 'pintarRetanguloPainel'\n");
		return comp;
	}
		
	// Cria uma textura a partir da superficie
	comp.textura = superficieParaTextura(comp.painelPertencente, comp.superficie);
	
	// Verifica se ocorreu um erro ao criar a textura
	if(comp.textura == NULL){
		salvarErro("Erro na funcao 'superficieParaTextura' de 'pintarRetanguloPainel'\n");
		return comp;
	}
	
	// Copia a textura para o painel e verifica se ocorreu um erro ao copiar a textura
	if(copiarTexturaPainel(comp.painelPertencente, comp.textura, comp.area) != 0){
		salvarErro("Erro na funcao 'copiarTexturaPainel' de 'pintarRetanguloPainel'\n");
		return comp;
	}
	
	return comp;
}



// Objetivo: Pintar um retangulo no painel com cor de borda e cor de fundo diferentes
// Parametros: As coordenadas X e Y onde o retangulo sera pintado no painel, a largura e 
//							altura do retangulo, a largura da borda, a cor da borda, a cor de dentro
//							do retangulo a ser pintado e o painel onde o retangulo sera pintado
// Retorno: A estrutura Componente contendo todos os dados do retangulo ou se ocorrer 
//					 um erro, o atributo da estrutura que ocorreu um erro sera NULL
Componente pintarRetanguloCBordasPainel(int posX, int posY, int largura, int altura, 
																	int larguraBorda, Cor corBorda, Cor corFundo, 
																	Painel painelDestino){
	Componente comp;
	
	// Pinta um retangulo com a cor da borda
	comp = pintarRetanguloPainel(posX, posY, largura, altura, corBorda, painelDestino);
	
	// Verifica se ocorreu um erro ao pintar o primeiro retangulo
	if(comp.painelPertencente == NULL || comp.superficie == NULL || comp.textura == NULL){
		salvarErro("Erro na funcao 1 'pintarRetanguloPainel' de 'pintarRetanguloCBordasPainel'\n");
		return comp;
	}
	
	// Pinta outro retangulo dentro do primeiro com a cor do fundo
	Componente compDentro = pintarRetanguloPainel(posX + larguraBorda , posY + 
												 larguraBorda, largura - larguraBorda*2, altura - larguraBorda*2, 
												 corFundo, painelDestino);
												 
	// Verifica se ocorreu um erro ao pintar esse retangulo
	if(compDentro.painelPertencente == NULL || compDentro.superficie == NULL || 
			compDentro.textura == NULL){
		salvarErro("Erro na funcao 2 'pintarRetanguloPainel' de 'pintarRetanguloCBordasPainel'\n");
		return comp;
	}
	
	return comp;
}



// Objetivo: Pintar em um painel uma tabela
// Parametros: As coordenadas X e Y onde a tabela sera pintada no painel, a largura e 
//							altura da tabela, a largura da borda, a cor da borda, a cor de dentro
//							de cada celula a ser pintada, a quantidade de colunas da tabela, a 
//							quantidade de linhas da tabela e o painel onde o retangulo sera pintado
// Retorno: A estrutura Componente contendo todos os dados do retangulo ou se ocorrer 
//					 um erro, o atributo da estrutura que ocorreu um erro sera NULL
Componente pintarTabelaPainel(int posX, int posY, int largura, int altura, 
															 int larguraBorda, Cor corBorda, Cor corFundo, 
															 int qtdColunas, int qtdLinhas, Painel painelDestino){
	Componente comp, compAux;
	comp.painelPertencente = painelDestino;
	
	pintarRetanguloPainel(posX, posY, largura, altura, corBorda, painelDestino);
	
	comp.area.x = posX + larguraBorda;
	comp.area.y = posY + larguraBorda;
	comp.area.w = largura - (larguraBorda*2);
	comp.area.h = altura - (larguraBorda*2);
	
	int linha, coluna, larguraCelula, alturaCelula, posXCelula, posYCelula;
	
	larguraCelula = comp.area.w / qtdColunas;
	alturaCelula = comp.area.h / qtdLinhas;
	//printf("%d - %d\n", alturaCelula, alturaCelula*5);
	
	
	for(linha = 1; linha <= qtdLinhas; linha++){
		for(coluna = 1; coluna <= qtdColunas; coluna++){
			if(linha == qtdLinhas && 
					(comp.area.y + (alturaCelula * linha) - (posY + comp.area.h)) < 0){
				//alturaCelula += (-1 * (comp.area.y + (alturaCelula * linha) - (posY + comp.area.h)));
				posYCelula = (altura / qtdLinhas) + 
												(-1 * (comp.area.y + (alturaCelula * linha) - (posY + comp.area.h)));
			}else{
				posYCelula = comp.area.h / qtdLinhas;
			}
			if(coluna == qtdColunas && 
					(comp.area.x + (larguraCelula * coluna) - (posX + comp.area.w)) < 0){
				//alturaCelula += (-1 * (comp.area.y + (alturaCelula * linha) - (posY + comp.area.h)));
				posXCelula = (largura / qtdColunas) + 
												(-1 * (comp.area.x + (larguraCelula * coluna) - (posX + comp.area.w)));
			}else{
				posXCelula = comp.area.w / qtdColunas;
			}
			
			//printf("-> %d \n", (comp.area.y + (alturaCelula * (linha))) - (posY + comp.area.h));
			//printf(" %d\n", altura - (comp.area.y + (alturaCelula * (linha))));
			//printf(" %d\n", (comp.area.x + (larguraCelula * (coluna))));
			compAux = pintarRetanguloCBordasPainel((comp.area.x + (larguraCelula * (coluna -1))),
																		(comp.area.y + (alturaCelula * (linha -1))),
																		posXCelula,
																		posYCelula, 
																		larguraBorda,
																		corBorda,
																		corFundo, 
																		painelDestino);
			/*printf("%d - %d | %d  %d\n", linha, coluna, 
							(comp.area.x + (larguraCelula * coluna)),
							(comp.area.y + (alturaCelula * linha)));*/
			if(compAux.painelPertencente == NULL || compAux.superficie == NULL || 
					compAux.textura == NULL){
				salvarErro(rsprintf("Erro na funcao %d %d 'pintarTabelaPainel' de 'pintarRetanguloCBordasPainel'\n",
														linha, coluna));
				return compAux;
			}
		}
	}
	
	comp.superficie = compAux.superficie;
	comp.textura = compAux.textura;
	comp.area.x = posX;
	comp.area.y = posY;
	//comp.area.w = largura;
	//comp.area.h = altura;
	
	return comp;	
}



// Objetivo: 
Componente pintarDadoTabela(Componente tabelaDestino, int linhaTabela, int colunaTabela, 
														 int espacamentoCelula, char *dado, Fonte fonteTexto, 
														 Cor corTexto){
	Retangulo rect;
	int larguraCelula, alturaCelula, posXDado, posYDado, larguraDado, alturaDado;
	Superficie superficieDado;
	
	superficieDado = textoParaSuperficie(fonteTexto, dado, corTexto);
	larguraDado = superficieDado->w;
	alturaDado = superficieDado->h;
	larguraCelula = tabelaDestino.superficie->w;
	alturaCelula = tabelaDestino.superficie->h;
	posXDado = tabelaDestino.area.x + (larguraCelula * (colunaTabela - 1)) + 
							((larguraCelula - larguraDado) / 2);
	posYDado = tabelaDestino.area.y + (alturaCelula * (linhaTabela - 1)) + 
							((alturaCelula - alturaDado) / 2);
	
	pintarTextoPainel(dado, tabelaDestino.painelPertencente, posXDado, posYDado, 
										 fonteTexto, corTexto);
	
}

#endif /* _FUNCOES_JANELA_C_ */
