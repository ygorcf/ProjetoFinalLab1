// Aluno: Ygor Cruz e Gustavo Arthur

/*
  Objetivo: Gerenciar os testes realizados na Formula 1

  Entrada:

  Saida:
*/

#include <stdio.h>
#include <conio.c>

#include <includesProjeto.h>

int main(int argc, char* args[]){
	inicializarTudo();

	Janela janelaPrincipal;
	Painel painelPrincipal;
	int sair = 0;
	
	janelaPrincipal = criarJanela("Projeto Final - Formula 1", 560, 480);
	painelPrincipal = criarPainel(janelaPrincipal);
	
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_EventState(SDL_KEYUP, SDL_IGNORE);
	SDL_EventState(SDL_TEXTEDITING, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
	checarEventoMenuPrincipal(janelaPrincipal, painelPrincipal);

	finalizarTudo();
	return 0;
}
