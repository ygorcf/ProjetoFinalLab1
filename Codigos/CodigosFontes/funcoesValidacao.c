#ifndef _FUNCOES_VALIDACAO_C_
#define _FUNCOES_VALIDACAO_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>



// Objetivo: Verificar se um número inteiro é válido.
// Parâmetros: Limite mínimo e máximo, número.
// Retorno: 1(inválido) ou 0(válido).
int validaInt (int min, int max, int num){	
	return (num < min || num > max) ? 1 : 0;
}



// Objetivo: Verificar se um número float é válido.
// Parâmetros: Limite mínimo e máximo, número.
// Retorno: 1(inválido) ou 0(válido).
int validaFloat (float min, float max, float num){
	return (num < min || num > max) ? 1 : 0;
}



// Objetivo: Verificar se existe um número inteiro repetido dentro de um vetor.
// Parâmetros: Referência ao vetor, quantidade de posições ocupadas.
// Retorno: 1(existe repetido) ou 0(não existe repetido).
int verificaIgualInt (int *vetor, int posicao){
	int i;
	int existe = 0;	
	
	for (i = posicao -1; i >= 0; i--){
		if (vetor[i] == vetor[posicao]){
			existe = 1
			break;
		}
	}
		
	return existe;
}

#endif /* _FUNCOES_VALIDACAO_C_ */
