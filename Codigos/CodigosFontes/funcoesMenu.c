#ifndef _FUNCOES_MENU_C_
#define _FUNCOES_MENU_C_

#include <Cabecalhos/tiposDadosJanela.h>
#include <Cabecalhos/funcoesJanela.h>
#include <Cabecalhos/funcoesPiloto.h>
#include <stdio.h>



// Objetivo: Pinta todo o menu principal e espera o usuario escolher uma opcao
// Parametros: A janela e o painel onde sera pintado o Menu Principal
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuPrincipal(Janela janelaDestino, Painel painelDestino){
//int pintarMenuPrincipalEEsperaEscolherOpcao(Janela janela, Painel painelDestino){
	int sair = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compPilotos, compCircuitos, compSair;
	
	// Limpa todo o painel
	limparPainel(painelDestino);
	
	// Pintar o titulo
	compTitulo.area = pintarTextoPainel("MENU PRINCIPAL", 180, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta as opcoes do menu
	compPilotos.area = pintarTextoPainel("Pilotos", 10, 40, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compCircuitos.area = pintarTextoPainel("Circuitos", 10, 80, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compSair.area = pintarTextoPainel("SAIR", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Atualizar o painel, para aparecer tudo que foi pintado 
	atualizarPainel(painelDestino);
	
	// Cria a estrutura 'SDL_Event' para guardar todos evento que ocorrem
	SDL_Event evento;
	
	// Loop para nao fechar a janela
	while(!sair){
	
	  // Verifica se e preciso pintar todo o menu
	  /*
	  ----------------------------	  ----------------------------	  ----------------------------	  ----------------------------	  ----------------------------	  ----------------------------
	  */
	  // Verifica se ocorreu um evento
		while(SDL_WaitEvent(&evento)){
		
		  // Verifica se o evento que ocorreu e o de fechar a janela
      if(evento.type == SDL_QUIT){
    		
    		// Define o componente que foi clicado
        compClicado = CLICADO_FECHAR;
    		
    		// Define que e para cancelar o loop da janela
        sair = 1;
    			
    		// Sair do loop de verificar um evento
        break;
        
      // Verifica se o evento que ocorreu e o de um clique do mouse
			} else if(evento.type == SDL_MOUSEBUTTONUP){
			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'sair'
    		if(verificarCliqueDentroRetangulo(compSair.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_SAIR;
    			
    			// Define que e para cancelar o loop da janela
    			sair = 1;
    			
    			// Sair do loop de verificar um evento
    			break;
    			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'Pilotos'
				} else if(verificarCliqueDentroRetangulo(compPilotos.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_PILOTOS;
    			
    			// Define que e para cancelar o loop da janela
    			sair = 1;
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compCircuitos.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_CIRCUITOS;
    			
    			// Define que e para cancelar o loop da janela
    			sair = 1;
    			
    			// Sair do loop de verificar um evento
    			break;
				}
			}
			
			// Limpa a memoria utilizada pelo evento atual
			SDL_FlushEvent(evento.type);
		}
	}
	
	return compClicado;
}



// Objetivo: Pinta todo o menu 'Pilotos' e espera o usuario escolher uma opcao
// Parametros: A janela e o painel onde sera pintado o Menu 'Pilotos'
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuPilotos(Janela janelaDestino, Painel painelDestino){
//int pintarMenuPilotosEEsperaEscolherOpcao(Janela janela, Painel painelDestino){
	int sair = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	Componente compTitulo, compNovoPiloto, compTabelaTodosPilotos, compVoltar;
	Retangulo areaDadosListaPilotos;
	
	// Cria a estrutura 'SDL_Event' para guardar todos evento que ocorrem
	SDL_Event evento;
	
	// Loop para nao sair do menu atual
	while(!sair){
	
	  // Verifica se e preciso pintar todo o menu
		if(pintaMenu){
			pintaMenu = 0;
		
		  // Limpa tudo o que estava pintado no painel
			limparPainel(painelDestino);
			
			// Pinta o titulo
			compTitulo.area = pintarTextoPainel("PILOTOS", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			
    	// Pinta as opcoes do menu		
			compNovoPiloto.area = pintarTextoPainel("Novo Piloto", 10, 40, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Pinta tabela que ficara todos os pilotos
			compTabelaTodosPilotos = pintarTabelaPainel(10, 80, 540, 350, COR_TABELA, 5, 10, painelDestino);
			areaDadosListaPilotos.x = compTabelaTodosPilotos.area.x;
			areaDadosListaPilotos.y = compTabelaTodosPilotos.area.y + (compTabelaTodosPilotos.area.h/10);
			areaDadosListaPilotos.w = compTabelaTodosPilotos.area.w;
			areaDadosListaPilotos.h = compTabelaTodosPilotos.area.h - (compTabelaTodosPilotos.area.h/10);
			// Pinta o cabecalho da tabela
			pintarDadoTabela(compTabelaTodosPilotos, 1, 1, "ID", janelaDestino);
			pintarDadoTabela(compTabelaTodosPilotos, 1, 2, "NOME", janelaDestino);
			pintarDadoTabela(compTabelaTodosPilotos, 1, 3, "IDADE", janelaDestino);
			pintarDadoTabela(compTabelaTodosPilotos, 1, 4, "SEXO", janelaDestino);
			pintarDadoTabela(compTabelaTodosPilotos, 1, 5, "PAIS", janelaDestino);
			// Pinta todos os pilotos
			apresentarTodosPilotos(compTabelaTodosPilotos, janelaDestino);
			
    	// Atualizar o painel, para aparecer tudo que foi pintado 
			atualizarPainel(painelDestino);
		}
		
	  // Verifica se ocorreu um evento
		while(SDL_WaitEvent(&evento)){
		
		  // Verifica se o evento que ocorreu e o de fechar a janela
      if(evento.type == SDL_QUIT){
    		
    		// Define o componente que foi clicado
	      compClicado = CLICADO_FECHAR;
    		
    		// Define que e para cancelar o loop do menu atual
	      sair = 1;
    			
    	  // Sair do loop de verificar um evento
        break;
        
      // Verifica se o evento que ocorreu e o de um clique do mouse
			}else if(evento.type == SDL_MOUSEBUTTONUP){
			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'voltar'
    		if(verificarCliqueDentroRetangulo(compVoltar.area)){
    		
    		  // Define o componente que foi clicado
	  			compClicado = CLICADO_VOLTAR;
    		
    	  	// Define que e para cancelar o loop do menu atual
	  			sair = 1;
    			
    	    // Sair do loop de verificar um evento
	  			break;
			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'novo piloto'
				} else if(verificarCliqueDentroRetangulo(compNovoPiloto.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_NOVO_PILOTO;
    			
    			// Vai para o menu 'Novo pilotos' e verifica seu retorno
					switch(checarEventoMenuNovoPiloto(janelaDestino, painelDestino)){
					
					  // Caso ocorreu um evento de fechar a janela
		    		case CLICADO_FECHAR:
		    		  
    	  	    // Define que e para cancelar o loop do menu atual
		    			sair = 1;
    			
    	        // Sair do loop de verificar um evento
		    			break;
		    		
		    		// Caso ocorra qualquer outro evento
						default:
						
						  // Define que nao e para cancelar o loop do menu atual
							sair = 0;
					}
					
					// Define que e para repintar o menu 'Pilotos'
					pintaMenu = 1;
					
					// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(areaDadosListaPilotos)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_TABELA_PILOTOS;
    			/*---------------------------------------------------------------------------------------------------------------------------------------
    			
    										 VERIFICAR QUANDO ALTERAR A PAGINACAO
    			
    			---------------------------------------------------------------------------------------------------------------------------------------*/
				int mouseY, mouseX;
				SDL_GetMouseState(&mouseX, &mouseY);
				int pilotoEscolhido = (int)(((mouseY - areaDadosListaPilotos.y))/(areaDadosListaPilotos.h/9));
				checarEventoMenuDescricaoPiloto(pilotoEscolhido, janelaDestino, painelDestino);
    			/*
    			// Vai para o menu 'Novo pilotos' e verifica seu retorno
					switch(checarEventoMenuNovoPiloto(janela, painelDestino)){
					
					  // Caso ocorreu um evento de fechar a janela
		    		case CLICADO_FECHAR:
		    		  
    	  	    // Define que e para cancelar o loop do menu atual
		    			sair = 1;
    			
    	        // Sair do loop de verificar um evento
		    			break;
		    		
		    		// Caso ocorra qualquer outro evento
						default:
						
						  // Define que nao e para cancelar o loop do menu atual
							sair = 0;
					}*/
					
					// Define que e para repintar o menu 'Pilotos'
					pintaMenu = 1;
					
					// Sair do loop de verificar um evento
    			break;
				}
			}
			
			// Limpa a memoria utilizada pelo evento atual
			SDL_FlushEvent(evento.type);
  	}
	}
	
	return compClicado;
}



// Objetivo: Pinta todo o menu 'Pilotos' e espera o usuario escolher uma opcao
// Parametros: A janela e o painel onde sera pintado o Menu 'Pilotos'
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuNovoPiloto(Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, campoAtivo = 0, pintarTexto = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compNomePiloto, compVoltar, compIdadePiloto, compSexoPiloto, 
	compPaisNatalPiloto, compNomePilotoUser, compSairUser, compIdadePilotoUser, 
	compSexoPilotoMUser, compSexoPilotoFUser, compPaisNatalPilotoUser, compAtualizar,
	compNomePilotoDigitado, compIdadePilotoDigitado, compSexoPilotoMText, 
	compSexoPilotoFText, compPaisNatalPilotoDigitado, compCadastrar;
	char nomePiloto[127], sexoPiloto = 'M', idadePilotoString[4], paisNatal[127];
	Piloto pilotoCadastrar;
	//alocarPiloto(&pilotoCadastrar);
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	compNomePilotoDigitado.area.w = 0;
	compNomePilotoDigitado.area.h = 0;
	compPaisNatalPilotoDigitado.area.w = 0;
	compPaisNatalPilotoDigitado.area.h = 0;
	compIdadePilotoDigitado.area.w = 0;
	compIdadePilotoDigitado.area.h = 0;
	compNomePilotoDigitado.painelPertencente = painelDestino;
	compPaisNatalPilotoDigitado.painelPertencente = painelDestino;
	compIdadePilotoDigitado.painelPertencente = painelDestino;
	
	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(nomePiloto, '\0', sizeof(nomePiloto));
	memset(idadePilotoString, '\0', sizeof(idadePilotoString));
	memset(paisNatal, '\0', sizeof(paisNatal));
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("NOVO PILOTO", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	compNomePiloto.area = pintarTextoPainel("Nome do Piloto:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compIdadePiloto.area = pintarTextoPainel("Idade do Piloto:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compSexoPiloto.area = pintarTextoPainel("Sexo do Piloto:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compPaisNatalPiloto.area = pintarTextoPainel("Pais natal do Piloto:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compNomePilotoUser = pintarRetanguloPainel((compNomePiloto.area.x + compNomePiloto.area.w + 10), compNomePiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	compIdadePilotoUser = pintarRetanguloPainel((compIdadePiloto.area.x + compIdadePiloto.area.w + 10), compIdadePiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	compSexoPilotoMUser = pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 10), compSexoPiloto.area.y, 30, 30, COR_SELECIONADO, painelDestino);
	compSexoPilotoFUser = pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 50), compSexoPiloto.area.y, 30, 30, COR_PRINCIPAL, painelDestino);
	compPaisNatalPilotoUser = pintarRetanguloPainel((compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 10), compPaisNatalPiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	
	// Pinta as letras das opcoes de sexo
	pintarTextoPainel("M", (compSexoPilotoMUser.area.x+10), (compSexoPilotoMUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("F", (compSexoPilotoFUser.area.x+10), (compSexoPilotoFUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo e depois o texto da opcao de cadastrar
	compCadastrar = pintarRetanguloPainel((compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 110), 260, 93, 30, COR_PRINCIPAL, painelDestino);
	pintarTextoPainel("Cadastrar", (compCadastrar.area.x + 10), (compCadastrar.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Atualizar o painel, para aparecer tudo que foi pintado
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
						compNomePilotoDigitado.area = pintarTextoPainel(nomePiloto, (compNomePiloto.area.x + compNomePiloto.area.w + 15), compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					campoAtivo = 1;
				}else if(verificarCliqueDentroRetangulo(compIdadePilotoUser.area)){
					compAtualizar = pintarRetanguloPainel((compIdadePiloto.area.x + compIdadePiloto.area.w + 10), compIdadePiloto.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(idadePilotoString) <= 3 && strlen(idadePilotoString) > 0)
						compIdadePilotoDigitado.area = pintarTextoPainel(idadePilotoString, (compIdadePiloto.area.x + compIdadePiloto.area.w + 15), compIdadePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
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
					compClicado = CLICADO_PAIS_PILOTO;
					checarEventoMenuEscolhePais(paisNatal);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPaisNatalPilotoDigitado.area);
					compPaisNatalPilotoDigitado.area = pintarTextoPainel(paisNatal, (compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 15), compPaisNatalPiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
        }else if(verificarCliqueDentroRetangulo(compCadastrar.area)){
					/* CADASTRAR USUARIO */
					pilotoCadastrar.idade = atoi(idadePilotoString);
					strcpy(pilotoCadastrar.nome, nomePiloto);
					strcpy(pilotoCadastrar.paisOrigem, paisNatal);
					pilotoCadastrar.sexo = sexoPiloto;
					salvarPiloto(pilotoCadastrar);
					char msgSucss[127];
					sprintf(msgSucss, "%s cadastrado com sucesso!", pilotoCadastrar.nome);
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             "Piloto cadastrado",
                             msgSucss,
                             janelaDestino);
				sair = 1;
				break;
        }
			}else if( event.type == SDL_KEYDOWN ){
			  	if( event.key.keysym.sym == SDLK_BACKSPACE){
	          	if(campoAtivo == 1){
	          		if(strlen(nomePiloto) > 0)
									compNomePilotoDigitado = retirarUltimaLetraTextoPainel(nomePiloto, compNomePilotoDigitado);
							} else if(campoAtivo == 2){
	          		if(strlen(idadePilotoString) > 0)
									compIdadePilotoDigitado = retirarUltimaLetraTextoPainel(idadePilotoString, compIdadePilotoDigitado);
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
					} else if(campoAtivo == 2 && atoi(event.text.text) != 0){
						if(strlen(idadePilotoString)+1 <= 3 && strlen(idadePilotoString)+1 > 0)
							strcat(idadePilotoString, event.text.text);
					}
		      pintarTexto = 1;
		      //atualizaPainel = 1;
		    }
		  }
			if(pintarTexto){
      	if(strlen(nomePiloto) <= 32 && strlen(nomePiloto) > 0)
					compNomePilotoDigitado.area = pintarTextoPainel(nomePiloto, (compNomePiloto.area.x + compNomePiloto.area.w + 15), compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				if(strlen(idadePilotoString) <= 3 && strlen(idadePilotoString) > 0)
					compIdadePilotoDigitado.area = pintarTextoPainel(idadePilotoString, (compIdadePiloto.area.x + compIdadePiloto.area.w + 15), compIdadePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				
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
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuEscolhePais(char *strDestinoPaisNatal){
	int ret = 0, sair = 0, atualizaPainel = 0, campoAtivo = 0, renderText, paisAtual = 0;
	ComponenteClicado compClicado;
	Cor corFundo = COR_FUNDO, corPrincipal = COR_PRINCIPAL;
	FILE *arquivoPaises;
	Componente compTitulo, compPais;
	
	char linha[127], pais[127];
	
	arquivoPaises = fopen("Dados/Paises.guyg", "r");
	if(arquivoPaises == NULL){
		salvarErro("Erro ao abrir o arquivo dos paises 'fopen' de 'checarEventoMenuEscolhePais'\n");
	}
	
	Janela janelaPaises = criarJanela("Lista de Paises", 300, 560);
	Painel painelPaises = criarPainel(janelaPaises);
	
	compTitulo.area = pintarTextoPainel("Paises", 90, 10, FONTE_TITULO_PRINCIPAL, janelaPaises);
	
	while(!feof(arquivoPaises)){
		memset(linha, '\0', sizeof(linha));
		fgets(linha, 127, arquivoPaises);
		//strcpy(linha, rRemoveQuebraLinha(linha));
		rRemoveQuebraLinha(linha);
		if(strlen(linha) < 1) break;
		compPais.area = pintarTextoPainel(linha, 10, 60+paisAtual*20, FONTE_TEXTO_PRINCIPAL, janelaPaises);
		paisAtual++;
	}
	fclose(arquivoPaises);
	
	atualizarPainel(painelPaises);
	Retangulo retanguloOpcoesPaises;
	
	retanguloOpcoesPaises.x = 10;
	retanguloOpcoesPaises.y = 60;
	retanguloOpcoesPaises.w = compPais.area.w;
	retanguloOpcoesPaises.h = compPais.area.h * paisAtual;
	
	SDL_Event evento;
	while(!sair){
		while(SDL_WaitEvent(&evento)){
			if(evento.type == SDL_QUIT){
				compClicado = CLICADO_SAIR;
				sair = 1;
				break;
			}else if(evento.type == SDL_MOUSEBUTTONUP){
				if(verificarCliqueDentroRetangulo(retanguloOpcoesPaises)){
					int mouseY, mouseX;
					SDL_GetMouseState(&mouseX, &mouseY);
					int paisEscolhido = (int)((((mouseY - retanguloOpcoesPaises.y))/(retanguloOpcoesPaises.h/paisAtual))+1);
					int qtdLinhas = 0;
					memset(pais, '\0', sizeof(pais));
					
					arquivoPaises = fopen("Dados/Paises.guyg", "r");
					if(arquivoPaises == NULL){
						salvarErro("Erro ao abrir o arquivo dos paises 'fopen' de 'checarEventoMenuEscolhePais'\n");
					}
					
					while(qtdLinhas < paisEscolhido){
						fgets(pais, 127, arquivoPaises);
						qtdLinhas++;
						if(feof(arquivoPaises)) break;
					}
					fclose(arquivoPaises);
					sair = 1;
					break;
				}
			}
			atualizarPainel(painelPaises);
			SDL_FlushEvent(evento.type);
		}
	}
	SDL_DestroyWindow(janelaPaises);
	rRemoveQuebraLinha(pais);
	strcpy(strDestinoPaisNatal, pais);
	return compClicado;
}



// Objetivo:
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuDescricaoPiloto(int idPiloto, Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, atualizaPainel = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	FILE *arquivoPilotos;
	Componente compTitulo, compVoltar, compAlterar, compExcluir;
	Piloto pilotoDescrever;
	
	char linha[127], pais[127];
	
	arquivoPilotos = fopen("Dados/Pilotos.guyg", "r");
	if(arquivoPilotos == NULL){
		salvarErro("Erro ao abrir o arquivo dos paises 'fopen' de 'checarEventoMenuDescricaoPiloto'\n");
	}
	
	fseek(arquivoPilotos, sizeof(Piloto) * idPiloto, SEEK_SET);
	if(fread(&pilotoDescrever, sizeof(Piloto), 1, arquivoPilotos) != 1){
		salvarErro("Erro ao ler um piloto!");
		ret = 1;
	}
	fclose(arquivoPilotos);
	
	
	char strIdPiloto[12];
	char strIdadePiloto[4];
	char strSexoPiloto[9];
	sprintf(strIdPiloto, "%d", pilotoDescrever.id);
	sprintf(strIdadePiloto, "%d", pilotoDescrever.idade);
		
	SDL_Event evento;
	while(!sair){
		if(pintaMenu){
			pintaMenu = 0;
			limparPainel(painelDestino);
			compTitulo.area = pintarTextoPainel(pilotoDescrever.nome, 90, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			pintarTextoPainel("ID:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel("IDADE:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel("PAIS:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel("SEXO:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel(strIdPiloto, 80, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel(strIdadePiloto, 80, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel(pilotoDescrever.paisOrigem, 80, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel(pilotoDescrever.sexo == 'M' ? "Masculino" : "Feminino", 80, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compAlterar.area = pintarTextoPainel("Alterar", 90, 265, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compExcluir.area = pintarTextoPainel("Excluir", 210, 265, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			pintarRetanguloPainel(80, 260, compAlterar.area.w + 20, 30, COR_PRINCIPAL, painelDestino);
			pintarRetanguloPainel(200, 260, compExcluir.area.w + 20, 30, COR_PRINCIPAL, painelDestino);
			atualizarPainel(painelDestino);
		}
		while(SDL_WaitEvent(&evento)){
			if(evento.type == SDL_QUIT){
				compClicado = CLICADO_SAIR;
				sair = 1;
				break;
			}else if(evento.type == SDL_MOUSEBUTTONUP){
			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'voltar'
	    		if(verificarCliqueDentroRetangulo(compVoltar.area)){
	    		
	    		  // Define o componente que foi clicado
		  			compClicado = CLICADO_VOLTAR;
	    		
	    	  	// Define que e para cancelar o loop do menu atual
		  			sair = 1;
	    			
	    	    // Sair do loop de verificar um evento
		  			break;
				
				  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'novo piloto'
					} else if(verificarCliqueDentroRetangulo(compAlterar.area)){
	    			
	    		  // Define o componente que foi clicado
		  			compClicado = CLICADO_ALTERA_PILOTO;
					
					checarEventoMenuAlteraPiloto(&pilotoDescrever, janelaDestino, painelDestino);
					pintaMenu = 1;
	    	    // Sair do loop de verificar um evento
		  			break;
					} else if(verificarCliqueDentroRetangulo(compExcluir.area)){
	    			
	    		  // Define o componente que foi clicado
		  			compClicado = CLICADO_EXCLUI_PILOTO;
					
					char msgRet[127];
					if(excluirPiloto(pilotoDescrever) == 0)
						sprintf(msgRet, "%s excluido com sucesso!", pilotoDescrever.nome);
					else
						sprintf(msgRet, "ERRO ao excluir %s!", pilotoDescrever.nome);
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             "Excluir Piloto",
                             msgRet,
                             janelaDestino);
					sair = 1;
					break;
					}
				}
			atualizarPainel(painelDestino);
			SDL_FlushEvent(evento.type);
		}
	}
	return compClicado;
}



// Objetivo: Pinta todo o menu 'Pilotos' e espera o usuario escolher uma opcao
// Parametros: A janela e o painel onde sera pintado o Menu 'Pilotos'
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuAlteraPiloto(Piloto *pilotoAlterar, Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, campoAtivo = 0, pintarTexto = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compNomePiloto, compVoltar, compIdadePiloto, compSexoPiloto, 
	compPaisNatalPiloto, compNomePilotoUser, compSairUser, compIdadePilotoUser, 
	compSexoPilotoMUser, compSexoPilotoFUser, compPaisNatalPilotoUser, compAtualizar,
	compNomePilotoDigitado, compIdadePilotoDigitado, compSexoPilotoMText, 
	compSexoPilotoFText, compPaisNatalPilotoDigitado, compAlterar;
	char nomePiloto[127], sexoPiloto = 'M', idadePilotoString[4], paisNatal[127];
	//alocarPiloto(&pilotoCadastrar);
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	compNomePilotoDigitado.area.w = 0;
	compNomePilotoDigitado.area.h = 0;
	compPaisNatalPilotoDigitado.area.w = 0;
	compPaisNatalPilotoDigitado.area.h = 0;
	compIdadePilotoDigitado.area.w = 0;
	compIdadePilotoDigitado.area.h = 0;
	compNomePilotoDigitado.painelPertencente = painelDestino;
	compPaisNatalPilotoDigitado.painelPertencente = painelDestino;
	compIdadePilotoDigitado.painelPertencente = painelDestino;
	
	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	strcpy(nomePiloto, pilotoAlterar->nome);
	strcpy(paisNatal, pilotoAlterar->paisOrigem);
	sprintf(idadePilotoString, "%d", pilotoAlterar->idade);
	sexoPiloto = pilotoAlterar->sexo;
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("COMPLEMENTAR PILOTO", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	compNomePiloto.area = pintarTextoPainel("Nome do Piloto:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compIdadePiloto.area = pintarTextoPainel("Idade do Piloto:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compSexoPiloto.area = pintarTextoPainel("Sexo do Piloto:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compPaisNatalPiloto.area = pintarTextoPainel("Pais natal do Piloto:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compNomePilotoUser = pintarRetanguloPainel((compNomePiloto.area.x + compNomePiloto.area.w + 10), compNomePiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	compIdadePilotoUser = pintarRetanguloPainel((compIdadePiloto.area.x + compIdadePiloto.area.w + 10), compIdadePiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	compSexoPilotoMUser = pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 10), compSexoPiloto.area.y, 30, 30, (pilotoAlterar->sexo == 'M') ? COR_SELECIONADO : COR_PRINCIPAL, painelDestino);
	compSexoPilotoFUser = pintarRetanguloPainel((compSexoPiloto.area.x + compSexoPiloto.area.w + 50), compSexoPiloto.area.y, 30, 30, (pilotoAlterar->sexo == 'F') ? COR_SELECIONADO : COR_PRINCIPAL, painelDestino);
	compPaisNatalPilotoUser = pintarRetanguloPainel((compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 10), compPaisNatalPiloto.area.y, 300, 30, COR_PRINCIPAL, painelDestino);
	
	// Pinta as letras das opcoes de sexo
	pintarTextoPainel("M", (compSexoPilotoMUser.area.x+10), (compSexoPilotoMUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("F", (compSexoPilotoFUser.area.x+10), (compSexoPilotoFUser.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compNomePilotoDigitado.area = pintarTextoPainel(nomePiloto, (compNomePiloto.area.x + compNomePiloto.area.w + 15), compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compIdadePilotoDigitado.area = pintarTextoPainel(idadePilotoString, (compIdadePiloto.area.x + compIdadePiloto.area.w + 15), compIdadePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compPaisNatalPilotoDigitado.area = pintarTextoPainel(paisNatal, (compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 15), compPaisNatalPiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				
	
	// Pinta o retangulo e depois o texto da opcao de cadastrar
	compAlterar = pintarRetanguloPainel((compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 110), 260, 74, 30, COR_PRINCIPAL, painelDestino);
	pintarTextoPainel("Alterar", (compAlterar.area.x + 10), (compAlterar.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Atualizar o painel, para aparecer tudo que foi pintado
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
						compNomePilotoDigitado.area = pintarTextoPainel(nomePiloto, (compNomePiloto.area.x + compNomePiloto.area.w + 15), compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					campoAtivo = 1;
				}else if(verificarCliqueDentroRetangulo(compIdadePilotoUser.area)){
					compAtualizar = pintarRetanguloPainel((compIdadePiloto.area.x + compIdadePiloto.area.w + 10), compIdadePiloto.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(idadePilotoString) <= 3 && strlen(idadePilotoString) > 0)
						compIdadePilotoDigitado.area = pintarTextoPainel(idadePilotoString, (compIdadePiloto.area.x + compIdadePiloto.area.w + 15), compIdadePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
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
					compClicado = CLICADO_PAIS_PILOTO;
					checarEventoMenuEscolhePais(paisNatal);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPaisNatalPilotoDigitado.area);
					compPaisNatalPilotoDigitado.area = pintarTextoPainel(paisNatal, (compPaisNatalPiloto.area.x + compPaisNatalPiloto.area.w + 15), compPaisNatalPiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
        }else if(verificarCliqueDentroRetangulo(compAlterar.area)){
					/* COMPLEMENTAR USUARIO */
					pilotoAlterar->idade = atoi(idadePilotoString);
					printf("<%c>\n", atoi(idadePilotoString));
					printf("<%s>\n", idadePilotoString);
					strcpy(pilotoAlterar->nome, nomePiloto);
					strcpy(pilotoAlterar->paisOrigem, paisNatal);
					pilotoAlterar->sexo = sexoPiloto;
					alterarPiloto(*pilotoAlterar);
					char msgSucss[127];
					sprintf(msgSucss, "%s alterado com sucesso!", pilotoAlterar->nome);
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             "Piloto Alterado",
                             msgSucss,
                             janelaDestino);
				sair = 1;
				break;
        }
			}else if( event.type == SDL_KEYDOWN ){
			  	if( event.key.keysym.sym == SDLK_BACKSPACE){
	          	if(campoAtivo == 1){
	          		if(strlen(nomePiloto) > 0)
									compNomePilotoDigitado = retirarUltimaLetraTextoPainel(nomePiloto, compNomePilotoDigitado);
							} else if(campoAtivo == 2){
	          		if(strlen(idadePilotoString) > 0)
									compIdadePilotoDigitado = retirarUltimaLetraTextoPainel(idadePilotoString, compIdadePilotoDigitado);
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
					} else if(campoAtivo == 2 && atoi(event.text.text) != 0){
						if(strlen(idadePilotoString)+1 <= 3 && strlen(idadePilotoString)+1 > 0)
							strcat(idadePilotoString, event.text.text);
					}
		      pintarTexto = 1;
		      //atualizaPainel = 1;
		    }
		  }
			if(pintarTexto){
      	if(strlen(nomePiloto) <= 32 && strlen(nomePiloto) > 0)
					compNomePilotoDigitado.area = pintarTextoPainel(nomePiloto, (compNomePiloto.area.x + compNomePiloto.area.w + 15), compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				if(strlen(idadePilotoString) <= 3 && strlen(idadePilotoString) > 0)
					compIdadePilotoDigitado.area = pintarTextoPainel(idadePilotoString, (compIdadePiloto.area.x + compIdadePiloto.area.w + 15), compIdadePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				
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
int checarEventoMenuCircuitos(Janela janelaDestino, Painel painelDestino){
	int sair = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	Componente compTitulo, compNovoCircuito, compTabelaTodosCircuitos, compVoltar;
	Retangulo areaDadosListaCircuitos;
	
	// Cria a estrutura 'SDL_Event' para guardar todos evento que ocorrem
	SDL_Event evento;
	
	// Loop para nao sair do menu atual
	while(!sair){
	
	  // Verifica se e preciso pintar todo o menu
		if(pintaMenu){
			pintaMenu = 0;
		
		  // Limpa tudo o que estava pintado no painel
			limparPainel(painelDestino);
			
			// Pinta o titulo
			compTitulo.area = pintarTextoPainel("CIRCUITOS", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			
    	// Pinta as opcoes do menu		
			compNovoCircuito.area = pintarTextoPainel("Novo Circuito", 10, 40, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Pinta tabela que ficara todos os pilotos
			compTabelaTodosCircuitos = pintarTabelaPainel(10, 80, 540, 350, COR_TABELA, 5, 10, painelDestino);
			areaDadosListaCircuitos.x = compTabelaTodosCircuitos.area.x;
			areaDadosListaCircuitos.y = compTabelaTodosCircuitos.area.y + (compTabelaTodosCircuitos.area.h/10);
			areaDadosListaCircuitos.w = compTabelaTodosCircuitos.area.w;
			areaDadosListaCircuitos.h = compTabelaTodosCircuitos.area.h - (compTabelaTodosCircuitos.area.h/10);
			// Pinta o cabecalho da tabela
			pintarDadoTabela(compTabelaTodosCircuitos, 1, 1, "ID", janelaDestino);
			pintarDadoTabela(compTabelaTodosCircuitos, 1, 2, "NOME", janelaDestino);
			pintarDadoTabela(compTabelaTodosCircuitos, 1, 3, "PAIS", janelaDestino);
			pintarDadoTabela(compTabelaTodosCircuitos, 1, 4, "TAMANHO", janelaDestino);
			pintarDadoTabela(compTabelaTodosCircuitos, 1, 5, "MENOR TEMPO", janelaDestino);
			// Pinta todos os pilotos
			apresentarTodosCircuitos(compTabelaTodosCircuitos, janelaDestino);
			
    	// Atualizar o painel, para aparecer tudo que foi pintado 
			atualizarPainel(painelDestino);
		}
		
	  // Verifica se ocorreu um evento
		while(SDL_WaitEvent(&evento)){
		
		  // Verifica se o evento que ocorreu e o de fechar a janela
      if(evento.type == SDL_QUIT){
    		
    		// Define o componente que foi clicado
	      compClicado = CLICADO_FECHAR;
    		
    		// Define que e para cancelar o loop do menu atual
	      sair = 1;
    			
    	  // Sair do loop de verificar um evento
        break;
        
      // Verifica se o evento que ocorreu e o de um clique do mouse
			}else if(evento.type == SDL_MOUSEBUTTONUP){
			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'voltar'
    		if(verificarCliqueDentroRetangulo(compVoltar.area)){
    		
    		  // Define o componente que foi clicado
	  			compClicado = CLICADO_VOLTAR;
    		
    	  	// Define que e para cancelar o loop do menu atual
	  			sair = 1;
    			
    	    // Sair do loop de verificar um evento
	  			break;
			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'novo piloto'
				} else if(verificarCliqueDentroRetangulo(compNovoCircuito.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_NOVO_PILOTO;
    			
    			// Vai para o menu 'Novo pilotos' e verifica seu retorno
					switch(checarEventoMenuNovoCircuito(janelaDestino, painelDestino)){
					
					  // Caso ocorreu um evento de fechar a janela
		    		case CLICADO_FECHAR:
		    		  
    	  	    // Define que e para cancelar o loop do menu atual
		    			sair = 1;
    			
    	        // Sair do loop de verificar um evento
		    			break;
		    		
		    		// Caso ocorra qualquer outro evento
						default:
						
						  // Define que nao e para cancelar o loop do menu atual
							sair = 0;
					}
					
					// Define que e para repintar o menu 'Pilotos'
					pintaMenu = 1;
					
					// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(areaDadosListaCircuitos)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_TABELA_PILOTOS;
    			/*---------------------------------------------------------------------------------------------------------------------------------------
    			
    										 VERIFICAR QUANDO ALTERAR A PAGINACAO
    			
    			---------------------------------------------------------------------------------------------------------------------------------------*/
				int mouseY, mouseX;
				SDL_GetMouseState(&mouseX, &mouseY);
				int circuitoEscolhido = (int)(((mouseY - areaDadosListaCircuitos.y))/(areaDadosListaCircuitos.h/9));
				checarEventoMenuDescricaoCircuito(circuitoEscolhido, janelaDestino, painelDestino);
    			/*
    			// Vai para o menu 'Novo pilotos' e verifica seu retorno
					switch(checarEventoMenuNovoPiloto(janela, painelDestino)){
					
					  // Caso ocorreu um evento de fechar a janela
		    		case CLICADO_FECHAR:
		    		  
    	  	    // Define que e para cancelar o loop do menu atual
		    			sair = 1;
    			
    	        // Sair do loop de verificar um evento
		    			break;
		    		
		    		// Caso ocorra qualquer outro evento
						default:
						
						  // Define que nao e para cancelar o loop do menu atual
							sair = 0;
					}*/
					
					// Define que e para repintar o menu 'Pilotos'
					pintaMenu = 1;
					
					// Sair do loop de verificar um evento
    			break;
				}
			}
			
			// Limpa a memoria utilizada pelo evento atual
			SDL_FlushEvent(evento.type);
  	}
	}
	
	return compClicado;
}



// Objetivo: 
int checarEventoMenuNovoCircuito(Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, campoAtivo = 0, pintarTexto = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compNomeCircuito, compVoltar, compPaisCircuito, compTamanhoCircuito, 
	compMenorTempoCircuito, compCadastrar, compAtualizar, compNomeCircuitoDigitado, compPaisCircuitoDigitado, 
	compTamanhoCircuitoDigitado, compMenorTempoCircuitoDigitado;
	char nomeCircuitoString[127], paisCircuitoString[127], tamanhoCircuitoString[10], menorTempoCircuitoString[9];
	Circuito circuitoCadastrar;
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	compNomeCircuito.area.w = 0;
	compNomeCircuito.area.h = 0;
	compPaisCircuito.area.w = 0;
	compPaisCircuito.area.h = 0;
	compTamanhoCircuito.area.w = 0;
	compTamanhoCircuito.area.h = 0;
	compMenorTempoCircuito.area.w = 0;
	compMenorTempoCircuito.area.h = 0;
	compNomeCircuitoDigitado.painelPertencente = painelDestino;
	compPaisCircuitoDigitado.painelPertencente = painelDestino;
	compTamanhoCircuitoDigitado.painelPertencente = painelDestino;
	compMenorTempoCircuitoDigitado.painelPertencente = painelDestino;
	
	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(nomeCircuitoString, '\0', sizeof(nomeCircuitoString));
	memset(paisCircuitoString, '\0', sizeof(paisCircuitoString));
	memset(tamanhoCircuitoString, '\0', sizeof(tamanhoCircuitoString));
	memset(menorTempoCircuitoString, '\0', sizeof(menorTempoCircuitoString));
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("NOVO CIRCUITO", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	pintarTextoPainel("Nome:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Pais:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Tamanho:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Menor tempo:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compNomeCircuito = pintarRetanguloPainel(150, 60, 300, 30, COR_PRINCIPAL, painelDestino);
	compPaisCircuito = pintarRetanguloPainel(150, 100, 300, 30, COR_PRINCIPAL, painelDestino);
	compTamanhoCircuito = pintarRetanguloPainel(150, 140, 300, 30, COR_PRINCIPAL, painelDestino);
	compMenorTempoCircuito = pintarRetanguloPainel(150, 180, 300, 30, COR_PRINCIPAL, painelDestino);
	
	// Pinta o retangulo e depois o texto da opcao de cadastrar
	compCadastrar = pintarRetanguloPainel(230, 260, 93, 30, COR_PRINCIPAL, painelDestino);
	pintarTextoPainel("Cadastrar", (compCadastrar.area.x + 10), (compCadastrar.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Atualizar o painel, para aparecer tudo que foi pintado
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
				}else if(verificarCliqueDentroRetangulo(compNomeCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 60, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(nomeCircuitoString) <= 32 && strlen(nomeCircuitoString) > 0)
						compNomeCircuitoDigitado.area = pintarTextoPainel(nomeCircuitoString, (compNomeCircuito.area.x + 15), compNomeCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					campoAtivo = 1;
				}else if(verificarCliqueDentroRetangulo(compPaisCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 100, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_PAIS_CIRCUITO;
					checarEventoMenuEscolhePais(paisCircuitoString);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPaisCircuitoDigitado.area);
					compPaisCircuitoDigitado.area = pintarTextoPainel(paisCircuitoString, (compPaisCircuito.area.x + 15), compPaisCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
        }else if(verificarCliqueDentroRetangulo(compTamanhoCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 140, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(tamanhoCircuitoString) <= 9 && strlen(tamanhoCircuitoString) > 0)
						compTamanhoCircuitoDigitado.area = pintarTextoPainel(tamanhoCircuitoString, (compTamanhoCircuito.area.x + 15), compTamanhoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					campoAtivo = 2;
        }else if(verificarCliqueDentroRetangulo(compMenorTempoCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 180, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(menorTempoCircuitoString) <= 8 && strlen(menorTempoCircuitoString) > 0)
						compTamanhoCircuitoDigitado.area = pintarTextoPainel(menorTempoCircuitoString, (compMenorTempoCircuito.area.x + 15), compMenorTempoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					campoAtivo = 3;
        }else if(verificarCliqueDentroRetangulo(compCadastrar.area)){
					/* CADASTRAR USUARIO */
					circuitoCadastrar.tamanho = atoi(tamanhoCircuitoString);
					strcpy(circuitoCadastrar.nome, nomeCircuitoString);
					strcpy(circuitoCadastrar.pais, paisCircuitoString);
					strcpy(circuitoCadastrar.menorTempo, menorTempoCircuitoString);
					char msgRet[127];
					if(salvarCircuito(circuitoCadastrar) == 0)
						sprintf(msgRet, "%s cadastrado com sucesso!", circuitoCadastrar.nome);
					else
						sprintf(msgRet, "ERRO ao excluir %s!", circuitoCadastrar.nome);
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             "Novo Circuito",
                             msgRet,
                             janelaDestino);
				sair = 1;
				break;
        }
			}else if( event.type == SDL_KEYDOWN ){
			  	if( event.key.keysym.sym == SDLK_BACKSPACE){
	          	if(campoAtivo == 1){
	          		if(strlen(nomeCircuitoString) > 0)
									compNomeCircuitoDigitado = retirarUltimaLetraTextoPainel(nomeCircuitoString, compNomeCircuitoDigitado);
							} else if(campoAtivo == 2){
	          		if(strlen(tamanhoCircuitoString) > 0)
									compTamanhoCircuitoDigitado = retirarUltimaLetraTextoPainel(tamanhoCircuitoString, compTamanhoCircuitoDigitado);
							} else if(campoAtivo == 3){
	          		if(strlen(menorTempoCircuitoString) > 0)
									compMenorTempoCircuitoDigitado = retirarUltimaLetraTextoPainel(menorTempoCircuitoString, compMenorTempoCircuitoDigitado);
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
						if(strlen(nomeCircuitoString)+1 <= 32 && strlen(nomeCircuitoString)+1 > 0)
							strcat(nomeCircuitoString, event.text.text);
					} else if(campoAtivo == 2 && atoi(event.text.text) != 0){
						if(strlen(tamanhoCircuitoString)+1 <= 9 && strlen(tamanhoCircuitoString)+1 > 0)
							strcat(tamanhoCircuitoString, event.text.text);
					} else if(campoAtivo == 3 && atoi(event.text.text) != 0){
						if(strlen(menorTempoCircuitoString)+1 <= 8 && strlen(menorTempoCircuitoString)+1 > 0)
							strcat(menorTempoCircuitoString, event.text.text);
					}
		      pintarTexto = 1;
		      //atualizaPainel = 1;
		    }
		  }
			if(pintarTexto){
      	if(strlen(nomeCircuitoString) <= 32 && strlen(nomeCircuitoString) > 0)
					compNomeCircuitoDigitado.area = pintarTextoPainel(nomeCircuitoString, (compNomeCircuito.area.x + 15), compNomeCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				if(strlen(tamanhoCircuitoString) <= 9 && strlen(tamanhoCircuitoString) > 0)
					compTamanhoCircuitoDigitado.area = pintarTextoPainel(tamanhoCircuitoString, (compTamanhoCircuito.area.x + 15), compTamanhoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				if(strlen(menorTempoCircuitoString) <= 8 && strlen(menorTempoCircuitoString) > 0)
					compMenorTempoCircuitoDigitado.area = pintarTextoPainel(menorTempoCircuitoString, (compMenorTempoCircuito.area.x + 15), compMenorTempoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				
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
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuDescricaoCircuito(int idCircuito, Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, atualizaPainel = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	FILE *arquivoCircuitos;
	Componente compTitulo, compVoltar, compAlterar;
	Circuito circuitoDescrever;
	char linha[127], pais[127], strIdCircuito[12], strTamanhoCircuito[13];
	
	arquivoCircuitos = fopen("Dados/Circuitos.guyg", "r");
	if(arquivoCircuitos == NULL){
		salvarErro("Erro ao abrir o arquivo dos paises 'fopen' de 'checarEventoMenuDescricaoCircuito'\n");
	}
	
	fseek(arquivoCircuitos, sizeof(Circuito) * idCircuito, SEEK_SET);
	if(fread(&circuitoDescrever, sizeof(Circuito), 1, arquivoCircuitos) != 1){
		salvarErro("Erro ao ler um circuito em 'checarEventoMenuDescricaoCircuito'!");
		ret = 1;
	}
	fclose(arquivoCircuitos);
	
	memset(strIdCircuito, '\0', sizeof(strIdCircuito));
	memset(strTamanhoCircuito, '\0', sizeof(strTamanhoCircuito));
	
	sprintf(strIdCircuito, "%d", circuitoDescrever.codigo);
	sprintf(strTamanhoCircuito, "%d", circuitoDescrever.tamanho);
		
	SDL_Event evento;
	while(!sair){
		if(pintaMenu){
			pintaMenu = 0;
			limparPainel(painelDestino);
			compTitulo.area = pintarTextoPainel(circuitoDescrever.nome, 90, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			pintarTextoPainel("ID:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel("PAIS:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel("EXTENSÃO:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel("MENOR TEMPO:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel(strIdCircuito, 140, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel(circuitoDescrever.pais, 140, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel(strTamanhoCircuito, 140, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			pintarTextoPainel(circuitoDescrever.menorTempo, 140, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compAlterar.area = pintarTextoPainel("Alterar", 90, 265, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			pintarRetanguloPainel(80, 260, compAlterar.area.w + 20, 30, COR_PRINCIPAL, painelDestino);
			atualizarPainel(painelDestino);
		}
		while(SDL_WaitEvent(&evento)){
			if(evento.type == SDL_QUIT){
				compClicado = CLICADO_SAIR;
				sair = 1;
				break;
			}else if(evento.type == SDL_MOUSEBUTTONUP){
			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'voltar'
	    		if(verificarCliqueDentroRetangulo(compVoltar.area)){
	    		
	    		  // Define o componente que foi clicado
		  			compClicado = CLICADO_VOLTAR;
	    		
	    	  	// Define que e para cancelar o loop do menu atual
		  			sair = 1;
	    			
	    	    // Sair do loop de verificar um evento
		  			break;
				
				  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'novo piloto'
					} else if(verificarCliqueDentroRetangulo(compAlterar.area)){
	    			
	    		  // Define o componente que foi clicado
		  			compClicado = CLICADO_ALTERA_PILOTO;
					
					checarEventoMenuAlteraCircuito(&circuitoDescrever, janelaDestino, painelDestino);
					pintaMenu = 1;
	    	    // Sair do loop de verificar um evento
		  			break;
					}
				}
			atualizarPainel(painelDestino);
			SDL_FlushEvent(evento.type);
		}
	}
	return compClicado;
}



// Objetivo: Pinta todo o menu 'Pilotos' e espera o usuario escolher uma opcao
// Parametros: A janela e o painel onde sera pintado o Menu 'Pilotos'
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuAlteraCircuito(Circuito *circuitoAlterar, Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, campoAtivo = 0, pintarTexto = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compNomeCircuito, compVoltar, compPaisCircuito, compTamanhoCircuito, 
	compMenorTempoCircuito, compAlterar, compAtualizar, compNomeCircuitoDigitado, compPaisCircuitoDigitado, 
	compTamanhoCircuitoDigitado, compMenorTempoCircuitoDigitado;
	char nomeCircuitoString[127], paisCircuitoString[127], tamanhoCircuitoString[10], menorTempoCircuitoString[9];
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	compNomeCircuito.area.w = 0;
	compNomeCircuito.area.h = 0;
	compPaisCircuito.area.w = 0;
	compPaisCircuito.area.h = 0;
	compTamanhoCircuito.area.w = 0;
	compTamanhoCircuito.area.h = 0;
	compMenorTempoCircuito.area.w = 0;
	compMenorTempoCircuito.area.h = 0;
	compNomeCircuitoDigitado.painelPertencente = painelDestino;
	compPaisCircuitoDigitado.painelPertencente = painelDestino;
	compTamanhoCircuitoDigitado.painelPertencente = painelDestino;
	compMenorTempoCircuitoDigitado.painelPertencente = painelDestino;
	
	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(nomeCircuitoString, '\0', sizeof(nomeCircuitoString));
	memset(paisCircuitoString, '\0', sizeof(paisCircuitoString));
	memset(tamanhoCircuitoString, '\0', sizeof(tamanhoCircuitoString));
	memset(menorTempoCircuitoString, '\0', sizeof(menorTempoCircuitoString));
	
	strcpy(nomeCircuitoString, circuitoAlterar->nome);
	strcpy(paisCircuitoString, circuitoAlterar->pais);
	strcpy(menorTempoCircuitoString, circuitoAlterar->menorTempo);
	sprintf(tamanhoCircuitoString, "%d", circuitoAlterar->tamanho);
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("COMPLEMENTAR CIRCUITO", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	compNomeCircuito.area = pintarTextoPainel("Nome:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compPaisCircuito.area = pintarTextoPainel("Pais:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compTamanhoCircuito.area = pintarTextoPainel("Extensão:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compMenorTempoCircuito.area = pintarTextoPainel("Menor tempo:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compNomeCircuito = pintarRetanguloPainel(150, 60, 300, 30, COR_PRINCIPAL, painelDestino);
	compPaisCircuito = pintarRetanguloPainel(150, 100, 300, 30, COR_PRINCIPAL, painelDestino);
	compTamanhoCircuito = pintarRetanguloPainel(150, 140, 300, 30, COR_PRINCIPAL, painelDestino);
	compMenorTempoCircuito = pintarRetanguloPainel(150, 180, 300, 30, COR_PRINCIPAL, painelDestino);
	
	// Pinta as letras das opcoes de sexo
	compNomeCircuitoDigitado.area = pintarTextoPainel(nomeCircuitoString, (compNomeCircuito.area.x + 15), compNomeCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compPaisCircuitoDigitado.area = pintarTextoPainel(paisCircuitoString, (compPaisCircuito.area.x + 15), compPaisCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compTamanhoCircuitoDigitado.area =  pintarTextoPainel(tamanhoCircuitoString, (compTamanhoCircuito.area.x + 15), compTamanhoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compMenorTempoCircuitoDigitado.area = pintarTextoPainel(menorTempoCircuitoString, (compMenorTempoCircuito.area.x + 15), compMenorTempoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				
	
	// Pinta o retangulo e depois o texto da opcao de cadastrar
	compAlterar = pintarRetanguloPainel(230, 260, 74, 30, COR_PRINCIPAL, painelDestino);
	pintarTextoPainel("Alterar", (compAlterar.area.x + 10), (compAlterar.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Atualizar o painel, para aparecer tudo que foi pintado
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
				}else if(verificarCliqueDentroRetangulo(compNomeCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 60, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(nomeCircuitoString) <= 32 && strlen(nomeCircuitoString) > 0)
						compNomeCircuitoDigitado.area = pintarTextoPainel(nomeCircuitoString, (compNomeCircuito.area.x + 15), compNomeCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					campoAtivo = 1;
				}else if(verificarCliqueDentroRetangulo(compPaisCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 100, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_PAIS_CIRCUITO;
					checarEventoMenuEscolhePais(paisCircuitoString);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPaisCircuitoDigitado.area);
					compPaisCircuitoDigitado.area = pintarTextoPainel(paisCircuitoString, (compPaisCircuito.area.x + 15), compPaisCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
        }else if(verificarCliqueDentroRetangulo(compTamanhoCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 140, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(tamanhoCircuitoString) <= 9 && strlen(tamanhoCircuitoString) > 0)
						compTamanhoCircuitoDigitado.area = pintarTextoPainel(tamanhoCircuitoString, (compTamanhoCircuito.area.x + 15), compTamanhoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					campoAtivo = 2;
        }else if(verificarCliqueDentroRetangulo(compMenorTempoCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 180, 300, 30, COR_SELECIONADO, painelDestino);
					if(strlen(menorTempoCircuitoString) <= 8 && strlen(menorTempoCircuitoString) > 0)
						compMenorTempoCircuitoDigitado.area = pintarTextoPainel(menorTempoCircuitoString, (compMenorTempoCircuito.area.x + 15), compMenorTempoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					campoAtivo = 3;
        }else if(verificarCliqueDentroRetangulo(compAlterar.area)){
					/* COMPLEMENTAR USUARIO */
					circuitoAlterar->tamanho = atoi(tamanhoCircuitoString);
					strcpy(circuitoAlterar->nome, nomeCircuitoString);
					strcpy(circuitoAlterar->pais, paisCircuitoString);
					strcpy(circuitoAlterar->menorTempo, menorTempoCircuitoString);
					char msgRet[127];
					if(alterarCircuito(*circuitoAlterar) == 0)
						sprintf(msgRet, "%s alterado com sucesso!", circuitoAlterar->nome);
					else
						sprintf(msgRet, "ERRO ao alterar %s!", circuitoAlterar->nome);
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             "Complementar Circuito",
                             msgRet,
                             janelaDestino);
				sair = 1;
				break;
        }
			}else if( event.type == SDL_KEYDOWN ){
			  	if( event.key.keysym.sym == SDLK_BACKSPACE){
	          	if(campoAtivo == 1){
	          		if(strlen(nomeCircuitoString) > 0)
									compNomeCircuitoDigitado = retirarUltimaLetraTextoPainel(nomeCircuitoString, compNomeCircuitoDigitado);
							} else if(campoAtivo == 2){
	          		if(strlen(tamanhoCircuitoString) > 0)
									compTamanhoCircuitoDigitado = retirarUltimaLetraTextoPainel(tamanhoCircuitoString, compTamanhoCircuitoDigitado);
							} else if(campoAtivo == 3){
	          		if(strlen(menorTempoCircuitoString) > 0)
									compMenorTempoCircuitoDigitado = retirarUltimaLetraTextoPainel(menorTempoCircuitoString, compMenorTempoCircuitoDigitado);
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
						if(strlen(nomeCircuitoString)+1 <= 32 && strlen(nomeCircuitoString)+1 > 0)
							strcat(nomeCircuitoString, event.text.text);
					} else if(campoAtivo == 2 && atoi(event.text.text) != 0){
						if(strlen(tamanhoCircuitoString)+1 <= 9 && strlen(tamanhoCircuitoString)+1 > 0)
							strcat(tamanhoCircuitoString, event.text.text);
					} else if(campoAtivo == 3 && atoi(event.text.text) != 0){
						if(strlen(menorTempoCircuitoString)+1 <= 8 && strlen(menorTempoCircuitoString)+1 > 0)
							strcat(menorTempoCircuitoString, event.text.text);
					}
		      pintarTexto = 1;
		      //atualizaPainel = 1;
		    }
		  }
			if(pintarTexto){
      	if(strlen(nomeCircuitoString) <= 32 && strlen(nomeCircuitoString) > 0)
					compNomeCircuitoDigitado.area = pintarTextoPainel(nomeCircuitoString, (compNomeCircuito.area.x + 15), compNomeCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				if(strlen(tamanhoCircuitoString) <= 9 && strlen(tamanhoCircuitoString) > 0)
					compTamanhoCircuitoDigitado.area = pintarTextoPainel(tamanhoCircuitoString, (compTamanhoCircuito.area.x + 15), compTamanhoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				if(strlen(menorTempoCircuitoString) <= 8 && strlen(menorTempoCircuitoString) > 0)
					compMenorTempoCircuitoDigitado.area = pintarTextoPainel(menorTempoCircuitoString, (compMenorTempoCircuito.area.x + 15), compMenorTempoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				
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


#endif /* _FUNCOES_MENU_C_ */
