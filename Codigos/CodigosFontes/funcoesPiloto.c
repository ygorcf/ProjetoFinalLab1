#ifndef _FUNCOES_PILOTO_C_
#define _FUNCOES_PILOTO_C_

#include <stdio.h>
#include <stdlib.h>
#include <Cabecalhos/tiposDadosJanela.h>

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
	FILE *arquivoPilotos = NULL;
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "ab");
	
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'salvarPiloto'\n");
		return 1;
	}
	
	if(fwrite(&pilotoCadastrar, sizeof(Piloto), 1, arquivoPilotos) != 1){
		salvarErro("Erro ao salvar os dados de um piloto de 'salvarPiloto'\n");
		return 1;
	}
	fclose(arquivoPilotos);
	return 0;
}



//Objetivo:
Piloto pesquisarPiloto(int idPesquisar){
	FILE *arquivoPilotos;
	Piloto pilotoPesquisar, pilotoErro;
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	pilotoErro.id = 0;
	pilotoErro.idade = 0;
	pilotoErro.nome = NULL;
	pilotoErro.paisOrigem = NULL;
	pilotoErro.sexo = 'E';
	
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'pesquisarPiloto'\n");
		return pilotoErro;
	}
	
	while(!feof(arquivoPilotos)){
		if(fread(&pilotoPesquisar, sizeof(Piloto), 1, arquivoPilotos) != 1){
			salvarErro("Erro ao ler os dados de um piloto de 'pesquisarPiloto'\n");
			return pilotoErro;
		}
		if(pilotoPesquisar.id == idPesquisar)
			break;
	}
	fclose(arquivoPilotos);
	
	return pilotoPesquisar;
}



//Objetivo:
int apresentarTodosPilotos(Componente tabelaDestino){
	FILE *arquivoPilotos;
	Piloto pilotoPesquisa, pilotoErro;
	int ret = 0, linhaTabela;
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'apresentarTodosPilotos'\n");
		return 1;
	}
	
	for(linhaTabela = 2; !feof(arquivoPilotos); linhaTabela++){
		if(fread(&pilotoPesquisa, sizeof(Piloto), 1, arquivoPilotos) != 1){
			salvarErro("Erro ao salvar um piloto!");
			return 1;
		}
		char stringIdPilotoPesquisa[4];
		sprintf(stringIdPilotoPesquisa, "%d", pilotoPesquisa.id);
		pintarDadoTabela(tabelaDestino, linhaTabela, 1, 5, stringIdPilotoPesquisa);
	}
	fclose(arquivoPilotos);
	
	return ret;
}

#endif /* _FUNCOES_PILOTO_C_ */
