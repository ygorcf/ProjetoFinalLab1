#ifndef _FUNCOES_STRINGS_C_
#define _FUNCOES_STRINGS_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>



// Objetivo: Criar uma string formatada
// Parametro: O formato que vai ficar a string e os dados necessarios no formato
// Retorno: Um ponteiro para a string formatada
char *rsprintf(char *formato, ...){
	va_list dadosNecessarios;
	char *strinRet;
	vsprintf(strinRet, formato, dadosNecessarios);
	va_end(dadosNecessarios);
	return strinRet;
}



// Objetivo: Diminuir um caracter da string
// Parametro: O endereco da string que ira ser retirado o caracter
// Retorno: Um ponteiro para a nova string
char *rTirarCaracter(char *stringTirarCaracter){
	stringTirarCaracter[strlen(stringTirarCaracter)-1] = '\0';
	return stringTirarCaracter;
}

#endif /* _FUNCOES_STRINGS_C_ */
