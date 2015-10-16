#ifndef _FUNCOES_ERRO_C_
#define _FUNCOES_ERRO_C_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOCAL_ARQUIVO_ERROS "Erros/errosProjeto.txt"



// Objetivo: Salvar no arquivo de erros, uma string
// Parametro: A string a ser salva
void salvarErro(char *stringSalvar){
	time_t segundosSistema;
	struct tm *horarioSistemaS;
	char horarioAtual[63];
	time(&segundosSistema);
	horarioSistemaS = localtime(&segundosSistema);
	strftime(horarioAtual, 63, "%Y-%m-%d- %H:%M", horarioSistemaS);
	FILE *arquivoErros = fopen(LOCAL_ARQUIVO_ERROS, "a");
	fprintf(arquivoErros, "%s: %s\n", horarioAtual, stringSalvar);	
	fclose(arquivoErros);
}

#endif /* _FUNCOES_ERRO_C_ */
