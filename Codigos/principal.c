// Aluno: Ygor Cruz e Gustavo Arthur

/*
  Objetivo: Gerenciar os testes realizados na Formula 1
  
  Entrada:
  
  Saida:
*/

#include <stdio.h>
#include <conio.c>

#include "includesProjeto.h"

int main(int argc, char* args[]){
	inicializarTudo();
	
	SDL_Surface* super =  SDL_CreateRGBSurfaceFrom("Texto",
                                      40,
                                      10,
                                      32,
                                      32,
                                      0,
                                      0,
                                      0,
                                      0);
	Janela janelaPrincipal;
	Painel painelPrincipal;
	int sair = 0;
	
	janelaPrincipal = criarJanela("Projeto Final - Formula 1", 560, 480);
	painelPrincipal = criarPainel(janelaPrincipal);
	
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_KEYUP);
	SDL_EventState(SDL_MOUSEMOTION, SDL_TEXTEDITING);
    while(!sair){
    	switch(checarEventoMenuPrincipal(janelaPrincipal, painelPrincipal)){
    		case CLICADO_SAIR:
    			sair = 1;
    			break;
    		case CLICADO_FECHAR:
    			sair = 1;
    			break;
    		case CLICADO_PILOTOS:
					switch(checarEventoMenuPilotos(janelaPrincipal, painelPrincipal)){
	    			case CLICADO_FECHAR:
		    			sair = 1;
		    			break;
						case CLICADO_NOVO_PILOTO:
							switch(checarEventoMenuNovoPiloto(janelaPrincipal, painelPrincipal)){
				    		case CLICADO_FECHAR:
				    			sair = 1;
				    			break;
								default:
									sair = 0;
							}
							break;
					}
    			break;
    		default :
    			sair = 0;
			}
    	atualizarPainel(painelPrincipal);
    }

	finalizarTudo();
	return 0;
}
