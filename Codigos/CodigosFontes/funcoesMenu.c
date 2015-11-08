#ifndef _FUNCOES_MENU_C_
#define _FUNCOES_MENU_C_

#include <Cabecalhos/tiposDadosJanela.h>
#include <Cabecalhos/funcoesJanela.h>
#include <Cabecalhos/funcoesPiloto.h>
#include <Cabecalhos/funcoesCircuito.h>
#include <Cabecalhos/funcoesMelhorVolta.h>
#include <stdio.h>



// Objetivo: Pinta todo o menu principal e espera o usuario escolher uma opcao
// Parametros: A janela e o painel onde sera pintado o Menu Principal
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuPrincipal(Janela janelaDestino, Painel painelDestino){
//int pintarMenuPrincipalEEsperaEscolherOpcao(Janela janela, Painel painelDestino){
	int sair = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	Componente compTitulo, compPilotos, compCircuitos, compMelhoresVoltas, compRelatorios, compSair;
	
	
	// Cria a estrutura 'SDL_Event' para guardar todos evento que ocorrem
	SDL_Event evento;
	
	// Loop para nao fechar a janela
	while(!sair){
	
	  // Verifica se e preciso pintar todo o menu
	  if(pintaMenu){
	  	pintaMenu = 0;
	  	
			// Limpa todo o painel
			limparPainel(painelDestino);
			
			// Pintar o titulo
			compTitulo.area = pintarTextoPainel("MENU PRINCIPAL", 180, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			
			// Pinta as opcoes do menu
			compPilotos.area = pintarTextoPainel("Pilotos", 10, 40, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compCircuitos.area = pintarTextoPainel("Circuitos", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compMelhoresVoltas.area = pintarTextoPainel("Melhores Voltas", 10, 80, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compRelatorios.area = pintarTextoPainel("Relatorios", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compSair.area = pintarTextoPainel("SAIR", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			Retangulo rect = {100, 200, 100, 100};
			Superficie sJanela = SDL_GetWindowSurface(janelaDestino);
			Superficie nascarS = SDL_LoadBMP("nascarIco.bmp");
			SDL_BlitSurface(nascarS, NULL, sJanela, &rect);
			SDL_UpdateWindowSurface(janelaDestino);
			
			// Atualizar o painel, para aparecer tudo que foi pintado 
			atualizarPainel(painelDestino);
		}
		
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
    			
					switch(checarEventoMenuPilotos(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compCircuitos.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_CIRCUITOS;
    			
					switch(checarEventoMenuCircuitos(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compMelhoresVoltas.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_MELHORES_VOLTAS;
    			
					switch(checarEventoMenuMelhoresVoltas(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compRelatorios.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_MELHORES_VOLTAS;
    			
					switch(checarEventoMenuRelatorios(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}
    			
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
	int sair = 0, pintaMenu = 1, qtdPilotos = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compNovoPiloto, compTabelaTodosPilotos, compVoltar;
	Retangulo areaDadosListaPilotos;
	Piloto *todosPilotos = NULL;
	
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
			areaDadosListaPilotos.y = compTabelaTodosPilotos.area.y + compTabelaTodosPilotos.areaAux.h;
			areaDadosListaPilotos.w = compTabelaTodosPilotos.area.w;
			areaDadosListaPilotos.h = compTabelaTodosPilotos.area.h - compTabelaTodosPilotos.areaAux.h;
			// Pinta o cabecalho da tabela
			pintarDadoTabela(compTabelaTodosPilotos, 1, 1, "ID", janelaDestino);
			pintarDadoTabela(compTabelaTodosPilotos, 1, 2, "NOME", janelaDestino);
			pintarDadoTabela(compTabelaTodosPilotos, 1, 3, "IDADE", janelaDestino);
			pintarDadoTabela(compTabelaTodosPilotos, 1, 4, "SEXO", janelaDestino);
			pintarDadoTabela(compTabelaTodosPilotos, 1, 5, "PAIS", janelaDestino);
			// Pinta todos os pilotos
			qtdPilotos = pesquisarTodosPilotos(&todosPilotos);
			if(qtdPilotos > 0)
				apresentarPilotosPesquisados(todosPilotos, qtdPilotos, compTabelaTodosPilotos, janelaDestino);
			
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
		    		  	compClicado = CLICADO_FECHAR;
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
				if(qtdPilotos > 0)
					checarEventoMenuDescricaoPiloto(todosPilotos[pilotoEscolhido].id, janelaDestino, painelDestino, 1);
    			
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
	Componente compTitulo, compIdPiloto, compNomePiloto, compIdadePiloto, compSexoPilotoM, 
	compSexoPilotoF, compPaisNatalPiloto, compAtualizar, compCadastrar, compVoltar;
	char idPilotoString[9], nomePiloto[127], sexoPiloto = 'M', idadePilotoString[4], paisNatal[127];
	Piloto pilotoCadastrar;
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	inicializarComponente(&compIdPiloto, painelDestino);
	inicializarComponente(&compNomePiloto, painelDestino);
	inicializarComponente(&compPaisNatalPiloto, painelDestino);
	inicializarComponente(&compIdadePiloto, painelDestino);
	
	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(idPilotoString, '\0', strlen(idPilotoString));
	memset(nomePiloto, '\0', strlen(nomePiloto));
	memset(idadePilotoString, '\0', strlen(idadePilotoString));
	memset(paisNatal, '\0', strlen(paisNatal));
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("NOVO PILOTO", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	pintarTextoPainel("Id:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Nome:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Idade:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Sexo:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Pais Natal:", 10, 220, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compIdPiloto = pintarRetanguloPainel(120, 60, 300, 30, COR_PRINCIPAL, painelDestino);
	compNomePiloto = pintarRetanguloPainel(120, 100, 300, 30, COR_PRINCIPAL, painelDestino);
	compIdadePiloto = pintarRetanguloPainel(120, 140, 300, 30, COR_PRINCIPAL, painelDestino);
	compSexoPilotoM = pintarRetanguloPainel(120, 180, 30, 30, COR_SELECIONADO, painelDestino);
	compSexoPilotoF = pintarRetanguloPainel(170, 180, 30, 30, COR_PRINCIPAL, painelDestino);
	compPaisNatalPiloto = pintarRetanguloPainel(120, 220, 300, 30, COR_PRINCIPAL, painelDestino);
	
	// Pinta as letras das opcoes de sexo
	pintarTextoPainel("M", (compSexoPilotoM.area.x+10), (compSexoPilotoM.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("F", (compSexoPilotoF.area.x+10), (compSexoPilotoF.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
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
				}else if(verificarCliqueDentroRetangulo(compSexoPilotoM.area)){
					pintarRetanguloPainel(170, 180, 30, 30, COR_PRINCIPAL, painelDestino);
					pintarRetanguloPainel(120, 180, 30, 30, COR_SELECIONADO, painelDestino);
					sexoPiloto = 'M';
        }else if(verificarCliqueDentroRetangulo(compSexoPilotoF.area)){
					pintarRetanguloPainel(120, 180, 30, 30, COR_PRINCIPAL, painelDestino);
					pintarRetanguloPainel(170, 180, 30, 30, COR_SELECIONADO, painelDestino);
					sexoPiloto = 'F';
        }else if(verificarCliqueDentroRetangulo(compPaisNatalPiloto.area)){
					compAtualizar = pintarRetanguloPainel(compPaisNatalPiloto.area.x, compPaisNatalPiloto.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_PAIS_PILOTO;
					checarEventoMenuEscolhePais(paisNatal);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPaisNatalPiloto.areaAux);
					compPaisNatalPiloto.areaAux = pintarTextoPainel(paisNatal, (compPaisNatalPiloto.area.x + 15), compPaisNatalPiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
        }else if(verificarCliqueDentroRetangulo(compCadastrar.area)){
					/* CADASTRAR PILOTO */
					char msgRet[127];
					if(validaCamposBrancos(4, idPilotoString, idadePilotoString, nomePiloto, paisNatal)){
						pilotoCadastrar.id = atoi(idPilotoString);
						pilotoCadastrar.idade = atoi(idadePilotoString);
						strcpy(pilotoCadastrar.nome, nomePiloto);
						strcpy(pilotoCadastrar.paisOrigem, paisNatal);
						pilotoCadastrar.sexo = sexoPiloto;
						if(salvarPiloto(pilotoCadastrar) == 0)
							sprintf(msgRet, "%s cadastrado com sucesso!", pilotoCadastrar.nome);
						else
							sprintf(msgRet, "ERRO ao cadastrar %s!", pilotoCadastrar.nome);
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
	                             "Novo Piloto",
	                             msgRet,
	                             janelaDestino);
						sair = 1;
					}else
						ERRO_CAMPO_NULO(janelaDestino);
					break;
        }
			}
			if(manipularCampoTexto(&event, &compIdPiloto, idPilotoString, janelaDestino, 0, 8, 1))
				compAtualizar = compIdPiloto;
			if(manipularCampoTexto(&event, &compNomePiloto, nomePiloto, janelaDestino, 0, 32, 0))
				compAtualizar = compNomePiloto;
			if(manipularCampoTexto(&event, &compIdadePiloto, idadePilotoString, janelaDestino, 0, 3, 1))
				compAtualizar = compIdadePiloto;
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
	FILE *arquivoPaises;
	Componente compTitulo, compPais;
	SDL_Event evento;
	char linha[127], pais[127];
	
	memset(pais, '\0', strlen(pais));
	strcpy(strDestinoPaisNatal, "-");
	
	Janela janelaPaises = criarJanela("Lista de Paises", 300, 560);
	Painel painelPaises = criarPainel(janelaPaises);
	
	compTitulo.area = pintarTextoPainel("Paises", 90, 10, FONTE_TITULO_PRINCIPAL, janelaPaises);
	
	arquivoPaises = fopen("Dados/Paises.txt", "r");
	if(arquivoPaises == NULL){
		salvarErro("Erro ao abrir o arquivo dos paises 'fopen' de 'checarEventoMenuEscolhePais'\n");
		ret = 1;
	}else{
		while(!feof(arquivoPaises)){
			memset(linha, '\0', strlen(linha));
			fgets(linha, 127, arquivoPaises);
			//strcpy(linha, rRemoveQuebraLinha(linha));
			rRemoveQuebraLinha(linha);
			if(strlen(linha) < 1) break;
			compPais.area = pintarTextoPainel(linha, 10, 60+paisAtual*20, FONTE_TEXTO_PRINCIPAL, janelaPaises);
			paisAtual++;
		}
		if(fclose(arquivoPaises) != 0){
			salvarErro("Erro ao fechar o arquivo dos paises 'fopen' de 'checarEventoMenuEscolhePais'\n");
			ret = 1;
		}
	}
	
	if(ret == 0){
	atualizarPainel(painelPaises);
	Retangulo retanguloOpcoesPaises;
	
	retanguloOpcoesPaises.x = 10;
	retanguloOpcoesPaises.y = 60;
	retanguloOpcoesPaises.w = compPais.area.w;
	retanguloOpcoesPaises.h = compPais.area.h * paisAtual;
	
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
						
						arquivoPaises = fopen("Dados/Paises.txt", "r");
						if(arquivoPaises == NULL){
							salvarErro("Erro ao abrir o arquivo dos paises 'fopen' de 'checarEventoMenuEscolhePais'\n");
							sair = 1;
							break;
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
		if(evento.type != SDL_QUIT){
			rRemoveQuebraLinha(pais);
			strcpy(strDestinoPaisNatal, pais);
		}
	}
	SDL_DestroyWindow(janelaPaises);
	return compClicado;
}



// Objetivo:
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuDescricaoPiloto(int idPiloto, Janela janelaDestino, Painel painelDestino, int aparecerOpcoes){
	int sair = 0, atualizaPainel = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	Componente compTitulo, compVoltar, compAlterar, compExcluir;
	Piloto pilotoDescrever;	
	char linha[127], pais[127], strIdPiloto[12], strIdadePiloto[4], strSexoPiloto[9];
	
	inicializarComponente(&compAlterar, painelDestino);
	inicializarComponente(&compExcluir, painelDestino);
	
	if(pesquisarPilotoPId(idPiloto, &pilotoDescrever) != 1){
		salvarErro("Erro ao pesquisar o pilotos em 'checarEventoMenuDescricaoPiloto'\n");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Descrever Piloto", "Erro ao descrever Piloto", janelaDestino);
	}else{
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
				if(aparecerOpcoes){
					compAlterar.area = pintarTextoPainel("Alterar", 90, 265, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					compExcluir.area = pintarTextoPainel("Excluir", 210, 265, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					pintarRetanguloPainel(80, 260, compAlterar.area.w + 20, 30, COR_PRINCIPAL, painelDestino);
					pintarRetanguloPainel(200, 260, compExcluir.area.w + 20, 30, COR_PRINCIPAL, painelDestino);
				}
				compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
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
							sprintf(strIdPiloto, "%d", pilotoDescrever.id);
							sprintf(strIdadePiloto, "%d", pilotoDescrever.idade);
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
	}
	
	return compClicado;
}



// Objetivo: Pinta todo o menu 'Pilotos' e espera o usuario escolher uma opcao
// Parametros: A janela e o painel onde sera pintado o Menu 'Pilotos'
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuAlteraPiloto(Piloto *pilotoAlterar, Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, campoAtivo = 0, pintarTexto = 0, idAntigo;
	ComponenteClicado compClicado;
	Componente compTitulo, compIdPiloto, compNomePiloto, compIdadePiloto, compSexoPilotoM, 
	compSexoPilotoF, compPaisNatalPiloto, compAtualizar, compAlterar, compVoltar;
	char idPilotoString[9], nomePiloto[127], sexoPiloto, idadePilotoString[4], paisNatal[127];
	//alocarPiloto(&pilotoCadastrar);
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	inicializarComponente(&compIdPiloto, painelDestino);
	inicializarComponente(&compNomePiloto, painelDestino);
	inicializarComponente(&compPaisNatalPiloto, painelDestino);
	inicializarComponente(&compIdadePiloto, painelDestino);
	
	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	strcpy(nomePiloto, pilotoAlterar->nome);
	strcpy(paisNatal, pilotoAlterar->paisOrigem);
	sprintf(idadePilotoString, "%d", pilotoAlterar->idade);
	sprintf(idPilotoString, "%d", pilotoAlterar->id);
	sexoPiloto = pilotoAlterar->sexo;
	idAntigo = pilotoAlterar->id;
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("COMPLEMENTAR PILOTO", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	pintarTextoPainel("Id:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Nome:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Idade:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Sexo:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Pais natal:", 10, 220, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compIdPiloto = pintarRetanguloPainel(120, 60, 300, 30, COR_PRINCIPAL, painelDestino);
	compNomePiloto = pintarRetanguloPainel(120, 100, 300, 30, COR_PRINCIPAL, painelDestino);
	compIdadePiloto = pintarRetanguloPainel(120, 140, 300, 30, COR_PRINCIPAL, painelDestino);
	compSexoPilotoM = pintarRetanguloPainel(120, 180, 30, 30, (pilotoAlterar->sexo == 'M') ? COR_SELECIONADO : COR_PRINCIPAL, painelDestino);
	compSexoPilotoF = pintarRetanguloPainel(170, 180, 30, 30, (pilotoAlterar->sexo == 'F') ? COR_SELECIONADO : COR_PRINCIPAL, painelDestino);
	compPaisNatalPiloto = pintarRetanguloPainel(120, 220, 300, 30, COR_PRINCIPAL, painelDestino);
	
	// Pinta as letras das opcoes de sexo
	pintarTextoPainel("M", (compSexoPilotoM.area.x+10), (compSexoPilotoM.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("F", (compSexoPilotoF.area.x+10), (compSexoPilotoF.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compNomePiloto.areaAux = pintarTextoPainel(nomePiloto, (compNomePiloto.area.x + 15), compNomePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compIdadePiloto.areaAux = pintarTextoPainel(idadePilotoString, (compIdadePiloto.area.x + 15), compIdadePiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compPaisNatalPiloto.areaAux = pintarTextoPainel(paisNatal, (compPaisNatalPiloto.area.x + 15), compPaisNatalPiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compIdPiloto.areaAux = pintarTextoPainel(idPilotoString, (compIdPiloto.area.x + 15), compIdPiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
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
				}else if(verificarCliqueDentroRetangulo(compSexoPilotoM.area)){
					pintarRetanguloPainel(170, 180, 30, 30, COR_PRINCIPAL, painelDestino);
					pintarRetanguloPainel(120, 180, 30, 30, COR_SELECIONADO, painelDestino);
					sexoPiloto = 'M';
        }else if(verificarCliqueDentroRetangulo(compSexoPilotoF.area)){
					pintarRetanguloPainel(120, 180, 30, 30, COR_PRINCIPAL, painelDestino);
					pintarRetanguloPainel(170, 180, 30, 30, COR_SELECIONADO, painelDestino);
					sexoPiloto = 'F';
        }else if(verificarCliqueDentroRetangulo(compPaisNatalPiloto.area)){
					compAtualizar = pintarRetanguloPainel(compPaisNatalPiloto.area.x, compPaisNatalPiloto.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_PAIS_PILOTO;
					checarEventoMenuEscolhePais(paisNatal);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPaisNatalPiloto.areaAux);
					compPaisNatalPiloto.areaAux = pintarTextoPainel(paisNatal, (compPaisNatalPiloto.area.x + 15), compPaisNatalPiloto.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
        }else if(verificarCliqueDentroRetangulo(compAlterar.area)){
					/* COMPLEMENTAR PILOTO */
					char msgRet[127];
					if(validaCamposBrancos(4, idPilotoString, idadePilotoString, nomePiloto, paisNatal)){
						pilotoAlterar->id = atoi(idPilotoString);
						pilotoAlterar->idade = atoi(idadePilotoString);
						strcpy(pilotoAlterar->nome, nomePiloto);
						strcpy(pilotoAlterar->paisOrigem, paisNatal);
						pilotoAlterar->sexo = sexoPiloto;
						if(alterarPiloto(idAntigo, *pilotoAlterar) == 0)
							sprintf(msgRet, "%s complementado com sucesso!", pilotoAlterar->nome);
						else
							sprintf(msgRet, "ERRO ao complementar %s!", pilotoAlterar->nome);
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
	                             "Complementar Piloto",
	                             msgRet,
	                             janelaDestino);
						sair = 1;
					}else
						ERRO_CAMPO_NULO(janelaDestino);
					break;
        }
			}
			if(manipularCampoTexto(&event, &compIdPiloto, idPilotoString, janelaDestino, 0, 8, 1))
				compAtualizar = compNomePiloto;
			if(manipularCampoTexto(&event, &compNomePiloto, nomePiloto, janelaDestino, 0, 32, 0))
				compAtualizar = compNomePiloto;
			if(manipularCampoTexto(&event, &compIdadePiloto, idadePilotoString, janelaDestino, 0, 3, 1))
				compAtualizar = compIdadePiloto;
			atualizarPainel(painelDestino);
			SDL_FlushEvent(event.type);
		}
	}
  SDL_StopTextInput();
	
	return compClicado;
}



// Objetivo: 
int checarEventoMenuCircuitos(Janela janelaDestino, Painel painelDestino){
	int sair = 0, pintaMenu = 1, qtdCircuitos = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compNovoCircuito, compTabelaTodosCircuitos, compVoltar;
	Retangulo areaDadosListaCircuitos;
	Circuito *todosCircuitos = NULL;
	
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
			compTabelaTodosCircuitos = pintarTabelaPainel(10, 80, 540, 350, COR_TABELA, 6, 10, painelDestino);
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
			pintarDadoTabela(compTabelaTodosCircuitos, 1, 6, "PILOTO", janelaDestino);
			// Pinta todos os pilotos
			qtdCircuitos = pesquisarTodosCircuitos(&todosCircuitos);
			//printf("=%d\n", qtdCircuitos);
			if(qtdCircuitos > 0)
			 apresentarCircuitosPesquisados(todosCircuitos, qtdCircuitos, compTabelaTodosCircuitos, janelaDestino);
			
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
				checarEventoMenuDescricaoCircuito(circuitoEscolhido, janelaDestino, painelDestino, 1);
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
	Componente compTitulo, compNomeCircuito, compVoltar, compPaisCircuito, 
	compTamanhoCircuito, compCadastrar, compAtualizar;
	char nomeCircuitoString[127], paisCircuitoString[127], tamanhoCircuitoString[10];
	Circuito circuitoCadastrar;
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	inicializarComponente(&compNomeCircuito, painelDestino);
	inicializarComponente(&compPaisCircuito, painelDestino);
	inicializarComponente(&compTamanhoCircuito, painelDestino);
	
	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(nomeCircuitoString, '\0', sizeof(nomeCircuitoString));
	memset(paisCircuitoString, '\0', sizeof(paisCircuitoString));
	memset(tamanhoCircuitoString, '\0', sizeof(tamanhoCircuitoString));
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("NOVO CIRCUITO", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	pintarTextoPainel("Nome:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Pais:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Tamanho:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compNomeCircuito = pintarRetanguloPainel(150, 60, 300, 30, COR_PRINCIPAL, painelDestino);
	compPaisCircuito = pintarRetanguloPainel(150, 100, 300, 30, COR_PRINCIPAL, painelDestino);
	compTamanhoCircuito = pintarRetanguloPainel(150, 140, 300, 30, COR_PRINCIPAL, painelDestino);
	
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
				}else if(verificarCliqueDentroRetangulo(compPaisCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 100, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_PAIS_CIRCUITO;
					checarEventoMenuEscolhePais(paisCircuitoString);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPaisCircuito.areaAux);
					compPaisCircuito.areaAux = pintarTextoPainel(paisCircuitoString, (compPaisCircuito.area.x + 15), compPaisCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
        }else if(verificarCliqueDentroRetangulo(compCadastrar.area)){
					/* CADASTRAR USUARIO */
					char msgRet[127];
					if(validaCamposBrancos(3, nomeCircuitoString, paisCircuitoString, tamanhoCircuitoString)){
						circuitoCadastrar.tamanho = atof(tamanhoCircuitoString);
						strcpy(circuitoCadastrar.nome, nomeCircuitoString);
						strcpy(circuitoCadastrar.pais, paisCircuitoString);
						strcpy(circuitoCadastrar.menorTempo, "-");
						circuitoCadastrar.idPiloto =  0;
						if(salvarCircuito(circuitoCadastrar) == 0)
							sprintf(msgRet, "%s cadastrado com sucesso!", circuitoCadastrar.nome);
						else
							sprintf(msgRet, "ERRO ao cadastrar %s!", circuitoCadastrar.nome);
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
	                             "Novo Circuito",
	                             msgRet,
	                             janelaDestino);
						sair = 1;
					}else
						ERRO_CAMPO_NULO(janelaDestino);
					break;
        }
			}
			if(manipularCampoTexto(&event, &compNomeCircuito, nomeCircuitoString, janelaDestino, 0, 32, 0))
				compAtualizar = compNomeCircuito;
			if(manipularCampoTexto(&event, &compTamanhoCircuito, tamanhoCircuitoString, janelaDestino, 0, 9, 0))
				compAtualizar = compTamanhoCircuito;
			atualizarPainel(painelDestino);
			SDL_FlushEvent(event.type);
		}
	}
  SDL_StopTextInput();
	
	return compClicado;
}



// Objetivo:
int checarEventoMenuDescricaoCircuito(int idCircuito, Janela janelaDestino, Painel painelDestino, int aparecerOpcoes){
	int ret = 0, sair = 0, atualizaPainel = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	Componente compTitulo, compVoltar, compAlterar;
	Circuito circuitoDescrever;
	Piloto pilotoMelhorVolta;
	char linha[127], nomePiloto[127], strIdCircuito[12], strTamanhoCircuito[127], strIdPiloto[12];
	
	if(pesquisarCircuitoPId(idCircuito, &circuitoDescrever) != 1){
		salvarErro("Erro ao pesquisar o circuito em 'checarEventoMenuDescricaoCircuito'\n");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Descrever Circuito", "Erro ao descrever Circuito", janelaDestino);
	}else{
		memset(strIdCircuito, '\0', strlen(strIdCircuito));
		memset(strTamanhoCircuito, '\0', strlen(strTamanhoCircuito));
		memset(strIdPiloto, '\0', strlen(strIdPiloto));
		memset(nomePiloto, '\0', strlen(nomePiloto));
		strcpy(strIdPiloto, "-");
		strcpy(nomePiloto, "-");
		sprintf(strIdCircuito, "%d", circuitoDescrever.codigo);
		sprintf(strTamanhoCircuito, "%lf", circuitoDescrever.tamanho);
		if(pesquisarPilotoPId(circuitoDescrever.idPiloto, &pilotoMelhorVolta) == 1){
			sprintf(strIdPiloto, "%d", circuitoDescrever.idPiloto);
			strcpy(nomePiloto, pilotoMelhorVolta.nome);
		}
		
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
				pintarTextoPainel("ID PILOTO:", 10, 220, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				pintarTextoPainel("PILOTO:", 10, 260, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				pintarTextoPainel(strIdCircuito, 140, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				pintarTextoPainel(circuitoDescrever.pais, 140, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				pintarTextoPainel(strTamanhoCircuito, 140, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				pintarTextoPainel(circuitoDescrever.menorTempo, 140, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				pintarTextoPainel(strIdPiloto, 140, 220, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				pintarTextoPainel(nomePiloto, 140, 260, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				if(aparecerOpcoes){
					compAlterar.areaAux = pintarTextoPainel("Alterar", 90, 305, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					compAlterar = pintarRetanguloPainel(compAlterar.areaAux.x-10, compAlterar.areaAux.y-5, compAlterar.areaAux.w + 20, 30, COR_PRINCIPAL, painelDestino);
				}
				compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
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
						sprintf(strIdCircuito, "%d", circuitoDescrever.codigo);
						sprintf(strTamanhoCircuito, "%d", circuitoDescrever.tamanho);
						pintaMenu = 1;
	    	    // Sair do loop de verificar um evento
		  			break;
					}
				}
				atualizarPainel(painelDestino);
				SDL_FlushEvent(evento.type);
			}
		}
	}
	
	return compClicado;
}



// Objetivo: 
int checarEventoMenuAlteraCircuito(Circuito *circuitoAlterar, Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, campoAtivo = 0, pintarTexto = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compNomeCircuito, compVoltar, compPaisCircuito, compTamanhoCircuito, 
	compAlterar, compAtualizar;
	char nomeCircuitoString[127], paisCircuitoString[127], tamanhoCircuitoString[10];
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	inicializarComponente(&compNomeCircuito, painelDestino);
	inicializarComponente(&compPaisCircuito, painelDestino);
	inicializarComponente(&compTamanhoCircuito, painelDestino);
	
	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(nomeCircuitoString, '\0', strlen(nomeCircuitoString));
	memset(paisCircuitoString, '\0', strlen(paisCircuitoString));
	memset(tamanhoCircuitoString, '\0', strlen(tamanhoCircuitoString));
	
	strcpy(nomeCircuitoString, circuitoAlterar->nome);
	strcpy(paisCircuitoString, circuitoAlterar->pais);
	sprintf(tamanhoCircuitoString, "%d", circuitoAlterar->tamanho);
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("COMPLEMENTAR CIRCUITO", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	pintarTextoPainel("Nome:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Pais:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Extensão:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compNomeCircuito = pintarRetanguloPainel(150, 60, 300, 30, COR_PRINCIPAL, painelDestino);
	compPaisCircuito = pintarRetanguloPainel(150, 100, 300, 30, COR_PRINCIPAL, painelDestino);
	compTamanhoCircuito = pintarRetanguloPainel(150, 140, 300, 30, COR_PRINCIPAL, painelDestino);
	
	// Pinta as letras das opcoes de sexo
	compNomeCircuito.areaAux = pintarTextoPainel(nomeCircuitoString, (compNomeCircuito.area.x + 15), compNomeCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compPaisCircuito.areaAux = pintarTextoPainel(paisCircuitoString, (compPaisCircuito.area.x + 15), compPaisCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compTamanhoCircuito.areaAux =  pintarTextoPainel(tamanhoCircuitoString, (compTamanhoCircuito.area.x + 15), compTamanhoCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
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
				}else if(verificarCliqueDentroRetangulo(compPaisCircuito.area)){
					compAtualizar = pintarRetanguloPainel(150, 100, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_PAIS_CIRCUITO;
					checarEventoMenuEscolhePais(paisCircuitoString);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPaisCircuito.areaAux);
					compPaisCircuito.areaAux = pintarTextoPainel(paisCircuitoString, (compPaisCircuito.area.x + 15), compPaisCircuito.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
        }else if(verificarCliqueDentroRetangulo(compAlterar.area)){
					/* COMPLEMENTAR CIRCUITO */
					char msgRet[127];
					if(validaCamposBrancos(3, nomeCircuitoString, paisCircuitoString, tamanhoCircuitoString)){
						circuitoAlterar->tamanho = atoi(tamanhoCircuitoString);
						strcpy(circuitoAlterar->nome, nomeCircuitoString);
						strcpy(circuitoAlterar->pais, paisCircuitoString);
						if(alterarCircuito(*circuitoAlterar) == 0)
							sprintf(msgRet, "%s complementado com sucesso!", circuitoAlterar->nome);
						else
							sprintf(msgRet, "ERRO ao complementar %s!", circuitoAlterar->nome);
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
	                             "Complementar Circuito",
	                             msgRet,
	                             janelaDestino);
						sair = 1;
					}else
						ERRO_CAMPO_NULO(janelaDestino);
					break;
        }
			}
			if(manipularCampoTexto(&event, &compNomeCircuito, nomeCircuitoString, janelaDestino, 0, 32, 0))
				compAtualizar = compNomeCircuito;
			if(manipularCampoTexto(&event, &compTamanhoCircuito, tamanhoCircuitoString, janelaDestino, 0, 32, 0))
				compAtualizar = compTamanhoCircuito;
			atualizarPainel(painelDestino);
			SDL_FlushEvent(event.type);
		}
	}
  SDL_StopTextInput();
	
	return compClicado;
}



// Objetivo: Pinta todo o menu 'Pilotos' e espera o usuario escolher uma opcao
// Parametros: A janela e o painel onde sera pintado o Menu 'Pilotos'
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuMelhoresVoltas(Janela janelaDestino, Painel painelDestino){
//int pintarMenuPilotosEEsperaEscolherOpcao(Janela janela, Painel painelDestino){
	int sair = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	Componente compTitulo, compNovaMelhorVolta, compTabelaTodasMelhoresVotlas, compVoltar;
	Retangulo areaDadosListaMelhoresVoltas;
	MelhorVolta *todasMelhoresVoltas = NULL;
	
	inicializarComponente(&compNovaMelhorVolta, painelDestino);
	inicializarComponente(&compTabelaTodasMelhoresVotlas, painelDestino);
	
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
			compTitulo.area = pintarTextoPainel("MELHORES VOLTAS", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			
    	// Pinta as opcoes do menu		
			compNovaMelhorVolta.area = pintarTextoPainel("Nova Melhor Volta", 10, 40, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Pinta tabela que ficara todos os pilotos
			compTabelaTodasMelhoresVotlas = pintarTabelaPainel(10, 80, 540, 350, COR_TABELA, 6, 10, painelDestino);
			areaDadosListaMelhoresVoltas.x = compTabelaTodasMelhoresVotlas.area.x;
			areaDadosListaMelhoresVoltas.y = compTabelaTodasMelhoresVotlas.area.y + (compTabelaTodasMelhoresVotlas.area.h/10);
			areaDadosListaMelhoresVoltas.w = compTabelaTodasMelhoresVotlas.area.w;
			areaDadosListaMelhoresVoltas.h = compTabelaTodasMelhoresVotlas.area.h - (compTabelaTodasMelhoresVotlas.area.h/10);
			// Pinta o cabecalho da tabela
			pintarDadoTabela(compTabelaTodasMelhoresVotlas, 1, 1, "ID", janelaDestino);
			pintarDadoTabela(compTabelaTodasMelhoresVotlas, 1, 2, "PILOTO", janelaDestino);
			pintarDadoTabela(compTabelaTodasMelhoresVotlas, 1, 3, "CIRCUITO", janelaDestino);
			pintarDadoTabela(compTabelaTodasMelhoresVotlas, 1, 4, "EQUIPE", janelaDestino);
			pintarDadoTabela(compTabelaTodasMelhoresVotlas, 1, 5, "DATA", janelaDestino);
			pintarDadoTabela(compTabelaTodasMelhoresVotlas, 1, 6, "TEMPO", janelaDestino);
			// Pinta todos os pilotos
			int qtdMelhoresVoltas = pesquisarTodasMelhoresVoltas(&todasMelhoresVoltas);
			apresentarMelhoresVoltasPesquisadas(todasMelhoresVoltas, qtdMelhoresVoltas, compTabelaTodasMelhoresVotlas, janelaDestino);
			
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
				} else if(verificarCliqueDentroRetangulo(compNovaMelhorVolta.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_NOVA_MELHOR_VOLTA;
    			
    			// Vai para o menu 'Novo pilotos' e verifica seu retorno
					switch(checarEventoMenuNovaMelhorVolta(janelaDestino, painelDestino)){
					
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
				} else if(verificarCliqueDentroRetangulo(areaDadosListaMelhoresVoltas)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_TABELA_MELHORES_VOLTAS;
    			/*---------------------------------------------------------------------------------------------------------------------------------------
    			
    										 VERIFICAR QUANDO ALTERAR A PAGINACAO
    			
    			---------------------------------------------------------------------------------------------------------------------------------------*/
				int mouseY, mouseX;
				SDL_GetMouseState(&mouseX, &mouseY);
				int melhorVoltaEscolhida = (int)(((mouseY - areaDadosListaMelhoresVoltas.y))/(areaDadosListaMelhoresVoltas.h/9));
				checarEventoMenuDescricaoMelhorVolta(melhorVoltaEscolhida, janelaDestino, painelDestino, 1);
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
int checarEventoMenuNovaMelhorVolta(Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, campoAtivo = 0, pintarTexto = 0, idPiloto = -1, idCircuito = -1;
	ComponenteClicado compClicado;
	Componente compTitulo, compPilotoMelhorVolta, compCircuitoMelhorVolta, 
	compNomeEquiperMelhorVolta, compDataMelhorVolta, compTempoMelhorVolta, 
	compSair, compCadastrar, compVoltar, compAtualizar;
	char nomePilotoString[127], nomeCircuitoString[127], nomeEquipeString[127], dataString[11], tempoString[11];
	MelhorVolta melhorVoltaCadastrar;
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	inicializarComponente(&compPilotoMelhorVolta, painelDestino);
	inicializarComponente(&compCircuitoMelhorVolta, painelDestino);
	inicializarComponente(&compNomeEquiperMelhorVolta, painelDestino);
	inicializarComponente(&compDataMelhorVolta, painelDestino);
	inicializarComponente(&compTempoMelhorVolta, painelDestino);
	
	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(nomePilotoString, '\0', strlen(nomePilotoString));
	memset(nomeCircuitoString, '\0', strlen(nomeCircuitoString));
	memset(nomeEquipeString, '\0', strlen(nomeEquipeString));
	memset(dataString, '\0', strlen(dataString));
	memset(tempoString, '\0', strlen(tempoString));
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("NOVA MELHOR VOLTA", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	pintarTextoPainel("Piloto:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Circuito:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Equipe:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Data:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Tempo:", 10, 220, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compPilotoMelhorVolta = pintarRetanguloPainel(100, 60, 300, 30, COR_PRINCIPAL, painelDestino);
	compCircuitoMelhorVolta = pintarRetanguloPainel(100, 100, 300, 30, COR_PRINCIPAL, painelDestino);
	compNomeEquiperMelhorVolta = pintarRetanguloPainel(100, 140, 300, 30, COR_PRINCIPAL, painelDestino);
	compDataMelhorVolta = pintarRetanguloPainel(100, 180, 300, 30, COR_PRINCIPAL, painelDestino);
	compTempoMelhorVolta = pintarRetanguloPainel(100, 220, 300, 30, COR_PRINCIPAL, painelDestino);
	
	// Pinta o retangulo e depois o texto da opcao de cadastrar
	compCadastrar = pintarRetanguloPainel(230, 300, 93, 30, COR_PRINCIPAL, painelDestino);
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
				}else if(verificarCliqueDentroRetangulo(compPilotoMelhorVolta.area)){
					compAtualizar = pintarRetanguloPainel(compPilotoMelhorVolta.area.x, compPilotoMelhorVolta.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_PILOTO_MELHOR_VOLTA;
					checarEventoMenuEscolhePiloto(nomePilotoString, &idPiloto);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPilotoMelhorVolta.areaAux);
					compPilotoMelhorVolta.areaAux = pintarTextoPainel(nomePilotoString, compPilotoMelhorVolta.area.x + 15, compPilotoMelhorVolta.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				}else if(verificarCliqueDentroRetangulo(compCircuitoMelhorVolta.area)){
					compAtualizar = pintarRetanguloPainel(compCircuitoMelhorVolta.area.x, compCircuitoMelhorVolta.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_CIRCUITO_MELHOR_VOLTA;
					checarEventoMenuEscolheCircuito(nomeCircuitoString, &idCircuito);
					//strcpy(nomeCircuitoString, "Implementando...");
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compCircuitoMelhorVolta.areaAux);
					compCircuitoMelhorVolta.areaAux = pintarTextoPainel(nomeCircuitoString, compCircuitoMelhorVolta.area.x + 15, compCircuitoMelhorVolta.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				}else if(verificarCliqueDentroRetangulo(compCadastrar.area)){
					/* CADASTRAR MELHOR VOLTA */
					char msgRet[127];
					if(validaCamposBrancos(5, nomeCircuitoString, nomePilotoString, nomeEquipeString, dataString, tempoString)){
						melhorVoltaCadastrar.idCircuito = idCircuito;
						melhorVoltaCadastrar.idPiloto = idPiloto;
						strcpy(melhorVoltaCadastrar.nomeEquipe, nomeEquipeString);
						strcpy(melhorVoltaCadastrar.data, dataString);
						strcpy(melhorVoltaCadastrar.tempo, tempoString);
						if(salvarMelhorVolta(melhorVoltaCadastrar) == 0)
							strcpy(msgRet, "Melhor volta cadastrada com sucesso!");
						else
							strcpy(msgRet, "ERRO ao cadastrar melhor volta!");
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
	                             "Cadastrar Melhor volta",
	                             msgRet,
	                             janelaDestino);
						sair = 1;
					}else
						ERRO_CAMPO_NULO(janelaDestino);
					break;
        }
			}
		  if(manipularCampoTexto(&event, &compNomeEquiperMelhorVolta, nomeEquipeString, janelaDestino, 0, 32, 0))
				compAtualizar = compNomeEquiperMelhorVolta;
			if(manipularCampoTexto(&event, &compDataMelhorVolta, dataString, janelaDestino, 0, 11, 2))
				compAtualizar = compDataMelhorVolta;
			if(manipularCampoTexto(&event, &compTempoMelhorVolta, tempoString, janelaDestino, 0, 11, 3))
				compAtualizar = compTempoMelhorVolta;
			atualizarPainel(painelDestino);
			SDL_FlushEvent(event.type);
		}
	}
  SDL_StopTextInput();
	
	return compClicado;
}



// Objetivo:
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuEscolhePiloto(char *strDestinoNomePiloto, int *intDestinoIdPiloto){
	int ret = 0, sair = 0, atualizaPainel = 0, pilotoAtual = 0, qtdPilotos;
	ComponenteClicado compClicado;
	FILE *arquivoPilotos;
	Componente compTitulo, compPiloto, compTabelaTodosPilotos;
	Piloto pilotoEscolhido, *todosPilotos = NULL;
	Janela janelaPilotos;
	Painel painelPilotos;
	SDL_Event evento;
	Retangulo areaDadosListaPilotos;
	
	strcpy(strDestinoNomePiloto, "-");
	
	janelaPilotos = criarJanela("Lista de Pilotos", 300, 560);
	painelPilotos = criarPainel(janelaPilotos);
	
	compTitulo.area = pintarTextoPainel("Pilotos", 90, 10, FONTE_TITULO_PRINCIPAL, janelaPilotos);
	
	qtdPilotos = pesquisarTodosPilotos(&todosPilotos);
	
	if(qtdPilotos > 0){
		compTabelaTodosPilotos = pintarTabelaPainel(10, 80, 280, 350, COR_FUNDO, 2, qtdPilotos+1, painelPilotos);
		areaDadosListaPilotos.x = compTabelaTodosPilotos.area.x;
		areaDadosListaPilotos.y = compTabelaTodosPilotos.area.y + compTabelaTodosPilotos.areaAux.h;
		areaDadosListaPilotos.w = compTabelaTodosPilotos.area.w;
		areaDadosListaPilotos.h = compTabelaTodosPilotos.area.h - compTabelaTodosPilotos.areaAux.h;
		pintarDadoTabela(compTabelaTodosPilotos, 1, 1, "ID", janelaPilotos);
		pintarDadoTabela(compTabelaTodosPilotos, 1, 2, "NOME", janelaPilotos);
		apresentarPilotosPesquisados(todosPilotos, qtdPilotos, compTabelaTodosPilotos, janelaPilotos);
	
		atualizarPainel(painelPilotos);
		
		while(!sair){
			while(SDL_WaitEvent(&evento)){
				if(evento.type == SDL_QUIT){
					compClicado = CLICADO_FECHAR;
					sair = 1;
					break;
				}else if(evento.type == SDL_MOUSEBUTTONUP){
					if(verificarCliqueDentroRetangulo(compTabelaTodosPilotos.area)){
						int mouseY, mouseX;
						SDL_GetMouseState(&mouseX, &mouseY);
						int pilotoEscolhidoClique = (int)(((mouseY - areaDadosListaPilotos.y))/(areaDadosListaPilotos.h/qtdPilotos));
						if(pesquisarPilotoPId(todosPilotos[pilotoEscolhidoClique].id, &pilotoEscolhido) < 0){
							salvarErro("Erro ao pesquisar um piloto em 'checarEventoMenuEscolhePiloto'!\n");
							ret = 1;
						}
						sair = 1;
						break;
					}
				}
				atualizarPainel(painelPilotos);
				SDL_FlushEvent(evento.type);
			}
		}
		if(evento.type != SDL_QUIT && ret == 0){
			strcpy(strDestinoNomePiloto, pilotoEscolhido.nome);
			*intDestinoIdPiloto = pilotoEscolhido.id;
		}
	}
	
	SDL_DestroyWindow(janelaPilotos);
	
	return compClicado;
}



// Objetivo:
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuEscolheCircuito(char *strDestinoNomeCircuito, int *intDestinoIdCircuito){
	int sair = 0, atualizaPainel = 0, circuitoAtual = 0, ret = 0, qtdCircuitos;
	ComponenteClicado compClicado;
	FILE *arquivoCircuitos;
	Componente compTitulo, compCircuito, compTabelaTodosCircuitos;
	Circuito *todosCircuitos, circuitoEscolhido;
	Janela janelaCircuitos;
	Painel painelCircuitos;
	Retangulo areaDadosListaCircuitos;
	SDL_Event evento;
	
	strcpy(strDestinoNomeCircuito, "-");
	
	janelaCircuitos = criarJanela("Lista de Circuitos", 300, 560);
	painelCircuitos = criarPainel(janelaCircuitos);
	
	compTitulo.area = pintarTextoPainel("Circuitos", 90, 10, FONTE_TITULO_PRINCIPAL, janelaCircuitos);
	
	qtdCircuitos = pesquisarTodosCircuitos(&todosCircuitos);
	
	if(qtdCircuitos > 0){
		compTabelaTodosCircuitos = pintarTabelaPainel(10, 80, 280, 350, COR_FUNDO, 2, qtdCircuitos+1, painelCircuitos);
		areaDadosListaCircuitos.x = compTabelaTodosCircuitos.area.x;
		areaDadosListaCircuitos.y = compTabelaTodosCircuitos.area.y + compTabelaTodosCircuitos.areaAux.h;
		areaDadosListaCircuitos.w = compTabelaTodosCircuitos.area.w;
		areaDadosListaCircuitos.h = compTabelaTodosCircuitos.area.h - compTabelaTodosCircuitos.areaAux.h;
		pintarDadoTabela(compTabelaTodosCircuitos, 1, 1, "ID", janelaCircuitos);
		pintarDadoTabela(compTabelaTodosCircuitos, 1, 2, "NOME", janelaCircuitos);
		apresentarCircuitosPesquisados(todosCircuitos, qtdCircuitos, compTabelaTodosCircuitos, janelaCircuitos);
		
		atualizarPainel(painelCircuitos);
		
		while(!sair){
			while(SDL_WaitEvent(&evento)){
				if(evento.type == SDL_QUIT){
					compClicado = CLICADO_SAIR;
					sair = 1;
					break;
				}else if(evento.type == SDL_MOUSEBUTTONUP){
					if(verificarCliqueDentroRetangulo(compTabelaTodosCircuitos.area)){
						int mouseY, mouseX, circuitoEscolhidoClique;
						SDL_GetMouseState(&mouseX, &mouseY);
						circuitoEscolhidoClique = (int)(((mouseY - areaDadosListaCircuitos.y))/(areaDadosListaCircuitos.h/qtdCircuitos));
						if(pesquisarCircuitoPId(todosCircuitos[circuitoEscolhidoClique].codigo, &circuitoEscolhido) < 0){
							salvarErro("Erro ao pesquisar um circuito em 'checarEventoMenuEscolheCircuito'!\n");
							ret = 1;
						}
						sair = 1;
						break;
					}
				}
				atualizarPainel(painelCircuitos);
				SDL_FlushEvent(evento.type);
			}
		}
		if(evento.type != SDL_QUIT && ret == 0){
			strcpy(strDestinoNomeCircuito, circuitoEscolhido.nome);
			*intDestinoIdCircuito = circuitoEscolhido.codigo;
		}
	}
	
	SDL_DestroyWindow(janelaCircuitos);
	
	return compClicado;
}



// Objetivo:
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuDescricaoMelhorVolta(int idMelhorVolta, Janela janelaDestino, Painel painelDestino, int aparecerOpcoes){
	int ret = 0, sair = 0, atualizaPainel = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	FILE *arquivoMelhoresVoltas;
	Componente compTitulo, compVoltar, compAlterar, compExcluir;
	MelhorVolta melhorVoltaDescrever;
	char strIdMelhorVolta[12];
	Piloto pilotoApresentar;
	Circuito circuitoApresentar;
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS, "r");
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro ao abrir o arquivo das melhores voltas de 'checarEventoMenuDescricaoMelhorVolta'\n");
		ret = 1;
	}else{
		if(fseek(arquivoMelhoresVoltas, sizeof(MelhorVolta) * idMelhorVolta, SEEK_SET) != 0){
			salvarErro("Erro ao posicionaro arquivo de melhor volta em 'checarEventoMenuDescricaoMelhorVolta'!\n");
			ret = 1;
		}else{
			if(fread(&melhorVoltaDescrever, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				salvarErro("Erro ao ler uma melhor volta em 'checarEventoMenuDescricaoMelhorVolta'!\n");
				ret = 1;
			}
		}
		if(fclose(arquivoMelhoresVoltas) != 0){
			salvarErro("Erro ao fechar o arquivo de melhores voltas em 'checarEventoMenuDescricaoMelhorVolta'!\n");
			ret = 1;
		}
	}
	
	if(ret == 0){
		sprintf(strIdMelhorVolta, "%d", melhorVoltaDescrever.id);
		if(pesquisarPilotoPId(melhorVoltaDescrever.idPiloto, &pilotoApresentar) < 0){
			salvarErro("Erro ao pesquisar um piloto de melhores voltas em 'checarEventoMenuDescricaoMelhorVolta'!\n");
			ret = 1;
		}else{
			if(pesquisarCircuitoPId(melhorVoltaDescrever.idCircuito, &circuitoApresentar) < 0){
				salvarErro("Erro ao pesquisar um circuito de melhores voltas em 'checarEventoMenuDescricaoMelhorVolta'!\n");
				ret = 1;
			}else{
				SDL_Event evento;
				while(!sair){
					if(pintaMenu){
						pintaMenu = 0;
						limparPainel(painelDestino);
						compTitulo.area = pintarTextoPainel("Melhor Volta", 90, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
						pintarTextoPainel("ID:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel("PILOTO:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel("CIRCUITO:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel("EQUIPE:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel("DATA:", 10, 220, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel("TEMPO:", 10, 260, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel(strIdMelhorVolta, 120, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel(pilotoApresentar.nome, 120, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel(circuitoApresentar.nome, 120, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel(melhorVoltaDescrever.nomeEquipe, 120, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel(melhorVoltaDescrever.data, 120, 220, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						pintarTextoPainel(melhorVoltaDescrever.tempo, 120, 260, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						if(aparecerOpcoes){
							compAlterar.area = pintarTextoPainel("Alterar", 90, 305, FONTE_TEXTO_PRINCIPAL, janelaDestino);
							compExcluir.area = pintarTextoPainel("Excluir", 210, 305, FONTE_TEXTO_PRINCIPAL, janelaDestino);
							pintarRetanguloPainel(80, 300, compAlterar.area.w + 20, 30, COR_PRINCIPAL, painelDestino);
							pintarRetanguloPainel(200, 300, compExcluir.area.w + 20, 30, COR_PRINCIPAL, painelDestino);
						}
						compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
						
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
					  			compClicado = CLICADO_ALTERA_MELHOR_VOLTA;
								
									checarEventoMenuAlteraMelhorVolta(&melhorVoltaDescrever, janelaDestino, painelDestino);
									sprintf(strIdMelhorVolta, "%d", melhorVoltaDescrever.id);
									//pesquisarPilotoPId(melhorVoltaDescrever.idPiloto, &pilotoApresentar);
									//pesquisarCircuitoPId(melhorVoltaDescrever.idCircuito, &circuitoApresentar);
									pintaMenu = 1;
				    	    // Sair do loop de verificar um evento
					  			break;
								} else if(verificarCliqueDentroRetangulo(compExcluir.area)){
				    			
				    		  // Define o componente que foi clicado
					  			compClicado = CLICADO_EXCLUI_MELHOR_VOLTA;
								
								char msgRet[127];
								if(excluirMelhorVolta(melhorVoltaDescrever) == 0)
									strcpy(msgRet, "Melhor volta excluida com sucesso!");
								else
									strcpy(msgRet, "ERRO ao excluir melhor volta!");
								SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			                             "Excluir Melhor volta",
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
			}
		}
	}else{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Descrever Melhor volta", "Erro ao descrever Melhor volta", janelaDestino);
	}
	
	return compClicado;
}



// Objetivo: Pinta todo o menu 'Pilotos' e espera o usuario escolher uma opcao
// Parametros: A janela e o painel onde sera pintado o Menu 'Pilotos'
// Retorno: O numero do componente que foi clicado, de acordo com a 'enum ComponenteClicado'
int checarEventoMenuAlteraMelhorVolta(MelhorVolta *melhorVoltaAlterar, Janela janelaDestino, Painel painelDestino){
	int ret = 0, sair = 0, campoAtivo = 0, pintarTexto = 0, idPiloto = -1, idCircuito = -1;
	ComponenteClicado compClicado;
	Componente compTitulo, compPilotoMelhorVolta, compCircuitoMelhorVolta, 
	compNomeEquiperMelhorVolta, compDataMelhorVolta, compTempoMelhorVolta, 
	compSair, compAlterar, compVoltar, compAtualizar, compExcluir;
	char nomePilotoString[127], nomeCircuitoString[127], nomeEquipeString[127], dataString[11], tempoString[11];
	Piloto pilotoMelhorVolta;
	Circuito circuitoMelhorVolta;
	
	// Define que nao precisa atualizar nenhum componente
	compAtualizar.painelPertencente = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	inicializarComponente(&compPilotoMelhorVolta, painelDestino);
	inicializarComponente(&compCircuitoMelhorVolta, painelDestino);
	inicializarComponente(&compNomeEquiperMelhorVolta, painelDestino);
	inicializarComponente(&compDataMelhorVolta, painelDestino);
	inicializarComponente(&compTempoMelhorVolta, painelDestino);

	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(nomePilotoString, '\0', strlen(nomePilotoString));
	memset(nomeCircuitoString, '\0', strlen(nomeCircuitoString));
	memset(nomeEquipeString, '\0', strlen(nomeEquipeString));
	memset(dataString, '\0', strlen(dataString));
	memset(tempoString, '\0', strlen(tempoString));
	
	strcpy(nomeEquipeString, melhorVoltaAlterar->nomeEquipe);
	strcpy(dataString, melhorVoltaAlterar->data);
	strcpy(tempoString, melhorVoltaAlterar->tempo);
	idPiloto = melhorVoltaAlterar->idPiloto;
	idCircuito = melhorVoltaAlterar->idCircuito;
	pesquisarPilotoPId(idPiloto, &pilotoMelhorVolta);
	pesquisarCircuitoPId(idCircuito, &circuitoMelhorVolta);
	strcpy(nomePilotoString, pilotoMelhorVolta.nome);
	strcpy(nomeCircuitoString, circuitoMelhorVolta.nome);
	
	// Limpa tudo o que estava pintado no painel
	limparPainel(painelDestino);
	
	// Pinta o titulo
	compTitulo.area = pintarTextoPainel("COMPLEMENTAR MELHOR VOLTA", 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
	
	// Pinta o nome dos campos
	pintarTextoPainel("Piloto:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Circuito:", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Equipe:", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Data:", 10, 180, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	pintarTextoPainel("Tempo:", 10, 220, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta opcao de voltar
	compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	
	// Pinta o retangulo dos campos de texto
	compPilotoMelhorVolta = pintarRetanguloPainel(100, 60, 300, 30, COR_PRINCIPAL, painelDestino);
	compCircuitoMelhorVolta = pintarRetanguloPainel(100, 100, 300, 30, COR_PRINCIPAL, painelDestino);
	compNomeEquiperMelhorVolta = pintarRetanguloPainel(100, 140, 300, 30, COR_PRINCIPAL, painelDestino);
	compDataMelhorVolta = pintarRetanguloPainel(100, 180, 300, 30, COR_PRINCIPAL, painelDestino);
	compTempoMelhorVolta = pintarRetanguloPainel(100, 220, 300, 30, COR_PRINCIPAL, painelDestino);
	
	// Pinta as letras das opcoes de sexo
	compPilotoMelhorVolta.areaAux = pintarTextoPainel(pilotoMelhorVolta.nome, compPilotoMelhorVolta.area.x + 15, compPilotoMelhorVolta.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compCircuitoMelhorVolta.areaAux = pintarTextoPainel(circuitoMelhorVolta.nome, compCircuitoMelhorVolta.area.x + 15, compCircuitoMelhorVolta.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compNomeEquiperMelhorVolta.areaAux = pintarTextoPainel(nomeEquipeString, compNomeEquiperMelhorVolta.area.x + 15, compNomeEquiperMelhorVolta.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compDataMelhorVolta.areaAux = pintarTextoPainel(dataString, compDataMelhorVolta.area.x + 15, compDataMelhorVolta.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
	compTempoMelhorVolta.areaAux = pintarTextoPainel(tempoString, compTempoMelhorVolta.area.x + 15, compTempoMelhorVolta.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				
	
	// Pinta o retangulo e depois o texto da opcao de cadastrar
	compAlterar = pintarRetanguloPainel(230, 300, 74, 30, COR_PRINCIPAL, painelDestino);
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
				}else if(verificarCliqueDentroRetangulo(compPilotoMelhorVolta.area)){
					compAtualizar = pintarRetanguloPainel(100, compPilotoMelhorVolta.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_PILOTO_MELHOR_VOLTA;
					checarEventoMenuEscolhePiloto(nomePilotoString, &idPiloto);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compPilotoMelhorVolta.areaAux);
					compPilotoMelhorVolta.areaAux = pintarTextoPainel(nomePilotoString, compPilotoMelhorVolta.area.x + 15, compPilotoMelhorVolta.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				}else if(verificarCliqueDentroRetangulo(compCircuitoMelhorVolta.area)){
					compAtualizar = pintarRetanguloPainel(100, compCircuitoMelhorVolta.area.y, 300, 30, COR_SELECIONADO, painelDestino);
					compClicado = CLICADO_CIRCUITO_MELHOR_VOLTA;
					checarEventoMenuEscolheCircuito(nomeCircuitoString, &idCircuito);
					SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
					SDL_RenderFillRect(painelDestino, &compCircuitoMelhorVolta.areaAux);
					compCircuitoMelhorVolta.areaAux = pintarTextoPainel(nomeCircuitoString, compCircuitoMelhorVolta.area.x + 15, compCircuitoMelhorVolta.area.y+5, FONTE_TEXTO_PRINCIPAL, janelaDestino);
				}else if(verificarCliqueDentroRetangulo(compAlterar.area)){
					/* COMPLEMENTAR MELHOR VOLTA */
					char msgRet[127];
					if(validaCamposBrancos(5, nomePilotoString, nomeCircuitoString, nomeEquipeString, dataString, tempoString)){
						melhorVoltaAlterar->idCircuito = idCircuito;
						melhorVoltaAlterar->idPiloto = idPiloto;
						strcpy(melhorVoltaAlterar->nomeEquipe, nomeEquipeString);
						strcpy(melhorVoltaAlterar->data, dataString);
						strcpy(melhorVoltaAlterar->tempo, tempoString);
						if(alterarMelhorVolta(*melhorVoltaAlterar) == 0)
							strcpy(msgRet, "Melhor volta alterada com sucesso!");
						else
							strcpy(msgRet, "ERRO ao complementar Melhor volta!");
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
	                             "Complementar Melhor volta",
	                             msgRet,
	                             janelaDestino);
						sair = 1;
					}else
						ERRO_CAMPO_NULO(janelaDestino);
					break;
        }
			}
			if(manipularCampoTexto(&event, &compNomeEquiperMelhorVolta, nomeEquipeString, janelaDestino, 0, 32, 0))
				compAtualizar = compNomeEquiperMelhorVolta;
			if(manipularCampoTexto(&event, &compDataMelhorVolta, dataString, janelaDestino, 0, 32, 0))
				compAtualizar = compDataMelhorVolta;
			if(manipularCampoTexto(&event, &compTempoMelhorVolta, tempoString, janelaDestino, 0, 32, 0))
				compAtualizar = compTempoMelhorVolta;
			atualizarPainel(painelDestino);
			SDL_FlushEvent(event.type);
		}
	}
  SDL_StopTextInput();
	
	return compClicado;
}



// Objetivo: 
int checarEventoMenuRelatorios(Janela janelaDestino, Painel painelDestino){
//int pintarMenuPrincipalEEsperaEscolherOpcao(Janela janela, Painel painelDestino){
	int sair = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	Componente compTitulo, compR1, compR2, compR3, compR4, compR5, compR6, 
	compVoltar;	
	
	// Cria a estrutura 'SDL_Event' para guardar todos evento que ocorrem
	SDL_Event evento;
	
	// Loop para nao fechar a janela
	while(!sair){
	
	  // Verifica se e preciso pintar todo o menu
	  if(pintaMenu){
	  	pintaMenu = 0;
	  	
			// Limpa todo o painel
			limparPainel(painelDestino);
			
			// Pintar o titulo
			compTitulo.area = pintarTextoPainel("RELATORIOS", 180, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			
			// Pinta as opcoes do menu
			compR1.area = pintarTextoPainel("R1 - Consultar Dados", 10, 40, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compR2.area = pintarTextoPainel("R2 - Pesquisar Piloto por nome", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compR3.area = pintarTextoPainel("R3 - Pesquisar Piloto por Circuito", 10, 80, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compR4.area = pintarTextoPainel("R4 - Pesquisar Circuito", 10, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compR5.area = pintarTextoPainel("R5 - Pesquisar Piloto em um intervalo de datas", 10, 120, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compR6.area = pintarTextoPainel("R6 - Pesquisar por tempo de Melhor volta", 10, 140, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Atualizar o painel, para aparecer tudo que foi pintado 
			atualizarPainel(painelDestino);
		}
		
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
    		if(verificarCliqueDentroRetangulo(compVoltar.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_VOLTAR;
    			
    			// Define que e para cancelar o loop da janela
    			sair = 1;
    			
    			// Sair do loop de verificar um evento
    			break;
    			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'Pilotos'
				} else if(verificarCliqueDentroRetangulo(compR1.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_RELATORIO_1;
    				
					switch(checarEventoMenuRelatorio1(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compR2.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_RELATORIO_2;
    			
					switch(checarEventoMenuRelatorio2(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compR3.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_RELATORIO_3;
    			/*
					switch(checarEventoMenuMelhoresVoltas(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}*/INFO_IMPLEMENTANDO(janelaDestino);
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compR4.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_RELATORIO_4;
    			/*
					switch(checarEventoMenuMelhoresVoltas(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}*/INFO_IMPLEMENTANDO(janelaDestino);
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compR5.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_RELATORIO_5;
    			/*
					switch(checarEventoMenuMelhoresVoltas(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}*/INFO_IMPLEMENTANDO(janelaDestino);
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compR6.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_RELATORIO_6;
    			/*
					switch(checarEventoMenuMelhoresVoltas(janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}*/INFO_IMPLEMENTANDO(janelaDestino);
    			
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
int checarEventoMenuRelatorio1(Janela janelaDestino, Painel painelDestino){
//int pintarMenuPrincipalEEsperaEscolherOpcao(Janela janela, Painel painelDestino){
	int sair = 0, pintaMenu = 1;
	ComponenteClicado compClicado;
	Componente compTitulo, compPilotos, compCircuitos, compMelhoresVoltas, 
	compVoltar;
	
	
	// Cria a estrutura 'SDL_Event' para guardar todos evento que ocorrem
	SDL_Event evento;
	
	// Loop para nao fechar a janela
	while(!sair){
	
	  // Verifica se e preciso pintar todo o menu
	  if(pintaMenu){
	  	pintaMenu = 0;
	  	
			// Limpa todo o painel
			limparPainel(painelDestino);
			
			// Pintar o titulo
			compTitulo.area = pintarTextoPainel("RELATORIO 1", 180, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			
			// Pinta as opcoes do menu
			compPilotos.area = pintarTextoPainel("Pilotos", 10, 40, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compCircuitos.area = pintarTextoPainel("Circuitos", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compMelhoresVoltas.area = pintarTextoPainel("Melhores Voltas", 10, 80, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Atualizar o painel, para aparecer tudo que foi pintado 
			atualizarPainel(painelDestino);
		}
		
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
    		if(verificarCliqueDentroRetangulo(compVoltar.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_VOLTAR;
    			
    			// Define que e para cancelar o loop da janela
    			sair = 1;
    			
    			// Sair do loop de verificar um evento
    			break;
    			
			  // Verifica se no clique do mouse, o mouse estava dentro do retangulo de 'Pilotos'
				} else if(verificarCliqueDentroRetangulo(compPilotos.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_PILOTOS;
    			
					switch(checarEventoMenuRelatorio1Consulta(0, janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compCircuitos.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_CIRCUITOS;
    			
					switch(checarEventoMenuRelatorio1Consulta(1, janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
							break;
					}
    			
    			// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compMelhoresVoltas.area)){
    		
    		  // Define o componente que foi clicado
    			compClicado = CLICADO_MELHORES_VOLTAS;
    			
					switch(checarEventoMenuRelatorio1Consulta(2, janelaDestino, painelDestino)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			compClicado = CLICADO_FECHAR;
		    			break;
						case CLICADO_VOLTAR:
							pintaMenu = 1;
		    			sair = 1;
		    			compClicado = CLICADO_VOLTAR;
							break;
					}
    		 
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
int checarEventoMenuRelatorio1Consulta(int tipoRelatorio, Janela janelaDestino, Painel painelDestino){
	int sair = 0, campoAtivo = 0, pintarTexto = 1;
	ComponenteClicado compClicado;
	Componente compTitulo, compCampoPesquisa, compTabelaResultado, 
	compPesquisar, compTodos, compVoltar, compAtualizar;
	char pesquisaString[127], tituloString[28];
	Piloto pilotoPesquisado, *pilotosEncontrados = NULL;
	Circuito circuitoPesquisado, *circuitosEncontrados = NULL;
	MelhorVolta melhorVoltaPesquisada, *melhoresVoltasEncontradas = NULL;
	Retangulo areaDadosTabela;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	inicializarComponente(&compCampoPesquisa, painelDestino);
	areaDadosTabela.x = 0;
	areaDadosTabela.y = 0;
	areaDadosTabela.w = 0;
	areaDadosTabela.h = 0;

	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(pesquisaString, '\0', strlen(pesquisaString));
	strcpy(tituloString, "Relatorio 1 ");
	
	if(tipoRelatorio == 0) strcat(tituloString, "Pilotos");
	else if(tipoRelatorio == 1) strcat(tituloString, "Circuitos");
	else strcat(tituloString, "Melhores Voltas");
	
	SDL_Event event;
	SDL_StartTextInput();
	while(!sair){
		if(pintarTexto){
			pintarTexto = 0;
			
			// Limpa tudo o que estava pintado no painel
			limparPainel(painelDestino);
			
			// Pinta o titulo
			compTitulo.area = pintarTextoPainel(tituloString, 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			
			// Pinta o nome dos campos
			pintarTextoPainel("Chave Única:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Pinta opcao de voltar
			compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Pinta o retangulo dos campos de texto
			compCampoPesquisa = pintarRetanguloPainel(120, 60, 150, 30, COR_PRINCIPAL, painelDestino);
			
			// Pinta o retangulo e depois o texto da opcao de cadastrar
			compPesquisar = pintarRetanguloPainel(290, 60, 91, 30, COR_PRINCIPAL, painelDestino);
			pintarTextoPainel("Pesquisar", (compPesquisar.area.x + 10), (compPesquisar.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			compTodos = pintarRetanguloPainel(400, 60, 153, 30, COR_PRINCIPAL, painelDestino);
			pintarTextoPainel("Apresentar Todos", (compTodos.area.x + 10), (compTodos.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			
			// Atualizar o painel, para aparecer tudo que foi pintado
			atualizarPainel(painelDestino);
		}
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
				}else if(verificarCliqueDentroRetangulo(compPesquisar.area)){
					/* CONSULTAR */
					char msgRet[127];
					int idPesquisar, retPesquisa = -1;

					idPesquisar = atoi(pesquisaString);
					if(tipoRelatorio == 0){
						pilotosEncontrados = (Piloto *)(malloc(1 * sizeof(Piloto)));
						if(pesquisarPilotoPId(idPesquisar, pilotosEncontrados) > 0){
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
		                             tituloString,
		                             "Encontrado um Piloto!",
		                             janelaDestino);
							SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
							SDL_RenderFillRect(painelDestino, &((SDL_Rect){9, 99, 541, 331}));
							compTabelaResultado = pintarTabelaPainel(10, 100, 540, 330, COR_TABELA, 5, 10, painelDestino);
							areaDadosTabela.x = compTabelaResultado.area.x;
							areaDadosTabela.y = compTabelaResultado.area.y + (compTabelaResultado.area.h/10);
							areaDadosTabela.w = compTabelaResultado.area.w;
							areaDadosTabela.h = compTabelaResultado.area.h - (compTabelaResultado.area.h/10);
			
							pintarDadoTabela(compTabelaResultado, 1, 1, "ID", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 2, "NOME", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 3, "IDADE", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 4, "SEXO", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 5, "PAIS", janelaDestino);
							
							apresentarPilotosPesquisados(pilotosEncontrados, 1, compTabelaResultado, janelaDestino);
						} else
							pintarTextoPainel("Não encontrado nenhum Piloto!", 200, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					}	else if(tipoRelatorio == 2){
						circuitosEncontrados = (Circuito *)(malloc(1 * sizeof(Circuito)));
						pesquisarCircuitoPId(idPesquisar, circuitosEncontrados);
						if(circuitoPesquisado.codigo != -1){
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
		                             tituloString,
		                             "Encontrado um Circuito!",
		                             janelaDestino);
							SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
							SDL_RenderFillRect(painelDestino, &((SDL_Rect){9, 99, 541, 331}));
							compTabelaResultado = pintarTabelaPainel(10, 100, 540, 330, COR_TABELA, 6, 10, painelDestino);
							pintarDadoTabela(compTabelaResultado, 1, 1, "ID", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 2, "NOME", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 3, "PAIS", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 4, "EXTENSAO", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 5, "MENOR TEMPO", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 6, "PILOTO", janelaDestino);
							apresentarPilotosPesquisados(&pilotoPesquisado, 1, compTabelaResultado, janelaDestino);
						} else
							pintarTextoPainel("Não encontrado nenhum Circuito!", 200, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					}	else {
						melhoresVoltasEncontradas = (MelhorVolta * )(malloc(1 * sizeof(MelhorVolta)));
						*melhoresVoltasEncontradas = pesquisarMelhorVolta(idPesquisar);
						if(melhorVoltaPesquisada.id != -1){
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
		                             tituloString,
		                             "Encontrada uma Melhor Volta!",
		                             janelaDestino);
							SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
							SDL_RenderFillRect(painelDestino, &((SDL_Rect){9, 99, 541, 331}));
							compTabelaResultado = pintarTabelaPainel(10, 100, 540, 330, COR_TABELA, 6, 10, painelDestino);
							pintarDadoTabela(compTabelaResultado, 1, 1, "ID", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 2, "PILOTO", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 3, "CIRCUITO", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 4, "EQUIPE", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 5, "DATA", janelaDestino);
							pintarDadoTabela(compTabelaResultado, 1, 5, "TEMPO", janelaDestino);
							apresentarPilotosPesquisados(&pilotoPesquisado, 1, compTabelaResultado, janelaDestino);
						} else
							pintarTextoPainel("Não encontrada nenhuma Melhor Volta!", 200, 100, FONTE_TEXTO_PRINCIPAL, janelaDestino);
					}
				//sair = 1;
				//pintarTexto = 1;
				break;
        } else if(verificarCliqueDentroRetangulo(areaDadosTabela)){
        	
    			/*---------------------------------------------------------------------------------------------------------------------------------------
    			
    										 VERIFICAR QUANDO ALTERAR A PAGINACAO
    			
    			---------------------------------------------------------------------------------------------------------------------------------------*/
				int mouseY, mouseX;
				SDL_GetMouseState(&mouseX, &mouseY);
				int dadoEscolhido = (int)(((mouseY - areaDadosTabela.y))/(areaDadosTabela.h/9));
        	if(tipoRelatorio == 0)
						checarEventoMenuDescricaoPiloto((pilotosEncontrados + dadoEscolhido)->id, janelaDestino, painelDestino, 0);
	    		else if(tipoRelatorio == 1)
						checarEventoMenuDescricaoCircuito((circuitosEncontrados + dadoEscolhido)->codigo, janelaDestino, painelDestino, 0);
	    		else
	    			checarEventoMenuDescricaoMelhorVolta((melhoresVoltasEncontradas + dadoEscolhido)->id, janelaDestino, painelDestino, 0);
					
					// Sair do loop de verificar um evento
    			break;
				} else if(verificarCliqueDentroRetangulo(compTodos.area)){
        	if(tipoRelatorio == 0){
        		int qtdPilotos = pesquisarTodosPilotos(&pilotosEncontrados);
						SDL_SetRenderDrawColor(painelDestino, 255, 255, 255, 255);
						SDL_RenderFillRect(painelDestino, &((SDL_Rect){9, 99, 541, 331}));
						compTabelaResultado = pintarTabelaPainel(10, 100, 540, 330, COR_TABELA, 5, 10, painelDestino);
						areaDadosTabela.x = compTabelaResultado.area.x;
						areaDadosTabela.y = compTabelaResultado.area.y + (compTabelaResultado.area.h/10);
						areaDadosTabela.w = compTabelaResultado.area.w;
						areaDadosTabela.h = compTabelaResultado.area.h - (compTabelaResultado.area.h/10);
						
						pintarDadoTabela(compTabelaResultado, 1, 1, "ID", janelaDestino);
						pintarDadoTabela(compTabelaResultado, 1, 2, "NOME", janelaDestino);
						pintarDadoTabela(compTabelaResultado, 1, 3, "IDADE", janelaDestino);
						pintarDadoTabela(compTabelaResultado, 1, 4, "SEXO", janelaDestino);
						pintarDadoTabela(compTabelaResultado, 1, 5, "PAIS", janelaDestino);
						
						apresentarPilotosPesquisados(pilotosEncontrados, qtdPilotos, compTabelaResultado, janelaDestino);
					}/*else if(tipoRelatorio == 1)
						checarEventoMenuDescricaoCircuito((circuitosEncontrados + dadoEscolhido)->codigo, janelaDestino, painelDestino);
    			else
    				checarEventoMenuDescricaoMelhorVolta((melhoresVoltasEncontradas + dadoEscolhido)->id, janelaDestino, painelDestino);
					// Define que e para repintar o menu 'Pilotos'
					//pintaMenu = 1;*/
					
					// Sair do loop de verificar um evento
    			break;
				}
			}
			if(manipularCampoTexto(&event, &compCampoPesquisa, pesquisaString, janelaDestino, 0, 9, 1))
				compAtualizar = compCampoPesquisa;
			atualizarPainel(painelDestino);
			SDL_FlushEvent(event.type);
		}
	}
  SDL_StopTextInput();
	/*
	if(pintarTexto){
		if(tipoRelatorio == 0)
			checarEventoMenuDescricaoPiloto(pilotoPesquisado.id, janelaDestino, painelDestino);
		else if(tipoRelatorio == 1)
			checarEventoMenuDescricaoCircuito(circuitoPesquisado.codigo, janelaDestino, painelDestino);
		else if(tipoRelatorio == 2)
			checarEventoMenuDescricaoMelhorVolta(melhorVoltaPesquisada.id, janelaDestino, painelDestino);
		compClicado = CLICADO_VOLTAR;
	}*/
	
	return compClicado;
}



// Objetivo: 
int checarEventoMenuRelatorio2(Janela janelaDestino, Painel painelDestino){
	int sair = 0, campoAtivo = 0, pintarTexto = 1, qtdPilotosEncontrados = 0;
	ComponenteClicado compClicado;
	Componente compTitulo, compCampoPesquisa, compTabelaResultado, compPesquisar, 
	compVoltar, compAtualizar;
	char pesquisaString[127], tituloString[12];
	Piloto *pilotosPesquisados = NULL;
	
	// Define que a largura e altura utilizadas pelas strings de nome e pais natal do piloto sao 0 (zero)
	inicializarComponente(&compCampoPesquisa, painelDestino);

	// Limpa a memoria utilizada pelo nome, idade e pais natal do piloto
	memset(pesquisaString, '\0', strlen(pesquisaString));
	memset(tituloString, '\0', strlen(tituloString));
	strcpy(tituloString, "Relatorio 2");
	
	SDL_Event event;
	SDL_StartTextInput();
	while(!sair){
		if(pintarTexto){
			pintarTexto = 0;
			
			// Limpa tudo o que estava pintado no painel
			limparPainel(painelDestino);
			
			// Pinta o titulo
			compTitulo.area = pintarTextoPainel(tituloString, 200, 10, FONTE_TITULO_PRINCIPAL, janelaDestino);
			
			// Pinta o nome dos campos
			pintarTextoPainel("Nome:", 10, 60, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Pinta opcao de voltar
			compVoltar.area = pintarTextoPainel("Voltar", 10, 460, FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Pinta o retangulo dos campos de texto
			compCampoPesquisa = pintarRetanguloPainel(120, 60, 300, 30, COR_PRINCIPAL, painelDestino);
			
			compTabelaResultado = pintarTabelaPainel(10, 110, 540, 330, COR_TABELA, 5, 10, painelDestino);
			/*areaDadosListaPilotos.x = compTabelaTodosPilotos.area.x;
			areaDadosListaPilotos.y = compTabelaTodosPilotos.area.y + (compTabelaTodosPilotos.area.h/10);
			areaDadosListaPilotos.w = compTabelaTodosPilotos.area.w;
			areaDadosListaPilotos.h = compTabelaTodosPilotos.area.h - (compTabelaTodosPilotos.area.h/10);*/
			// Pinta o cabecalho da tabela
			pintarDadoTabela(compTabelaResultado, 1, 1, "ID", janelaDestino);
			pintarDadoTabela(compTabelaResultado, 1, 2, "NOME", janelaDestino);
			pintarDadoTabela(compTabelaResultado, 1, 3, "IDADE", janelaDestino);
			pintarDadoTabela(compTabelaResultado, 1, 4, "SEXO", janelaDestino);
			pintarDadoTabela(compTabelaResultado, 1, 5, "PAIS", janelaDestino);
			apresentarPilotosPesquisados(pilotosPesquisados, qtdPilotosEncontrados, compTabelaResultado, janelaDestino);
			
			// Pinta o retangulo e depois o texto da opcao de cadastrar
			compPesquisar = pintarRetanguloPainel(440, 60, 91, 30, COR_PRINCIPAL, painelDestino);
			pintarTextoPainel("Pesquisar", (compPesquisar.area.x + 10), (compPesquisar.area.y+5), FONTE_TEXTO_PRINCIPAL, janelaDestino);
			
			// Atualizar o painel, para aparecer tudo que foi pintado
			atualizarPainel(painelDestino);
		}
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
				}else if(verificarCliqueDentroRetangulo(compPesquisar.area)){
					/* CONSULTAR */
					char msgRet[127];

					qtdPilotosEncontrados = pesquisarPilotoPNome(pesquisaString, &pilotosPesquisados);
			    qsort(pilotosPesquisados, qtdPilotosEncontrados, sizeof(Piloto), ordenarPilotoNome);
			    
					if(qtdPilotosEncontrados > 0){
						sprintf(msgRet, "Encontrado(s) %d Piloto(s)!", qtdPilotosEncontrados);
					} else {
						strcpy(msgRet, "Não encontrado nenhum Piloto!");
					}
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
			                            	tituloString,
			                            	msgRet,
			                            	janelaDestino);
				//sair = 1;
				pintarTexto = 1;
				break;
        }
			}
			if(manipularCampoTexto(&event, &compCampoPesquisa, pesquisaString, janelaDestino, 0, 32, 0))
				compAtualizar = compCampoPesquisa;
			atualizarPainel(painelDestino);
			SDL_FlushEvent(event.type);
		}
	}
  SDL_StopTextInput();
	
	/*if(pintarTexto){
		if(tipoRelatorio == 0){
			checarEventoMenuDescricaoPiloto(pilotoPesquisado.id, janelaDestino, painelDestino);
			compClicado = CLICADO_VOLTAR;
		} else if(tipoRelatorio == 1){
			checarEventoMenuDescricaoCircuito(circuitoPesquisado.codigo, janelaDestino, painelDestino);
			compClicado = CLICADO_VOLTAR;
		}	else if(tipoRelatorio == 2){
			checarEventoMenuDescricaoMelhorVolta(melhorVoltaPesquisada.id, janelaDestino, painelDestino);
			compClicado = CLICADO_VOLTAR;
		}
	}*/
	
	return compClicado;
}


#endif /* _FUNCOES_MENU_C_ */
