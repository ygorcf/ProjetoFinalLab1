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
	Cor branco = BRANCO;
	Painel painel = NULL;
  painel = SDL_CreateRenderer(janela, // A janela onde ficara o painel
														-1, // O index do driver de renderizacao ou -1 para
																//	o primeiro driver
														0); // O tipo de rederizacao
	
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
Superficie textoParaSuperficie(char *texto, Fonte fonteTexto){
	Superficie superficeTexto = NULL;
	SDL_Color colorText = {178, 34, 34, 255};
	
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
Componente pintarTextoPainel(char *textoPintar, Painel painelDestino, int posX, int posY, 
															Fonte fonteTexto){
	Componente componenteTexto;
	Superficie super;
	Textura tex;
	int copiadaSucesso = 0;
	Cor corFonte = COR_PRINCIPAL;
	
	if(textoPintar > 0){
	// Transforma o texto em superficie e atribui a superficie na estrutura
	super = textoParaSuperficie(textoPintar, fonteTexto);
	
	// Verifica se ocorreu um erro ao criar a superficie
	if(super == NULL)
		salvarErro("Erro na funcao 'textoParaSuperficie' de 'pintarTextoPainel'\n");
		
		// Define as coordenadas da area ocupada pelo texto dentro do painel
		componenteTexto.area.x = posX;
		componenteTexto.area.y = posY;
		componenteTexto.area.h = super->h;
		componenteTexto.area.w = super->w;
		
		// Cria a textura do texto apartir da superficie
		tex = superficieParaTextura(painelDestino, super);
																		 
		limparSuperficie(super);
		
		// Verifica se ocorreu um erro ao criar a textura
		if(tex == NULL)
			salvarErro("Erro na funcao 'superficieParaTextura' de 'pintarTextoPainel'\n");
		
		// Copia a textura para o painel
		copiadaSucesso = copiarTexturaPainel(painelDestino, tex, componenteTexto.area);
		
		SDL_DestroyTexture(tex);
		
		// Verifica se ocorreu um erro ao copiar a textura para o painel
		if(copiadaSucesso)
			salvarErro("Erro na funcao 'copiarTexturaPainel' de 'pintarTextoPainel'\n");
			
		// Define o painel de destino na estrutura do componente
		componenteTexto.painelPertencente = painelDestino;
	}
	
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
	Superficie super;
	Textura tex;
	comp.area.x = posX;
	comp.area.y = posY;
	comp.area.w = largura;
	comp.area.h = altura;
		
	// Criada superficie
	super = criarSuperficie(comp.area.w, comp.area.h);
	
	// Verifica se ocorreu erro ao pintar a superficie
	if(super == NULL){
		salvarErro("Erro na funcao 'criarSuperficie' de 'pintarRetanguloPainel'\n");
		return comp;
	}
	
	
	// Pinta a superficie e verifica se ocorreu erro quando ela foi pintada
	if(pintarSuperficie(super, cor) != 0){
		salvarErro("Erro na funcao 'pintarSuperficie' de 'pintarRetanguloPainel'\n");
		return comp;
	}
		
	// Cria uma textura a partir da superficie
	tex = superficieParaTextura(painelDestino, super);
	
	// Verifica se ocorreu um erro ao criar a textura
	if(tex == NULL){
		salvarErro("Erro na funcao 'superficieParaTextura' de 'pintarRetanguloPainel'\n");
		return comp;
	}			 
	limparSuperficie(super);
	
	// Copia a textura para o painel e verifica se ocorreu um erro ao copiar a textura
	if(copiarTexturaPainel(painelDestino, tex, comp.area) != 0){
		salvarErro("Erro na funcao 'copiarTexturaPainel' de 'pintarRetanguloPainel'\n");
		return comp;
	}
	
	SDL_DestroyTexture(tex);
	comp.painelPertencente = painelDestino;
	
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
	
	// Pinta um retangulo para ser a borda
	comp = pintarRetanguloPainel(posX, posY, largura, altura, corBorda, painelDestino);
	
	// Verifica se ocorreu um erro ao pintar o primeiro retangulo
	if(comp.painelPertencente == NULL){
		salvarErro("Erro na funcao 1 'pintarRetanguloPainel' de 'pintarRetanguloCBordasPainel'\n");
		return comp;
	}
	
	// Pinta outro retangulo dentro do primeiro com a cor do fundo
	Componente compDentro = pintarRetanguloPainel(posX + larguraBorda , posY + 
												 larguraBorda, largura - larguraBorda*2, altura - larguraBorda*2, 
												 corFundo, painelDestino);
												 
	// Verifica se ocorreu um erro ao pintar esse retangulo
	if(compDentro.painelPertencente == NULL){
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
	int linha, coluna, larguraCelula, alturaCelula, posXCelula, posYCelula;
	
	// Pinta um retangulo para ser a borda
	comp = pintarRetanguloPainel(posX, posY, largura, altura, corBorda, painelDestino);
	
	// Verifica se ocorreu um erro ao pintar o retangulo da borda
	if(comp.painelPertencente == NULL){
		salvarErro("Erro na funcao 1 'pintarRetanguloPainel' de 'pintarRetanguloCBordasPainel'\n");
		return comp;
	}
	
	Retangulo areaTabelaSBorda = {posX + larguraBorda, posY + larguraBorda, 
																 largura - (larguraBorda*2), altura - (larguraBorda*2)};
	comp.area.x = posX + larguraBorda;
	comp.area.y = posY + larguraBorda;
	comp.area.w = largura - (larguraBorda*2);
	comp.area.h = altura - (larguraBorda*2);
	
	
	larguraCelula = areaTabelaSBorda.w / qtdColunas;
	alturaCelula = areaTabelaSBorda.h / qtdLinhas;
	
	
	for(linha = 1; linha <= qtdLinhas; linha++){
		for(coluna = 1; coluna <= qtdColunas; coluna++){
			if(linha == qtdLinhas && (areaTabelaSBorda.y + (alturaCelula * linha) - 
					(posY + areaTabelaSBorda.h)) < 0){
				posYCelula = (altura / qtdLinhas) + 
											 (-1 * (areaTabelaSBorda.y + (alturaCelula * linha) - 
											 (posY + areaTabelaSBorda.h)));
			}else{
				posYCelula = areaTabelaSBorda.h / qtdLinhas;
			}
			if(coluna == qtdColunas && (areaTabelaSBorda.x + (larguraCelula * coluna) - 
					(posX + areaTabelaSBorda.w)) < 0){
				posXCelula = (largura / qtdColunas) + 
											 (-1 * (areaTabelaSBorda.x + (larguraCelula * coluna) - 
											 (posX + areaTabelaSBorda.w)));
			}else{
				posXCelula = areaTabelaSBorda.w / qtdColunas;
			}
			compAux = pintarRetanguloCBordasPainel((areaTabelaSBorda.x + (larguraCelula * 
																							(coluna -1))),
																							(areaTabelaSBorda.y + (alturaCelula * 
																							(linha -1))),
																							posXCelula,
																							posYCelula, 
																							larguraBorda,
																							corBorda,
																							corFundo, 
																							painelDestino);
			if(compAux.painelPertencente == NULL){
				salvarErro(rsprintf("Erro na funcao %d %d 'pintarTabelaPainel' de 'pintarRetanguloCBordasPainel'\n",
														linha, coluna));
				return compAux;
			}
		}
	}
	
	comp.painelPertencente = painelDestino;
	comp.area.x = posX;
	comp.area.y = posY;
	comp.area.w = largura;
	comp.area.h = altura;
	comp.areaAux.w = compAux.area.w;
	comp.areaAux.h = compAux.area.h;
	
	return comp;	
}



// Objetivo: 
Componente pintarDadoTabela(Componente tabelaDestino, int linhaTabela, int colunaTabela, 
														 int espacamentoCelula, char *dado){
	Retangulo rect;
	int larguraCelula, alturaCelula, posXDado, posYDado, larguraDado, alturaDado;
	Superficie superficieDado;
	Cor corTexto = COR_PRINCIPAL;
	
	superficieDado = textoParaSuperficie(dado, FONTE_TEXTO_PRINCIPAL);
	larguraDado = superficieDado->w;
	alturaDado = superficieDado->h;
	limparSuperficie(superficieDado);
	larguraCelula = tabelaDestino.areaAux.w;
	alturaCelula = tabelaDestino.areaAux.h;
	posXDado = tabelaDestino.area.x + (larguraCelula * (colunaTabela - 1)) + 
							((larguraCelula - larguraDado) / 2);
	posYDado = tabelaDestino.area.y + (alturaCelula * (linhaTabela - 1)) + 
							((alturaCelula - alturaDado) / 2);
	
	pintarTextoPainel(dado, tabelaDestino.painelPertencente, posXDado, posYDado, FONTE_TEXTO_PRINCIPAL);
	
}



// Objetivo: 
Componente retirarUltimaLetraTextoPainel(char *texto, Componente componenteTexto){
	Cor corTexto = COR_PRINCIPAL;
	rTirarCaracter(texto);
	if(strlen(texto) < 33){
	  Superficie superAux = textoParaSuperficie(texto, FONTE_TEXTO_PRINCIPAL);
	  Retangulo rectAux;
		if(strlen(texto) > 0){
		  rectAux.x = (componenteTexto.area.x + superAux->w);
		  rectAux.y = componenteTexto.area.y;
		  rectAux.w = componenteTexto.area.w - superAux->w;
		  rectAux.h = superAux->h;
			componenteTexto = pintarTextoPainel(texto, componenteTexto.painelPertencente, componenteTexto.area.x, componenteTexto.area.y, FONTE_TEXTO_PRINCIPAL);
		}else{
		  rectAux = componenteTexto.area;
		}
		limparSuperficie(superAux);
		pintarRetanguloPainel(rectAux.x, rectAux.y, rectAux.w, rectAux.h, BRANCO, componenteTexto.painelPertencente);
		atualizarPainel(componenteTexto.painelPertencente);
	}
	return componenteTexto;
}



// Objetivo: 
Painel limparPainel(Painel painelLimpar, Janela janelaPertencente){
	SDL_SetRenderDrawColor(painelLimpar, 255, 255, 255, 255);
	SDL_RenderFillRect(painelLimpar, NULL);
	SDL_RenderPresent(painelLimpar);
	return painelLimpar;
}



// Objetivo:
int pintarMenuPrincipal(Janela janela, Painel painelDestino, Cor corFundo, Cor corPrincipal){
	int ret = 0, sair = 0;
	Fonte fonteTexto = FONTE_TEXTO_PRINCIPAL;
	Fonte fonteTitulo = abrirFonte("Ubuntu-M.ttf", 22);
	Componente compTitulo, compNomePiloto, compSair;
	
	limparPainel(painelDestino, janela);
	compTitulo = pintarTextoPainel("MENU PRINCIPAL", painelDestino, 200, 10, FONTE_TITULO_PRINCIPAL);
	pintarTextoPainel("Pilotos", painelDestino, 10, 40, FONTE_TEXTO_PRINCIPAL);
	compSair = pintarTextoPainel("SAIR", painelDestino, 10, 460, FONTE_TEXTO_PRINCIPAL);
	/*compNomePiloto = pintarTextoPainel("Nome do Piloto:", painelDestino, 10, 60, fonteTexto, corPrincipal);
	compSair = pintarTextoPainel("SAIR", painelDestino, 10, 460, fonteTexto, corPrincipal);
	pintarRetanguloCBordasPainel((compNomePiloto.area.x + compNomePiloto.area.w + 10), compNomePiloto.area.y, 300, 21, 1, corPrincipal, corFundo, painelDestino);
	atualizarPainel(painelDestino);
	
	SDL_Event event;
	while(sair){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_MOUSEBUTTONUP){
        SDL_Point posMouse;
        SDL_GetMouseState(&posMouse.x, &posMouse.y);
        if(pontoDentroRetangulo(&posMouse, &compSair)){
          sair = 1;
				}
      }
		}
	}*/
	
	return 0;
}



// Objetivo:
int pintarMenuPilotos(Janela janela, Painel painelDestino, Cor corFundo, Cor corPrincipal){
	int ret = 0, sair = 0;
	Fonte fonteTexto = abrirFonte("Ubuntu-M.ttf", 16);
	Fonte fonteTitulo = abrirFonte("Ubuntu-M.ttf", 22);
	Componente compTitulo, compNovoPiloto, compSair;
	
	limparPainel(painelDestino, janela);
	compTitulo = pintarTextoPainel("PILOTOS", painelDestino, 200, 10, FONTE_TITULO_PRINCIPAL);
	compNovoPiloto = pintarTextoPainel("Novo Piloto", painelDestino, 10, 40, FONTE_TEXTO_PRINCIPAL);
	compSair = pintarTextoPainel("SAIR", painelDestino, 10, 460, FONTE_TEXTO_PRINCIPAL);
	//compNomePiloto = pintarTextoPainel("Novo Piloto", painelDestino, 10, 60, fonteTexto, corPrincipal);
	//compSair = pintarTextoPainel("SAIR", painelDestino, 10, 460, fonteTexto, corPrincipal);
	//pintarRetanguloCBordasPainel((compNomePiloto.area.x + compNomePiloto.area.w + 10), compNomePiloto.area.y, 300, 21, 1, corPrincipal, corFundo, painelDestino);
	atualizarPainel(painelDestino);
	SDL_Event evento;
	while(!sair){
		while(SDL_WaitEvent(&evento)){
			if(evento.type == SDL_MOUSEBUTTONUP){
        SDL_Point posMouse;
        SDL_GetMouseState(&posMouse.x, &posMouse.y);
        if(pontoDentroRetangulo(&posMouse, &compSair.area)){
          sair = 1;
          break;
				}else if(pontoDentroRetangulo(&posMouse, &compNovoPiloto.area)){
          if(pintarMenuNovoPiloto(janela, painelDestino, corFundo, corPrincipal) == 0){
						painelDestino = limparPainel(painelDestino, janela);
						pintarMenuPilotos(janela, painelDestino, corFundo, corPrincipal);
					}
				}
      }
  }
	}
	return 0;
}



// Objetivo:
int pintarMenuNovoPiloto(Janela janela, Painel painelDestino, Cor corFundo, Cor corPrincipal){
	int ret = 0, sair = 0, atualizaPainel = 0, campoAtivo = 0, renderText;
	Fonte fonteTexto = abrirFonte("Ubuntu-M.ttf", 16);
	Fonte fonteTitulo = abrirFonte("Ubuntu-M.ttf", 22);
	Componente compTitulo, compNomePiloto, compSair, compIdadePiloto, compSexoPiloto, 
	compPaisNatalPiloto, compNomePilotoUser, compSairUser, compIdadePilotoUser, 
	compSexoPilotoMUser, compSexoPilotoFUser, compPaisNatalPilotoUser, compAtualizar,
	compNomePilotoDigitado;
	char nomePiloto[127];
	memset(nomePiloto, '\0', sizeof(nomePiloto));
	
	compAtualizar.painelPertencente = NULL;
	
	limparPainel(painelDestino, janela);
	compTitulo = pintarTextoPainel("NOVO PILOTO", painelDestino, 200, 10, FONTE_TITULO_PRINCIPAL);
	compNomePiloto = pintarTextoPainel("Nome do Piloto:", painelDestino, 10, 60, FONTE_TEXTO_PRINCIPAL);
	compIdadePiloto = pintarTextoPainel("Idade do Piloto:", painelDestino, 10, 100, FONTE_TEXTO_PRINCIPAL);
	compSexoPiloto = pintarTextoPainel("Sexo do Piloto:", painelDestino, 10, 140, FONTE_TEXTO_PRINCIPAL);
	compPaisNatalPiloto = pintarTextoPainel("Pais natal do Piloto:", painelDestino, 10, 180, FONTE_TEXTO_PRINCIPAL);
	compSair = pintarTextoPainel("SAIR", painelDestino, 10, 460, FONTE_TEXTO_PRINCIPAL);
	compNomePilotoUser = pintarRetanguloCBordasPainel((compNomePiloto.area.x + compNomePiloto.area.w + 10), compNomePiloto.area.y, 300, 30, 1, corPrincipal, corFundo, painelDestino);
	compIdadePilotoUser = pintarRetanguloCBordasPainel((compIdadePiloto.area.x + compIdadePiloto.area.w + 10), compIdadePiloto.area.y, 300, 30, 1, corPrincipal, corFundo, painelDestino);
	compSexoPilotoMUser = pintarRetanguloCBordasPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 10), compSexoPiloto.area.y, 30, 30, 3, corPrincipal, corFundo, painelDestino);
	compSexoPilotoFUser = pintarRetanguloCBordasPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 50), compSexoPiloto.area.y, 30, 30, 1, corPrincipal, corFundo, painelDestino);
	compPaisNatalPilotoUser = pintarRetanguloCBordasPainel((compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 10), compPaisNatalPiloto.area.y, 300, 30, 1, corPrincipal, corFundo, painelDestino);
	atualizarPainel(painelDestino);
	
	SDL_Event event;
	SDL_StartTextInput();
	while(!sair){
		renderText = 0;
		while(SDL_WaitEvent(&event)){
			if(event.type == SDL_MOUSEBUTTONUP){
        SDL_Point posMouse;
        SDL_GetMouseState(&posMouse.x, &posMouse.y);
        if(pontoDentroRetangulo(&posMouse, &compSair.area)){
          sair = 1;
          break;
				}else if(pontoDentroRetangulo(&posMouse, &compNomePilotoUser.area)){
					if(compAtualizar.painelPertencente != NULL){
						pintarRetanguloCBordasPainel(compAtualizar.area.x, compAtualizar.area.y, 300, 30, 3, corFundo, corFundo, painelDestino);
						pintarRetanguloCBordasPainel(compAtualizar.area.x, compAtualizar.area.y, 300, 30, 1, corPrincipal, corFundo, painelDestino);
						
						compAtualizar.painelPertencente = NULL;
					}
					compAtualizar = pintarRetanguloCBordasPainel((compNomePiloto.area.x + compNomePiloto.area.w + 10), compNomePiloto.area.y, 300, 30, 3, corPrincipal, corFundo, painelDestino);
					campoAtivo = 1;
					//atualizarPainel(painelDestino);
					atualizaPainel = 1;
        }else if(pontoDentroRetangulo(&posMouse, &compIdadePilotoUser.area)){
					if(compAtualizar.painelPertencente != NULL){
						pintarRetanguloCBordasPainel(compAtualizar.area.x, compAtualizar.area.y, 300, 30, 3, corFundo, corFundo, painelDestino);
						pintarRetanguloCBordasPainel(compAtualizar.area.x, compAtualizar.area.y, 300, 30, 1, corPrincipal, corFundo, painelDestino);
						
						compAtualizar.painelPertencente = NULL;
					}
					compAtualizar = pintarRetanguloCBordasPainel((compIdadePiloto.area.x + compIdadePiloto.area.w + 10), compIdadePiloto.area.y, 300, 30, 3, corPrincipal, corFundo, painelDestino);
					campoAtivo = 2;
					atualizarPainel(painelDestino);
        }else if(pontoDentroRetangulo(&posMouse, &compSexoPilotoMUser.area)){
					pintarRetanguloCBordasPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 50), compSexoPiloto.area.y, 30, 30, 3, corFundo, corFundo, painelDestino);
					pintarRetanguloCBordasPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 50), compSexoPiloto.area.y, 30, 30, 1, corPrincipal, corFundo, painelDestino);
					pintarRetanguloCBordasPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 10), compSexoPiloto.area.y, 30, 30, 3, corPrincipal, corFundo, painelDestino);
					atualizarPainel(painelDestino);
        }else if(pontoDentroRetangulo(&posMouse, &compSexoPilotoFUser.area)){
					pintarRetanguloCBordasPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 10), compSexoPiloto.area.y, 30, 30, 3, corFundo, corFundo, painelDestino);
					pintarRetanguloCBordasPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 10), compSexoPiloto.area.y, 30, 30, 1, corPrincipal, corFundo, painelDestino);
					pintarRetanguloCBordasPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 50), compSexoPiloto.area.y, 30, 30, 3, corPrincipal, corFundo, painelDestino);
					atualizarPainel(painelDestino);
        }else if(pontoDentroRetangulo(&posMouse, &compPaisNatalPilotoUser.area)){
					if(compAtualizar.painelPertencente != NULL){
						pintarRetanguloCBordasPainel(compAtualizar.area.x, compAtualizar.area.y, 300, 30, 3, corFundo, corFundo, painelDestino);
						pintarRetanguloCBordasPainel(compAtualizar.area.x, compAtualizar.area.y, 300, 30, 1, corPrincipal, corFundo, painelDestino);
						
						compAtualizar.painelPertencente = NULL;
					}
					compAtualizar = pintarRetanguloCBordasPainel((compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 10), compPaisNatalPiloto.area.y, 300, 30, 3, corPrincipal, corFundo, painelDestino);
					campoAtivo = 3;
					atualizarPainel(painelDestino);
        }else{
        	if(compAtualizar.painelPertencente){
						pintarRetanguloCBordasPainel(compAtualizar.area.x, compAtualizar.area.y, 300, 30, 3, corFundo, corFundo, painelDestino);
						pintarRetanguloCBordasPainel(compAtualizar.area.x, compAtualizar.area.y, 300, 30, 1, corPrincipal, corFundo, painelDestino);
						
						compAtualizar.painelPertencente = NULL;
						//if(strlen(nomePiloto) > 0 && strlen(nomePiloto) < 33)
						//	compNomePilotoDigitado = pintarTextoPainel(nomePiloto, painelDestino, (compNomePiloto.area.x + compNomePiloto.area.w + 15), compNomePiloto.area.y+5, fonteTexto, corPrincipal);
      			//atualizarPainel(painelDestino);
      			atualizaPainel = 1;
      			renderText = 1;
					}
					campoAtivo = 0;
				}
      } else if( event.type == SDL_KEYDOWN ){
		  	if( event.key.keysym.sym == SDLK_BACKSPACE && strlen(nomePiloto) > 0 ){
          retirarUltimaLetraTextoPainel(nomePiloto, compNomePilotoDigitado);
        }
        /*//Handle copy
        else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
        {
            SDL_SetClipboardText( inputText );
            printf("COPY\n");
        }
        //Handle paste
        else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
        {
            strcpy(inputText, SDL_GetClipboardText());
            renderText = 1;
            printf("PASTE\n");
        }*/
      } else if( event.type == SDL_TEXTINPUT ){
		    if( !( ( event.text.text[ 0 ] == 'c' || event.text.text[ 0 ] == 'C' ) && ( event.text.text[ 0 ] == 'v' || event.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) ){
		      if(campoAtivo == 1){
						strcat(nomePiloto, event.text.text);
					} else if(campoAtivo == 2){
						
					} else if(campoAtivo == 3){
						
					}
		      renderText = 1;
		      atualizaPainel = 1;
		    }
		  }
			if(renderText){
				if(strlen(nomePiloto) <= 32 && strlen(nomePiloto) > 0){
		      if( nomePiloto != "" ){
		        compNomePilotoDigitado = pintarTextoPainel(nomePiloto, painelDestino, (compNomePiloto.area.x + compNomePiloto.area.w + 15), compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL);
		      }else{
		        compNomePilotoDigitado = pintarTextoPainel(" ", painelDestino, (compNomePiloto.area.x + compNomePiloto.area.w + 10), compNomePiloto.area.y, FONTE_TEXTO_PRINCIPAL);
		      }
				}
	      renderText = 0;
	    }
			if(atualizaPainel){
				atualizaPainel = 0;
				atualizarPainel(painelDestino);
			}
		}
	}
  SDL_StopTextInput();
	
	return 0;
}

#endif /* _FUNCOES_JANELA_C_ */
