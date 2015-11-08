#ifndef _FUNCOES_ERRO_C_
#define _FUNCOES_ERRO_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define LOCAL_ARQUIVO_ERROS "Erros/errosProjeto.txt"



// Objetivo: Salvar no arquivo de erros, uma string
// Parametro: O formato da string a ser salva, e os dados necessarios na string
void salvarErro(char *descricao){
	// Cria uma variavel para armazenar os milisegundo atuais do sistema
	time_t segundosSistema;
	// EStrutura que guarda informacoes do horario atual
	struct tm *horarioSistemaS;
	// String que ira receber o horario atual
	char horarioAtual[63];
	// Pega os milesegundos atuais do sistema
	time(&segundosSistema);
	// Preenche os dados da estrutura com a partir dos milisegundos atuais do sistema
	horarioSistemaS = localtime(&segundosSistema);
	// Pega os dados da estrutura e transforma em uma string
	strftime(horarioAtual, 63, "%Y-%m-%d- %H:%M", horarioSistemaS);
	// Abre o arquivo de erros
	FILE *arquivoErros = fopen(LOCAL_ARQUIVO_ERROS, "a");
	// Escreve no arquivo o horario do erro e o erro que ocorreu
	fprintf(arquivoErros, "%s: %s\n", horarioAtual, descricao);	
	// Fecha o arquivo
	fclose(arquivoErros);
}

#endif /* _FUNCOES_ERRO_C_ */
