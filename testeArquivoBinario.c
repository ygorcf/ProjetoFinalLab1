// Aluno: Ygor Cruz

/*
  Objetivo:
  
  Entrada:
  
  Saida:
*/

#include <stdio.h>
#include <conio.c>

#define LOCAL_ARQUIVO_PILOTOS "Dados/Pilotos.guyg"

typedef struct {
	unsigned int id;
	char nome[255];
	unsigned int idade;
	char sexo;
	char paisOrigem[255];
} Piloto;

int main(void){
	Piloto pilotoCadastrar = {0, "Jao", 32, 'M', "Brasil"};
	FILE *arquivoPilotos = NULL;
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "ab");
	pilotoCadastrar.id = 0;
		/*printf("<%d>\n", pilotoCadastrar.id);
		printf("<%d>\n", pilotoCadastrar.idade);
		printf("<%s>\n", pilotoCadastrar.nome);
		printf("<%s>\n", pilotoCadastrar.paisOrigem);
		printf("<%c>\n", pilotoCadastrar.sexo);*/
	
	if(arquivoPilotos == NULL){
		printf("Erro abrir o arquivo com os dados dos pilotos de 'salvarPiloto'\n");
		return 1;
	}
	
	if(fwrite(&pilotoCadastrar, sizeof(Piloto), 1, arquivoPilotos) != 1){
		printf("Erro ao salvar os dados de um piloto de 'salvarPiloto'\n");
		return 1;
	}
	fclose(arquivoPilotos);
	
	
	//FILE *arquivoPilotos;
	Piloto pilotoApresentar, pilotoErro;
	int ret = 0, linhaTabela;
	//alocarPiloto(&pilotoApresentar);
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	
	if(arquivoPilotos == NULL){
		printf("Erro abrir o arquivo com os dados dos pilotos de 'apresentarTodosPilotos'\n");
		return 1;
	}
	
	for(linhaTabela = 2; !feof(arquivoPilotos); linhaTabela++){
		if(fread(&pilotoApresentar, sizeof(Piloto), 1, arquivoPilotos) != 1){
			printf("Erro ao ler um piloto!");
			return 1;
		}
		char stringIdPilotoPesquisa[4];
		sprintf(stringIdPilotoPesquisa, "%d", pilotoApresentar.id);
		printf("\n<%d>\n", pilotoApresentar.id);
		printf("<%d>\n", pilotoApresentar.idade);
		printf("<%s>\n", pilotoApresentar.nome);
		printf("<%s>\n", pilotoApresentar.paisOrigem);
		printf("<%c>\n", pilotoApresentar.sexo);
		//pintarDadoTabela(tabelaDestino, linhaTabela, 1, 5, stringIdPilotoPesquisa);
		printf("Linha tabela: %d\n", linhaTabela);
	}
	fclose(arquivoPilotos);
	system("PAUSE");
	return 0;
}

