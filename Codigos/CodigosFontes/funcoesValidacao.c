#ifndef _FUNCOES_VALIDACAO_C_
#define _FUNCOES_VALIDACAO_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>



// Objetivo: Verificar se um n�mero inteiro � v�lido.
// Par�metros: Limite m�nimo e m�ximo, n�mero.
// Retorno: 1(inv�lido) ou 0(v�lido).
int validaInt (int min, int max, int num){	
	return (num < min || num > max) ? 1 : 0;
}



// Objetivo: Verificar se um n�mero float � v�lido.
// Par�metros: Limite m�nimo e m�ximo, n�mero.
// Retorno: 1(inv�lido) ou 0(v�lido).
int validaFloat (float min, float max, float num){
	return (num < min || num > max) ? 1 : 0;
}



// Objetivo: Verificar se existe um n�mero inteiro repetido dentro de um vetor.
// Par�metros: Refer�ncia ao vetor, quantidade de posi��es ocupadas.
// Retorno: 1(existe repetido) ou 0(n�o existe repetido).
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
