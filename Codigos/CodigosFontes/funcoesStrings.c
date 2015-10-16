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

#endif /* _FUNCOES_STRINGS_C_ */
