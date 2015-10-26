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
		salvarErro("Erro na funcao 'SDL_CreateWindow' de 'criarJanela': %s\n", 
						SDL_GetError());
  
	return jan;					
}


// Objetivo: Criar um painel
// Parametro: A janela onde ficara o painel
// Retorno: O painel criado ou NULL se ocorrer um erro
Painel criarPainel(Janela janela){
	// Cria a cor branca
	Cor branco = BRANCO;
	Painel painel = NULL;
	Superficie surper;
  painel = SDL_CreateRenderer(janela, // A janela onde ficara o painel
														-1, // O index do driver de renderizacao ou -1 para
																//	o primeiro driver
														SDL_RENDERER_SOFTWARE); // O tipo de rederizacao
	
	//Verifica se ocorreu um erro ao criar o painel
	if(painel == NULL)
		salvarErro("Erro na funcao 'SDL_CreateRenderer' de 'criarPainel': %s\n", 
						SDL_GetError());
	
	// Pinta o fundo do painel com a cor branca e verifica se ocorreu um erro ao 
	//	pintar o fundo
	if(alteraCorFundoPainel(painel, branco) != 0){
  	salvarErro("Erro na funcao 'alteraCorFundoPainel' de 'criarPainel': %s\n", 
						SDL_GetError());
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
  	salvarErro("Erro na funcao 'SDL_SetRenderDrawColor' de 'alteraCorFundoPainel': %s\n", 
						SDL_GetError());
		return 1;
	}
  // Pinta o fundo do painel com a nova cor e verifica se ocorreu um erro ao 
  // pinta-lo com essa cor
  if(SDL_RenderClear(painelAlterarCor) != 0){
  	salvarErro("Erro na funcao 'SDL_RenderClear' de 'alteraCorFundoPainel': %s\n", 
						SDL_GetError());
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
		salvarErro("Erro na funcao 'TTF_OpenFont' de 'abrirFonte': %s\n", 
						TTF_GetError());
	
	return fonte;
}



// Objetivo: Transformar um texto em uma superficie
// Parametros: A fonte do texto, o endereco da string que contem o texto e a cor do texto
// Retorno: A superficie do texto ou NULL se ocorrer um erro
Superficie textoParaSuperficie(char *texto, Fonte fonteTexto){
	Superficie superficeTexto = NULL;
	
	//Transforma o texto em uma superficie
	superficeTexto = TTF_RenderText_Solid(fonteTexto, texto, COR_FONTE_PRINCIPAL);
	
	// Verifica se ocorreu um erro ao transformar o text em superficie
	if(superficeTexto == NULL) 
		salvarErro("Erro na funcao 'TTF_RenderText_Solid' de 'textoParaSuperficie': %s\n", 
						TTF_GetError());
	
	TTF_CloseFont(fonteTexto);
	
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
		salvarErro("Erro na funcao 'SDL_CreateTextureFromSurface' de 'superficieParaTextura': %s\n", 
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
// Parametros: O painel onde ficara a textura, a textura que sera copiada para o painel 
//							e o retangulo com o tamanho que sera 
//							usado pela textura no painel
// Retorno: 0 - Se a textura foi copiada para o painel com sucesso ou o codigo do erro 
//					 que ocorreu
int copiarTexturaPainel(Painel painelDestino, Textura texturaCopiar, 
												 Retangulo retanguloTextura){
	int res = 0;
	
	// Copia a textura para o painel
	res = SDL_RenderCopy(painelDestino, // O painel onde ficara a textura
												texturaCopiar, // A textura a ser copiada
													NULL, // O tamanho que sera copiado da textura ou
																//	NULL para toda textura
													&retanguloTextura); // O tamanho que sera utilizado
	
	// Verifica se ocorreu um erro ao copiar a textura
	if(res != 0)
		salvarErro("Erro na funcao 'SDL_RenderCopyEx' de 'copiarTexturaPainel': %s\n", 
						SDL_GetError());
	
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
															Fonte fonteTexto, Janela janela){
	Componente componenteTexto;
	componenteTexto.painelPertencente == NULL;
	
	if(textoPintar > 0){
		Superficie super;
		//Textura tex;
		int copiadaSucesso = 0;
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
		//tex = superficieParaTextura(painelDestino, super);
												
		Superficie sJanela = SDL_GetWindowSurface(janela);
		SDL_BlitSurface(super, NULL, sJanela, &componenteTexto.area);
		SDL_UpdateWindowSurface(janela);
		limparSuperficie(sJanela);
		limparSuperficie(super);
		sJanela = 0;
		super = 0;
		
		// Verifica se ocorreu um erro ao criar a textura
		/*if(tex == NULL)
			salvarErro("Erro na funcao 'superficieParaTextura' de 'pintarTextoPainel'\n");
		
		// Copia a textura para o painel
		copiadaSucesso = copiarTexturaPainel(painelDestino, tex, componenteTexto.area);
		
		SDL_DestroyTexture(tex);
		
		// Verifica se ocorreu um erro ao copiar a textura para o painel
		if(copiadaSucesso)
			salvarErro("Erro na funcao 'copiarTexturaPainel' de 'pintarTextoPainel'\n");
<<<<<<< HEAD
			*/
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
		salvarErro("Erro na funcao 'SDL_CreateRGBSurface' de 'criarSuperficie': %s\n", 
						SDL_GetError());
	
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
		salvarErro("Erro na funcao 'SDL_FillRect' de 'pintarSuperficie': %s\n", 
						SDL_GetError());
	
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
	comp.area.x = posX;
	comp.area.y = posY;
	comp.area.w = largura;
	comp.area.h = altura;
	
	SDL_SetRenderDrawColor(painelDestino, cor.r, cor.g, cor.b, cor.opacidade);
	SDL_RenderDrawRect(painelDestino, &comp.area);
	comp.painelPertencente = painelDestino;
	
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
			compAux = pintarRetanguloPainel((areaTabelaSBorda.x + (larguraCelula * 
																			 (coluna -1))),
																			 (areaTabelaSBorda.y + (alturaCelula * 
																			 (linha -1))),
																			 posXCelula,
																			 posYCelula, 
																			 corBorda,
																			 painelDestino);
			if(compAux.painelPertencente == NULL){
				salvarErro("Erro na funcao %d %d 'pintarTabelaPainel' de 'pintarRetanguloCBordasPainel'\n",
														linha, coluna);

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
	
	//pintarTextoPainel(dado, tabelaDestino.painelPertencente, posXDado, posYDado, FONTE_TEXTO_PRINCIPAL);
	
}



// Objetivo: 
Componente retirarUltimaLetraTextoPainel(char *texto, Componente componenteTexto){
	Cor corTexto = COR_PRINCIPAL;
	Cor corFundo = COR_FUNDO;
	rTirarCaracter(texto);
	if(strlen(texto) < 33){
	  Superficie superAux = textoParaSuperficie(texto, FONTE_TEXTO_PRINCIPAL);
	  Retangulo rectAux;
		if(strlen(texto) > 0){
		  rectAux.x = componenteTexto.area.x + superAux->w;
		  rectAux.y = componenteTexto.area.y;
		  rectAux.w = componenteTexto.area.w - superAux->w;
		  rectAux.h = superAux->h;
			//componenteTexto = pintarTextoPainel(texto, componenteTexto.painelPertencente, componenteTexto.area.x, componenteTexto.area.y, FONTE_TEXTO_PRINCIPAL);

		}else{
		  rectAux = componenteTexto.area;
		}
		limparSuperficie(superAux);
		SDL_SetRenderDrawColor(componenteTexto.painelPertencente, corFundo.r, corFundo.g, corFundo.b, corFundo.opacidade);
		SDL_RenderFillRect(componenteTexto.painelPertencente, &rectAux);
		//componenteTexto = pintarRetanguloPainel(rectAux.x, rectAux.y, rectAux.w, rectAux.h, BRANCO, componenteTexto.painelPertencente);
		atualizarPainel(componenteTexto.painelPertencente);
	}
	return componenteTexto;
}



// Objetivo: Limpar todo o painel, pintando-o com a cor de fundo novamente
// Parametro: O painel que sera limpo
// Retorno: 0 - Se a funcao executar com sucesso
//					1 - Se ocorrer um erro
int limparPainel(Painel painelLimpar){
  if(alteraCorFundoPainel(painelLimpar, COR_FUNDO) != 0){
  	salvarErro("Erro na funcao 'alteraCorFundoPainel' de 'limparPainel'\n");
		return 1;
	}
	atualizarPainel(painelLimpar);
	return 0;
}



// Objetivo:
int checarEventoMenuPrincipal(Janela janela, Painel painelDestino){
	int sair = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compPilotos, compSair;
	Retangulo rect = {30,100,200,100};
	
	limparPainel(painelDestino);
	compTitulo = pintarTextoPainel("MENU PRINCIPAL", painelDestino, 180, 10, FONTE_TITULO_PRINCIPAL, janela);
	compPilotos = pintarTextoPainel("Pilotos", painelDestino, 10, 40, FONTE_TEXTO_PRINCIPAL, janela);
	compSair = pintarTextoPainel("SAIR", painelDestino, 10, 460, FONTE_TEXTO_PRINCIPAL, janela);
	//pintarRetanguloPainel(rect.x, rect.y, rect.w, rect.h, (Cor){0,0,128,255}, painelDestino);
		
	SDL_SetRenderDrawColor(painelDestino, 0, 0, 128, 255);
	SDL_RenderDrawRect(painelDestino, &rect);
	SDL_SetTextInputRect(&rect);

	atualizarPainel(painelDestino);
	
	SDL_Event evento;
	while(!sair){
		while(SDL_WaitEvent(&evento)){
      if(evento.type == SDL_QUIT){
        compClicado = CLICADO_FECHAR;
        sair = 1;
        break;
			} else if(evento.type == SDL_MOUSEBUTTONUP){
    		if(verificarCliqueDentroRetangulo(compSair.area)){
    			compClicado = CLICADO_SAIR;
    			sair = 1;
    			break;
				} else if(verificarCliqueDentroRetangulo(compPilotos.area)){
    			compClicado = CLICADO_PILOTOS;
    			sair = 1;
    			break;
				}
			}
			SDL_FlushEvent(evento.type);
		}
	}
	
	return compClicado;
}



// Objetivo:
int checarEventoMenuPilotos(Janela janela, Painel painelDestino){
	int sair = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compNovoPiloto, compVoltar;
	
	limparPainel(painelDestino);
	compTitulo = pintarTextoPainel("PILOTOS", painelDestino, 200, 10, FONTE_TITULO_PRINCIPAL, janela);
	compNovoPiloto = pintarTextoPainel("Novo Piloto", painelDestino, 10, 40, FONTE_TEXTO_PRINCIPAL, janela);
	compVoltar = pintarTextoPainel("VOLTAR", painelDestino, 10, 460, FONTE_TEXTO_PRINCIPAL, janela);

	atualizarPainel(painelDestino);
	SDL_Event evento;
	while(!sair){
		while(SDL_WaitEvent(&evento)){
      if(evento.type == SDL_QUIT){
	      compClicado = CLICADO_FECHAR;
	      sair = 1;
          break;
			}else if(evento.type == SDL_MOUSEBUTTONUP){
    		if(verificarCliqueDentroRetangulo(compVoltar.area)){
	  			compClicado = CLICADO_VOLTAR;
	  			sair = 1;
	  			break;
				} else if(verificarCliqueDentroRetangulo(compNovoPiloto.area)){
    			compClicado = CLICADO_NOVO_PILOTO;
    			sair = 1;
    			break;
				}
			}
			SDL_FlushEvent(evento.type);
  	}
	}
	return compClicado;
}



// Objetivo:
int checarEventoMenuNovoPiloto(Janela janela, Painel painelDestino){
	int ret = 0, sair = 0, campoAtivo = 0, pintarTexto = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compNomePiloto, compVoltar, compIdadePiloto, compSexoPiloto, 
	compPaisNatalPiloto, compNomePilotoUser, compSairUser, compIdadePilotoUser, 
	compSexoPilotoMUser, compSexoPilotoFUser, compPaisNatalPilotoUser, compAtualizar,
	compNomePilotoDigitado, compIdadePilotoDigitado, compSexoPilotoMText, compSexoPilotoFText, compCadastrar;
	compAtualizar.painelPertencente = NULL;
	compNomePilotoDigitado.area.w = 0;
	
	char nomePiloto[127], sexoPiloto = 'M', idadePilotoString[4];
	int idadePiloto;
	
	memset(nomePiloto, '\0', sizeof(nomePiloto));
	memset(idadePilotoString, '\0', sizeof(idadePilotoString));
	
	
	limparPainel(painelDestino);
	compTitulo = pintarTextoPainel("NOVO PILOTO", painelDestino, 200, 10, FONTE_TITULO_PRINCIPAL, janela);
	compNomePiloto = pintarTextoPainel("Nome do Piloto:", painelDestino, 10, 60, FONTE_TEXTO_PRINCIPAL, janela);
	compIdadePiloto = pintarTextoPainel("Idade do Piloto:", painelDestino, 10, 100, FONTE_TEXTO_PRINCIPAL, janela);
	compSexoPiloto = pintarTextoPainel("Sexo do Piloto:", painelDestino, 10, 140, FONTE_TEXTO_PRINCIPAL, janela);
	compPaisNatalPiloto = pintarTextoPainel("Pais natal do Piloto:", painelDestino, 10, 180, FONTE_TEXTO_PRINCIPAL, janela);
	compVoltar = pintarTextoPainel("Voltar", painelDestino, 10, 460, FONTE_TEXTO_PRINCIPAL, janela);
	compNomePilotoUser = pintarRetanguloPainel((compNomePiloto.area.x + compNomePiloto.area.w + 10), compNomePiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	compIdadePilotoUser = pintarRetanguloPainel((compIdadePiloto.area.x + compIdadePiloto.area.w + 10), compIdadePiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	compSexoPilotoMUser = pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 10), compSexoPiloto.area.y, 30, 30, COR_SELECIONADO, painelDestino);
	pintarTextoPainel("M", painelDestino, (compSexoPilotoMUser.area.x+10), (compSexoPilotoMUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janela);
	compSexoPilotoFUser = pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 50), compSexoPiloto.area.y, 30, 30, COR_PRINCIPAL, painelDestino);
	pintarTextoPainel("F", painelDestino, (compSexoPilotoFUser.area.x+10), (compSexoPilotoFUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janela);
	compPaisNatalPilotoUser = pintarRetanguloPainel((compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 10), compPaisNatalPiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	compCadastrar = pintarRetanguloPainel((compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 10), compPaisNatalPiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	atualizarPainel(painelDestino);
	
	SDL_Event event;
	SDL_StartTextInput();
	while(!sair){
		while(SDL_WaitEvent(&event)){
			if(event.type == SDL_QUIT){
				compClicado = CLICADO_FECHAR;
				sair = 1;
				break;
			}else if(event.type == SDL_MOUSEBUTTONUP){
				if(compAtualizar.painelPertencente != NULL){
					atualizarBordaComponente(&compAtualizar);
				}
				if(verificarCliqueDentroRetangulo(compVoltar.area)){
					compClicado = CLICADO_VOLTAR;
		      sair = 1;
		      break;
				}else if(verificarCliqueDentroRetangulo(compNomePilotoUser.area)){
					compAtualizar = pintarRetanguloPainel((compNomePiloto.area.x + compNomePiloto.area.w + 10), compNomePiloto.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(nomePiloto) <= 32 && strlen(nomePiloto) > 0)
						compNomePilotoDigitado = pintarTextoPainel(nomePiloto, painelDestino, (compNomePiloto.area.x + compNomePiloto.area.w + 15), compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janela);
					campoAtivo = 1;
				}else if(verificarCliqueDentroRetangulo(compIdadePilotoUser.area)){
					compAtualizar = pintarRetanguloPainel((compIdadePiloto.area.x + compIdadePiloto.area.w + 10), compIdadePiloto.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(idadePilotoString) <= 3 && strlen(idadePilotoString) > 0)
						pintarTextoPainel(idadePilotoString, painelDestino, (compIdadePiloto.area.x + compIdadePiloto.area.w + 15), compIdadePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janela);
					campoAtivo = 2;
        }else if(verificarCliqueDentroRetangulo(compSexoPilotoMUser.area)){
					pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 50), compSexoPiloto.area.y, 30, 30, COR_PRINCIPAL, painelDestino);
					pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 10), compSexoPiloto.area.y, 30, 30, COR_SELECIONADO, painelDestino);
					//pintarTextoPainel("M", painelDestino, (compSexoPilotoMUser.area.x+10), (compSexoPilotoMUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janela);
					//pintarTextoPainel("F", painelDestino, (compSexoPilotoFUser.area.x+10), (compSexoPilotoFUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janela);
					sexoPiloto = 'M';
        }else if(verificarCliqueDentroRetangulo(compSexoPilotoFUser.area)){
					pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 10), compSexoPiloto.area.y, 30, 30, COR_PRINCIPAL, painelDestino);
					pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 50), compSexoPiloto.area.y, 30, 30, COR_SELECIONADO, painelDestino);
					//pintarTextoPainel("M", painelDestino, (compSexoPilotoMUser.area.x+10), (compSexoPilotoMUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janela);
					//pintarTextoPainel("F", painelDestino, (compSexoPilotoFUser.area.x+10), (compSexoPilotoFUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janela);
					sexoPiloto = 'F';
        }else if(verificarCliqueDentroRetangulo(compPaisNatalPilotoUser.area)){
					compAtualizar = pintarRetanguloPainel((compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 10), compPaisNatalPiloto.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					campoAtivo = 3;
					compClicado = CLICADO_PAIS_PILOTO;
					checarEventoMenuEscolhePais();
        }
			}else if( event.type == SDL_KEYDOWN ){
			  	if( event.key.keysym.sym == SDLK_BACKSPACE){
	          	if(campoAtivo == 1){
	          		if(strlen(nomePiloto) > 0)
									compNomePilotoDigitado = retirarUltimaLetraTextoPainel(nomePiloto, compNomePilotoDigitado);
							} else if(campoAtivo == 2){
	          		if(strlen(idadePilotoString) > 0)
									compIdadePilotoDigitado = retirarUltimaLetraTextoPainel(idadePilotoString, compIdadePilotoDigitado);
							} else if(campoAtivo == 3){
								
							}	
		      		//renderText = 1;
		      		//atualizaPainel = 1;
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
						if(strlen(nomePiloto)+1 <= 32 && strlen(nomePiloto)+1 > 0)
							strcat(nomePiloto, event.text.text);
							char strTextoTela[1];
							sprintf(strTextoTela, "%c", nomePiloto[strlen(nomePiloto) - 1]);
							//compNomePilotoDigitado = pintarTextoPainel(strTextoTela, painelDestino, compNomePiloto.area.x + compNomePiloto.area.w + 15 + compNomePilotoDigitado.area.w, compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janela);
					} else if(campoAtivo == 2 && atoi(event.text.text) != 0){
						if(strlen(idadePilotoString)+1 <= 3 && strlen(idadePilotoString)+1 > 0)
							strcat(idadePilotoString, event.text.text);
					} else if(campoAtivo == 3){
						
					}
		      pintarTexto = 1;
		      //atualizaPainel = 1;
		    }
		  }
			if(pintarTexto){
      	if(strlen(nomePiloto) <= 32 && strlen(nomePiloto) > 0)
					compNomePilotoDigitado = pintarTextoPainel(nomePiloto, painelDestino, (compNomePiloto.area.x + compNomePiloto.area.w + 15), compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janela);
				if(strlen(idadePilotoString) <= 3 && strlen(idadePilotoString) > 0)
					compIdadePilotoDigitado = pintarTextoPainel(idadePilotoString, painelDestino, (compIdadePiloto.area.x + compIdadePiloto.area.w + 15), compIdadePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janela);
				
	      pintarTexto = 0;
	    }
			/*if(atualizaPainel){
				atualizaPainel = 0;*/
			//}
			atualizarPainel(painelDestino);
			SDL_FlushEvent(event.type);
		}
	}
  SDL_StopTextInput();
	
	return compClicado;
}



// Objetivo:
int checarEventoMenuEscolhePais(){
	int ret = 0, sair = 0, atualizaPainel = 0, campoAtivo = 0, renderText, paisAtual = 0;
	ComponenteClicado compClicado;
	Cor corFundo = COR_FUNDO, corPrincipal = COR_PRINCIPAL;
	FILE *arquivoPaises;
	Componente compTitulo;
	
	char linha[127];
	
	arquivoPaises = fopen("Dados/Paises.guyg", "r");
	if(arquivoPaises == NULL){
		salvarErro("Erro ao abrir o arquivo dos paises 'fopen' de 'checarEventoMenuEscolhePais'\n");
	}
	
	Janela janelaPaises = criarJanela("Lista de Paises", 300, 560);
	Painel painelPaises = criarPainel(janelaPaises);
	
	compTitulo = pintarTextoPainel("Paises", painelPaises, 90, 10, FONTE_TITULO_PRINCIPAL, janelaPaises);
	
	while(!feof(arquivoPaises)){
		memset(linha, '\0', sizeof(linha));
		fgets(linha, 127, arquivoPaises);
		strcpy(linha, rRemoveQuebraLinha(linha));
		pintarTextoPainel(linha, painelPaises, 10, 60+paisAtual*20, FONTE_TEXTO_PRINCIPAL, janelaPaises);
		paisAtual++;
	}
	
	atualizarPainel(painelPaises);
	
	SDL_Event event;
	while(!sair){
		renderText = 0;
		while(SDL_WaitEvent(&event)){
			if(event.type == SDL_QUIT){
				compClicado = CLICADO_FECHAR;
				sair = 1;
				break;
			}
			atualizarPainel(painelPaises);
			SDL_FlushEvent(event.type);
		}
	}
	SDL_DestroyWindow(janelaPaises);
	return compClicado;
}



// Objetivo:
int verificarCliqueDentroRetangulo(Retangulo rect){
  SDL_Point posMouse;
  SDL_GetMouseState(&posMouse.x, &posMouse.y);
	if((posMouse.x <= (rect.w+rect.x) && posMouse.x >= rect.x) && 
			(posMouse.y <= (rect.h+rect.y) && posMouse.y >= rect.y)) return 1;
	return 0;
}



// Objetivo: 
int atualizarBordaComponente(Componente *compAtualizar){
	pintarRetanguloPainel(compAtualizar->area.x, compAtualizar->area.y, 300, 30, COR_PRINCIPAL, compAtualizar->painelPertencente);
	compAtualizar->painelPertencente = NULL;
}


#endif /* _FUNCOES_JANELA_C_ */
