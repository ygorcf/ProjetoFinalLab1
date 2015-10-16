#ifndef _ABRE_ARQUIVOS_C_
#define _ABRE_ARQUIVOS_C_

#include <stdio.h>
#include <stdlib.h>



// Objetivo: Criar um arquivo que ira conter todos os erros que aconteceram 
//				 durante a execucao do projeto
// Parametro: O endereco da string que contem o nome do arquivo de erros
// Retorno: Um ponteiro FILE que aponta para o arquivo onde sera salvo os erros
FILE *criaArquivoErros(char *nomeArquivo){
	if(nomeArquivo[strlen(nomeArquivo)-4] != '.' && 
		nomeArquivo[strlen(nomeArquivo)-3] != 't' && 
		nomeArquivo[strlen(nomeArquivo)-2] != 'x' && 
		nomeArquivo[strlen(nomeArquivo)-1] != 't')
		strcat(nomeArquivo, ".txt");

	FILE *arq;
	arq = fopen(nomeArquivo, "w+");
	if(arq == NULL)
		exit(1);
	return arq;
}

#endif
