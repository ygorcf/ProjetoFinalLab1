#ifndef _FUNCOES_PILOTO_C_
#define _FUNCOES_PILOTO_C_

#include <stdio.h>
#include <stdlib.h>

#define LOCAL_ARQUIVO_PILOTOS "/Dados/Pilotos.guyg"

typedef struct {
	unsigned int id;
	char *nome;
	unsigned int idade;
	char sexo;
	char *paisOrigem;
} Piloto;



// Objetivo: Alocar a quantidade de memória necessaria para uma nova estrutura do 
//						tipo piloto
// Retorno: A estrutura do novo piloto que foi alocado
Piloto alocarPiloto(){
	Piloto novoPiloto;
	novoPiloto.nome = (char *)(malloc(255 * sizeof(Piloto)));
	novoPiloto.paisOrigem = (char *)(malloc(255 * sizeof(Piloto)));
	return novoPiloto;
}



// Objetivo: Salvar no arquivo dos pilotos, os dados de mais um piloto
// Parametro: A estrutura contendo os dados do piloto a ser salvo
// Retorno: 0 - se o piloto foi salvo ou 1 - caso ocorrer um erro
int salvarPiloto(Piloto pilotoCadastrar){
	FILE *arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "ab");
	if(fwrite(&pilotoCadastrar, sizeof(Piloto), 1, arquivoPilotos) != 1){
		salvarErro("Erro ao salvar um piloto!");
		return 1;
	}
	fclose(arquivoPilotos);
	return 0;
}



//

#endif /* _FUNCOES_PILOTO_C_ */
