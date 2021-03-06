#ifndef _FUNCOES_JANELA_C_
#define _FUNCOES_JANELA_C_

#include <Cabecalhos/tiposDadosJanela.h>
//#include <Cabecalhos/funcoesMenu.h>
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
		salvarErro("Erro na funcao 'SDL_CreateWindow' de 'criarJanela': \n");
  
	return jan;					
}


// Objetivo: Criar um painel
// Parametro: A janela onde ficara o painel
// Retorno: O painel criado ou NULL se ocorrer um erro
Painel criarPainel(Janela janela){
	Painel painel = NULL;
  painel = SDL_CreateRenderer(janela, // A janela onde ficara o painel
														-1, // O index do driver de renderizacao ou -1 para
																//	o primeiro driver
														SDL_RENDERER_SOFTWARE); // O tipo de rederizacao
	
	//Verifica se ocorreu um erro ao criar o painel
	if(painel == NULL)
		salvarErro("Erro na funcao 'SDL_CreateRenderer' de 'criarPainel'\n");
	
	// Pinta o fundo do painel com a cor branca e verifica se ocorreu um erro ao 
	//	pintar o fundo
	if(alteraCorFundoPainel(painel, COR_FUNDO) != 0){
  	salvarErro("Erro na funcao 'alteraCorFundoPainel' de 'criarPainel'\n");
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
  if(SDL_SetRenderDrawColor(painelAlterarCor, // Painel que sera definido a cor
														novaCor.r, // Quantidade de vermelho
														novaCor.g, // Quantidade de verde
														novaCor.b, // Quantidade de azul
														novaCor.opacidade) != 0){ // Opacidade da cor
  	salvarErro("Erro na funcao 'SDL_SetRenderDrawColor' de 'alteraCorFundoPainel'\n");
		return 1;
	}
	
  // Pinta o fundo do painel com a nova cor e verifica se ocorreu um erro ao 
  // pinta-lo com essa cor
  if(SDL_RenderClear(painelAlterarCor) != 0){
  	salvarErro("Erro na funcao 'SDL_RenderClear' de 'alteraCorFundoPainel'\n");
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
		salvarErro("Erro na funcao 'TTF_OpenFont' de 'abrirFonte'\n");
	
	return fonte;
}



// Objetivo: Transformar um texto em uma superficie
// Parametros: O endereco da string que contem o texto e a fonte do texto
// Retorno: A superficie do texto ou NULL se ocorrer um erro
Superficie textoParaSuperficie(char *texto, Fonte fonteTexto){
	Superficie superficeTexto = NULL;
	
	// Transforma o texto em uma superficie
	superficeTexto = TTF_RenderText_Solid(fonteTexto, // A fonte do texto
	                                       texto, // O texto que sera tranformado
	                                       COR_FONTE_PRINCIPAL); // A cor do texto
	
	// Verifica se ocorreu um erro ao transformar o text em superficie
	if(superficeTexto == NULL) 
		salvarErro("Erro na funcao 'TTF_RenderText_Solid' de 'textoParaSuperficie'\n");
	
	// Limpa a memoria utilizada pela fonte
	TTF_CloseFont(fonteTexto);
	
	return superficeTexto;
}



// Objetivo: Transformar uma superficie em textura
// Parametros: O painel onde ficara a superficie e a superficie que sera transformada
// Retorno: A textura criada ou NULL se ocorrer um erro
Textura superficieParaTextura(Painel painelDestino, Superficie superficieTransformar){
	Textura novaTextura = NULL;
	
	// Cria uma textura apartir da superficie
	novaTextura = SDL_CreateTextureFromSurface(painelDestino, // O painel que ficara a textura
																							superficieTransformar); // A superficie que 
																							                        //  sera transformada
	
	// Verifica se ocorreu um erro ao criar a textura
	if(novaTextura == NULL) 
		salvarErro("Erro na funcao 'SDL_CreateTextureFromSurface' de 'superficieParaTextura'\n");
	
	return novaTextura;
}



// Objetivo: Limpar a memoria usada pela superficie
// Parametro: A superficie a ser limpa
void limparMemSuperficie(Superficie superficieLimpar){
	SDL_FreeSurface(superficieLimpar);
}



// Objetivo: Copiar uma parte ou toda a textura para um painel
// Parametros: O painel onde ficara a textura, a textura que sera copiada para o painel 
//							e o retangulo com o tamanho que sera usado pela textura no painel
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
		salvarErro("Erro na funcao 'SDL_RenderCopyEx' de 'copiarTexturaPainel'\n");
	
	return res;
}



// Objetivo: Atualizar um painel
// Parametro: O painel a ser atualizado
void atualizarPainel(Painel painelAtualizar){
	SDL_RenderPresent(painelAtualizar);
}



// Objetivo: Pintar no painel um texto
// Parametros: O endereco da string que contem o texto que ser� pintado, a posicao X e 
//              Y de onde ficara o texto, a fonte do texto e a janela onde ficara o texto
// Retorno: A estrutura Componente contendo dados do texto no painel e se ocorreu um erro
//           o atributo 'painelPertencente' da estrutura estara setado como NULL
Retangulo pintarTextoPainel(char *textoPintar, int posX, int posY, Fonte fonteTexto, 
															Janela janelaDestino){
	Retangulo retanguloTexto = {0,0,0,0};
	// Inicializa o 'painelPertencente' como NULL para ser uma flag de erro
	
	if(strlen(textoPintar) > 0){
		Superficie super;
		int copiadaSucesso = 0;
		// Transforma o texto em superficie
		super = textoParaSuperficie(textoPintar, fonteTexto);
		
		// Verifica se ocorreu um erro ao criar a superficie
		if(super == NULL){
			salvarErro("Erro na funcao 'textoParaSuperficie' de 'pintarTextoPainel'\n");
      return retanguloTexto;
    }
		
		// Define as coordenadas da area ocupada pelo texto dentro do painel
		retanguloTexto.x = posX;
		retanguloTexto.y = posY;
		retanguloTexto.h = super->h;
		retanguloTexto.w = super->w;
		
		// Pega a superficie da janela de destino
		Superficie sJanela = SDL_GetWindowSurface(janelaDestino);
		// Copia uma superficie para outra
		SDL_BlitSurface(super, // A superficie que sera copiada
		                 NULL, // O retangulo que sera copiado da superficie ou NULL para 
		                       //  toda superficie
		                 sJanela, // A superficie de destino
		                 &retanguloTexto); // O retangulo onde sera copiada a 
		                                         //  primeira superficie
		// Atualiza a superficie da janela
		SDL_UpdateWindowSurface(janelaDestino);
		// Limpa a memoria utilizada pelas superficies
		limparMemSuperficie(sJanela);
		limparMemSuperficie(super);
		// Garante que nao restara nada na memoria sobre as superficies
		sJanela = 0;
		super = 0;
	}
	/*
	// Cria um painel auxiliar e seta ele com o painel da janela
	Painel painelJanela = SDL_GetRenderer(janelaDestino);
	
	// Verifica se ocorreu erro ao receber o painel auxiliar
	if(painelJanela == NULL){
	  salvarErro("Erro na funcao 'SDL_GetRenderer' de 'pintarTextoPainel'\n");
    return componenteTexto;
	}
	*/
	// Define o painel do componente do texto com o painel auxiliar
	//componenteTexto.painelPertencente == painelJanela;
	
	// Limpar a memoria utilizada pelo painel auxiliar
	//limparMemPainel(painelJanela);
	
	return retanguloTexto;
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
		salvarErro("Erro na funcao 'SDL_CreateRGBSurface' de 'criarSuperficie'\n");
	
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
														//  NULL para toda a superficie
											SDL_MapRGB( // Pega o valor inteiro da cor a ser pintada no mesmo 
																	//  formato de bits da superficie
																	superficiePintar->format, // Pega o formato de bits da 
																														//  superficie
																	corPintar.r, // Cor vermelha
																	corPintar.g, // Cor verde
																	corPintar.b)); // Cor azul
	
	// Verifica se ocorreu erro ao pintar a superficie
	if(ret != 0)
		salvarErro("Erro na funcao 'SDL_FillRect' de 'pintarSuperficie'\n");
	
	return ret;
}



// Objetivo: Pintar um retangulo no painel
// Parametros: As coordenadas X e Y onde o retangulo sera pintado no painel, a largura e 
//							altura do retangulo, a cor do retangulo a ser pintado e o painel onde o 
//							retangulo sera pintado
// Retorno: A estrutura Componente contendo os dados do retangulo no painele se ocorreu 
//           um erro o atributo 'painelPertencente' da estrutura estara setado como NULL
Componente pintarRetanguloPainel(int posX, int posY, int largura, int altura, Cor cor, 
																	Painel painelDestino){
	Componente comp;
	comp.ocorreuErro = 1;
	comp.painelPertencente = painelDestino;
	
	// Define a area do retangulo
	comp.area.x = posX;
	comp.area.y = posY;
	comp.area.w = largura;
	comp.area.h = altura;
	
	// Define a cor do retangulo e verifica se ocorreu um erro ao definir essa cor
  if(SDL_SetRenderDrawColor(painelDestino, // Painel que sera pintado o retangulo
														cor.r, // Quantidade de vermelho
														cor.g, // Quantidade de verde
														cor.b, // Quantidade de azul
														cor.opacidade) != 0) // Opacidade da cor
  	salvarErro("Erro na funcao 'SDL_SetRenderDrawColor' de 'pintarRetanguloPainel'\n");
	else{
		// Desenha o retangulo e verifica se ocorreu um erro ao desenha-lo
		if(SDL_RenderDrawRect(painelDestino, // O painel onde sera pintado o retangulo
		                       &comp.area) != 0) // O retangulo que sera pintado
		  salvarErro("Erro na funcao 'SDL_RenderDrawRect' de 'pintarRetanguloPainel'\n");
		else{
			comp.ocorreuErro = 0;
		}
	}
	
	return comp;
}



// Objetivo: Pintar em um painel uma tabela
// Parametros: As coordenadas X e Y onde a tabela sera pintada no painel, a largura e 
//							altura da tabela, a cor da borda, a quantidade de colunas da tabela, a 
//							quantidade de linhas da tabela e o painel onde a tabela sera pintada
// Retorno: A estrutura Componente contendo os dados do retangulo no painel ou se ocorrer 
//					 um erro o atributo 'painelPertencente' da estrutura estara setado como NULL
Componente pintarTabelaPainel(int posX, int posY, int largura, int altura, Cor corBorda, 
                               int qtdColunas, int qtdLinhas, Painel painelDestino){
	Componente comp, compAux;
	int linhaAtual, colunaAtual, larguraCelula, alturaCelula, celulaW, celulaH;
	
	// Inicializa o 'painelPertencente' como NULL para ser uma flag de erro
	comp.painelPertencente = NULL;
	// Pinta um retangulo para ser a borda de fora da tabela
	/*comp = pintarRetanguloPainel(posX, posY, largura, altura, corBorda, painelDestino);
	
	// Verifica se ocorreu um erro ao pintar o retangulo da borda de fora da tabela
	if(comp.painelPertencente == NULL){
		salvarErro("Erro na funcao 1 'pintarRetanguloPainel' de 'pintarRetanguloCBordasPainel'\n");
		return comp;
	}*/
	
	// Cria um retangulo contendo as coordenadas da tabela sem a borda de fora
	Retangulo areaTabelaSBorda = {posX + 1, posY + 1, 
																 largura - 2, altura - 2};
  /*
	comp.area.x = posX + larguraBorda;
	comp.area.y = posY + larguraBorda;
	comp.area.w = largura - (larguraBorda*2);
	comp.area.h = altura - (larguraBorda*2);
	*/
	
	// Calcula a largura e a altura de cada celula da tabela
	larguraCelula = largura / qtdColunas;
	alturaCelula = altura / qtdLinhas;
	
	// Ira pintar cada retangulo da tabela
	for(linhaAtual = 1; linhaAtual <= qtdLinhas; linhaAtual++){ // FOR das linhas
		for(colunaAtual = 1; colunaAtual <= qtdColunas; colunaAtual++){ // FOR das colunas
		  /*  PROBLEMA CALCULA DUAS VEZES A LARGURA E A ALTURA DAS CELULAS  */
			if(linhaAtual == qtdLinhas && (posY + (alturaCelula * linhaAtual) - 
					(posY + altura)) < 0){
				celulaH = (altura / qtdLinhas) + 
									 (-1 * (posY + (alturaCelula * linhaAtual) - 
									 (posY + altura)));
			}else{
				celulaH = altura / qtdLinhas;
			}
			if(colunaAtual == qtdColunas && (posX + (larguraCelula * colunaAtual) - 
					(posX + largura)) < 0){
				celulaW = (largura / qtdColunas) + 
									 (-1 * (posX + (larguraCelula * colunaAtual) - 
									 (posX + largura)));
			}else{
				celulaW = largura / qtdColunas;
			}
			
			// Pinta uma celula da tabela
			compAux = pintarRetanguloPainel((posX + (larguraCelula * 
																			 (colunaAtual -1))-1),
																			 (posY + (alturaCelula * 
																			 (linhaAtual -1))-1),
																			 celulaW+1,
																			 celulaH+1, 
																			 corBorda,
																			 painelDestino);
			// Verifica se ocorreu um erro ao pintar a ultima celula da tabela
			if(compAux.painelPertencente == NULL){
				char strErr[127];
				sprintf(strErr, "Erro na funcao %d %d 'pintarTabelaPainel' de 'pintarRetanguloCBordasPainel'\n", linhaAtual, colunaAtual);
				salvarErro(strErr);
				return compAux;
			}
		}
		if(linhaAtual < qtdLinhas) comp.areaAux = compAux.area;
	}
	
	comp.painelPertencente = painelDestino;
	
	comp.area.x = posX;
	comp.area.y = posY;
	comp.area.w = largura;
	comp.area.h = altura;
	
	return comp;	
}



// Objetivo: 
Componente pintarDadoTabela(Componente tabelaDestino, int linhaTabela, int colunaTabela, 
														 char *dado, Janela janelaDestino){
	int larguraCelula, alturaCelula, posXDado, posYDado, larguraDado, alturaDado;
	Superficie superficieDado;
	Cor corTexto = COR_PRINCIPAL;
	char dadoAlterado[13];
	
	memset(dadoAlterado, '\0', sizeof(dadoAlterado));
	strncpy(dadoAlterado, dado, 7);
	if(strlen(dado) > 7) strcat(dadoAlterado, "...");
	
	superficieDado = textoParaSuperficie(dadoAlterado, FONTE_TEXTO_PRINCIPAL);
	larguraDado = superficieDado->w;
	alturaDado = superficieDado->h;
	limparMemSuperficie(superficieDado);	
	larguraCelula = tabelaDestino.areaAux.w;
	alturaCelula = tabelaDestino.areaAux.h;
	posXDado = tabelaDestino.area.x + (larguraCelula * (colunaTabela - 1)) + 
							((larguraCelula - larguraDado) / 2);
	posYDado = tabelaDestino.area.y + (alturaCelula * (linhaTabela - 1)) + 
							((alturaCelula - alturaDado) / 2);
	pintarTextoPainel(dadoAlterado, posXDado, posYDado, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
}



// Objetivo: Apagar a ultima letra de uma string
// Parametros: O endereco da string que contem o texto que ser� retirada a ultima 
//              letra, a estrutura Componente que contem informacoes sobre o texto
//              no painel
// Retorno: A estrutura Componente contendo informacoes sobre o texto no painel ou 
//           se ocorrer um erro o atributo 'painelPertencente' da estrutura estara 
//           setado como NULL
Componente retirarUltimaLetraTextoPainel(char *texto, Componente componenteTexto){
	Cor corFundo = COR_SELECIONADO;
	
	// Define o 'painelPertencente' como NULL para ser uma flag de erro
	/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	//             ALTERAR A ESTRUTURA COMPONENTE PARA TER UMA FLAG DE ERRO
	/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

	// Retira o ultimo caracter da string
	rTirarCaracter(texto);
	
	// Inicializa um retangulo com as coordenadas do texto
	Retangulo rectAux = {componenteTexto.area.x,componenteTexto.area.y,
												componenteTexto.area.w,componenteTexto.area.h};
	// Verifica se e necessario apagar uma letra da tela
	if(strlen(texto) < 33 && strlen(texto) > 0){
	  // Se for necessario, cria a superficie do novo texto (texto sem o ultimo 
	  //  caracter)
		Superficie superAux = textoParaSuperficie(texto, FONTE_TEXTO_PRINCIPAL);
		
		// Define as novas coordenadas do texto
		rectAux.x = componenteTexto.area.x + superAux->w;
		rectAux.y = componenteTexto.area.y;
		rectAux.w = componenteTexto.area.w - superAux->w;
		rectAux.h = superAux->h;
		
		// Limpa o espaco na memoria utilizado pela superficie
		limparMemSuperficie(superAux);
	}
		
	// Define a cor do retangulo que apagara a ultima letra e verifica se ocorreu um 
	//  erro ao definir essa cor
  if(SDL_SetRenderDrawColor(componenteTexto.painelPertencente, // Painel que sera
                                                               //  pintado o 
                                                               //  retangulo
														corFundo.r, // Quantidade de vermelho
														corFundo.g, // Quantidade de verde
														corFundo.b, // Quantidade de azul
														corFundo.opacidade) != 0){ // Opacidade da cor
  	salvarErro("Erro na funcao 'SDL_SetRenderDrawColor' de 'retirarUltimaLetraTextoPainel': \n");
		return componenteTexto;
	}
	
	// Prenche o retangulo no painel e verifica se ocorreu erro ao preenche-lo
	if(SDL_RenderFillRect(componenteTexto.painelPertencente, // O painel onde o 
	                                                         //  retangulo sera 
	                                                         //  preenchido
	                    &rectAux) != 0){ // As coordenadas do retangulo
  	salvarErro("Erro na funcao 'SDL_RenderFillRect' de 'retirarUltimaLetraTextoPainel'\n");
		return componenteTexto;
	}
	
	// Atualiza o painel
	atualizarPainel(componenteTexto.painelPertencente);
	
	return componenteTexto;
}



// Objetivo: Apagar a ultima letra de uma string
// Parametros: O endereco da string que contem o texto que ser� retirada a ultima 
//              letra, a estrutura Componente que contem informacoes sobre o texto
//              no painel
// Retorno: A estrutura Componente contendo informacoes sobre o texto no painel ou 
//           se ocorrer um erro o atributo 'painelPertencente' da estrutura estara 
//           setado como NULL
Componente retirarUltimaLetraTextoPainel2(char *texto, Componente *componenteTexto){
	Cor corFundo = COR_FUNDO;
	
	// Define o 'painelPertencente' como NULL para ser uma flag de erro
	/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	//             ALTERAR A ESTRUTURA COMPONENTE PARA TER UMA FLAG DE ERRO
	/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

	// Retira o ultimo caracter da string
	rTirarCaracter(texto);
	
	// Inicializa um retangulo com as coordenadas do texto
	Retangulo rectAux = {componenteTexto->areaAux.x,componenteTexto->areaAux.y,
												componenteTexto->areaAux.w,componenteTexto->areaAux.h};
	// Verifica se e necessario apagar uma letra da tela
	if(strlen(texto) < 33 && strlen(texto) > 0){
	  // Se for necessario, cria a superficie do novo texto (texto sem o ultimo 
	  //  caracter)
		Superficie superAux = textoParaSuperficie(texto, FONTE_TEXTO_PRINCIPAL);
		
		// Define as novas coordenadas do texto
		rectAux.x = componenteTexto->areaAux.x + superAux->w;
		rectAux.y = componenteTexto->areaAux.y;
		rectAux.w = componenteTexto->areaAux.w - superAux->w;
		rectAux.h = superAux->h;
		
		// Limpa o espaco na memoria utilizado pela superficie
		limparMemSuperficie(superAux);
	}
		
	// Define a cor do retangulo que apagara a ultima letra e verifica se ocorreu um 
	//  erro ao definir essa cor
  if(SDL_SetRenderDrawColor(componenteTexto->painelPertencente, // Painel que sera
                                                               //  pintado o 
                                                               //  retangulo
														corFundo.r, // Quantidade de vermelho
														corFundo.g, // Quantidade de verde
														corFundo.b, // Quantidade de azul
														corFundo.opacidade) != 0){ // Opacidade da cor
  	salvarErro("Erro na funcao 'SDL_SetRenderDrawColor' de 'retirarUltimaLetraTextoPainel': \n");
		return *componenteTexto;
	}
	
	// Prenche o retangulo no painel e verifica se ocorreu erro ao preenche-lo
	if(SDL_RenderFillRect(componenteTexto->painelPertencente, // O painel onde o 
	                                                         //  retangulo sera 
	                                                         //  preenchido
	                    &rectAux) != 0){ // As coordenadas do retangulo
  	salvarErro("Erro na funcao 'SDL_RenderFillRect' de 'retirarUltimaLetraTextoPainel'\n");
		return *componenteTexto;
	}
	
	// Atualiza o painel
	atualizarPainel(componenteTexto->painelPertencente);
	
	return *componenteTexto;
}



// Objetivo: Limpar todo o painel, pintando-o com a cor de fundo novamente
// Parametro: O painel que sera limpo
// Retorno: 0 - Se a funcao executar com sucesso
//					1 - Se ocorrer um erro
int limparPainel(Painel painelLimpar){
	
  // Pinta todo painel com a cor de fundo padrao
  if(alteraCorFundoPainel(painelLimpar, COR_FUNDO) != 0){
  	salvarErro("Erro na funcao 'alteraCorFundoPainel' de 'limparPainel'\n");
		return 1;
	}
	atualizarPainel(painelLimpar);
	return 0;
}



// Objetivo: Verificar se quando ocorreu um clique o mouse estava dentro de um 
//            retangulo
// Parametro: O retangulo que sera verificado se o mouse estava dentro
// Retorno: 0 - Se o mouse esta fora do retangulo
//					1 - Se o mouse esta dentro do retangulo
int verificarCliqueDentroRetangulo(Retangulo retanguloInterseccao){
  // Cria uma estrutura 'SDL_Point' que contem as coordenadas de um ponto, no
  //  caso as coordenadas do mouse
  SDL_Point posMouse;
  
  // Pega a posicao do mouse
  SDL_GetMouseState(&posMouse.x, &posMouse.y);
  
  // Verifica se as coordenas do mouse estao dentro do retangulo ou nao
	if((posMouse.x <= (retanguloInterseccao.w+retanguloInterseccao.x) && 
	    posMouse.x >= retanguloInterseccao.x) && 
			(posMouse.y <= (retanguloInterseccao.h+retanguloInterseccao.y) && 
			posMouse.y >= retanguloInterseccao.y)) return 1;
	return 0;
}



// Objetivo: Atulizar a cor da borda de um Componente
// Parametro: A estrutura Componente que contem informacoes sobre o
//             componente a ser atualizado no painel
// Retorno: 0 - Se a funcao executar com sucesso
//					1 - Se ocorrer um erro
int atualizarBordaComponente(Componente *compAtualizar){
  Componente componenteAuxAtualizar;
	
	// Redesenha um retangulo com a cor principal
	componenteAuxAtualizar = pintarRetanguloPainel(compAtualizar->area.x, compAtualizar->area.y, compAtualizar->area.w, compAtualizar->area.h, COR_PRINCIPAL, compAtualizar->painelPertencente);
	
	if(componenteAuxAtualizar.painelPertencente == NULL){
  	salvarErro("Erro na funcao 'pintarRetanguloPainel' de 'atualizarBordaComponente'\n");
		return 1;
	}
	
	compAtualizar->painelPertencente = NULL;
	
	return 0;
}


/*
// Objetivo: Limpar a memoria utilizada pelo painel
// Parametro: O painel a ser limpado
void limparMemPainel(Painel painelLimpar){
	SDL_DestroyRenderer(painelLimpar);
}
*/



// Objetivo: 
int manipularCampoTexto(SDL_Event *e, Componente *c, char *txt, Janela j, int min, int max, int tipo){
	int pintarTexto = 0, atualizarComp = 0;
	if(e->type == SDL_MOUSEBUTTONUP){
		if(verificarCliqueDentroRetangulo(c->area)){
			pintarRetanguloPainel(c->area.x, c->area.y, c->area.w, c->area.h, COR_SELECIONADO, c->painelPertencente);
			if(strlen(txt) <= max && strlen(txt) > min)
				c->areaAux = pintarTextoPainel(txt, c->area.x + 15, c->area.y+5, FONTE_TEXTO_PRINCIPAL, j);
			c->ativo = 1;
			atualizarComp = 1;
		}else{
			c->ativo = 0;
		}
		pintarTexto = 1;
	}else if( e->type == SDL_KEYDOWN ){
  	if( e->key.keysym.sym == SDLK_BACKSPACE){
      	if(c->ativo == 1){
      		if(strlen(txt) > 0){
						retirarUltimaLetraTextoPainel2(txt, c);
					}
				}
		}
	} else if( e->type == SDL_TEXTINPUT ){
    if( !( ( e->text.text[ 0 ] == 'c' || e->text.text[ 0 ] == 'C' ) && ( e->text.text[ 0 ] == 'v' || e->text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) ){
      if(c->ativo == 1 && strlen(txt) < max){
				if(strlen(txt) < max && (tipo <= 1 && tipo >= 3) ? strENumero(e->text.text) != 0 : 1){
					strcat(txt, e->text.text);
					memset(e->text.text, '\0', strlen(e->text.text) * sizeof(e->text.text));
					if(tipo == 2 && (strlen(txt) == 2 || strlen(txt) == 5))
						strcat(txt, "/");
					if(tipo == 3 && (strlen(txt) == 2))
						strcat(txt, ":");
					if(tipo == 3 && (strlen(txt) == 5))
						strcat(txt, "'");
				}
			}
		}
		pintarTexto = 1;
	}
	if(pintarTexto){
  	if(strlen(txt) <= max && strlen(txt) > min)
			c->areaAux = pintarTextoPainel(txt, c->area.x + 15, c->area.y+5, FONTE_TEXTO_PRINCIPAL, j);
		pintarTexto = 0;
	}
	return atualizarComp;
}



// Objetivo: Inicializar componente com os valores zerados
// Parametros: O endereco da estrutura Componente que ser� inicializada e o painel de destino
void inicializarComponente(Componente *componenteInicializar, Painel painelDestino){
	componenteInicializar->area.x = 0;
	componenteInicializar->area.y = 0;
	componenteInicializar->area.w = 0;
	componenteInicializar->area.h = 0;
	componenteInicializar->areaAux.x = 0;
	componenteInicializar->areaAux.y = 0;
	componenteInicializar->areaAux.w = 0;
	componenteInicializar->areaAux.h = 0;
	componenteInicializar->painelPertencente = painelDestino;
	componenteInicializar->ativo = 0;
	componenteInicializar->ocorreuErro = 0;
}

#endif /* _FUNCOES_JANELA_C_ */
