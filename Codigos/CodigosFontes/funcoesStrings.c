#ifndef _FUNCOES_STRINGS_C_
#define _FUNCOES_STRINGS_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


/*
// Objetivo: Criar uma string formatada
// Parametro: O formato que vai ficar a string e os dados necessarios no formato
// Retorno: Um ponteiro para a string formatada
char *rsprintf(char *dst, char *formato, ...){
	//dst = (char *)malloc(strlen(formato) * sizeof(char));
	//memset(dst, '\0', sizeof(dst));
	vsprintf(dst, formato, dadosNecessarios);
	va_end(dadosNecessarios);
	return dst;
}*/



// Objetivo: Diminuir um caracter da string
// Parametro: O endereco da string que ira ser retirado o caracter
// Retorno: Um ponteiro para a nova string
char *rTirarCaracter(char *stringTirarCaracter){
	stringTirarCaracter[strlen(stringTirarCaracter)-1] = '\0';
	return stringTirarCaracter;
}



// Objetivo: Retirar o quebrador de linhas no final da string
// Parametro: O endereco da string que ira ser retirado o quebrador de linha
// Retorno: Um ponteiro para a nova string
char *rRemoveQuebraLinha(char *stringTirarQuebraLinha){
	if(stringTirarQuebraLinha[strlen(stringTirarQuebraLinha)-1] == '\n')
		rTirarCaracter(stringTirarQuebraLinha);
	return stringTirarQuebraLinha;
}

#endif /* _FUNCOES_STRINGS_C_ */
