#ifndef _FUNCOES_PILOTO_C_
#define _FUNCOES_PILOTO_C_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <includesProjeto.h>

#define LOCAL_ARQUIVO_PILOTOS "Dados/Pilotos.guyg"
#define LOCAL_ARQUIVO_PILOTOS_TMP "Dados/PilotosTmp.guyg"
/*


// Objetivo: Alocar a quantidade de memória necessaria para uma nova estrutura do 
//						tipo piloto
// Retorno: A estrutura do novo piloto que foi alocado
void alocarPiloto(Piloto *pilotoAlocar){
	pilotoAlocar->nome = (char *)(malloc(255 * sizeof(char)));
	pilotoAlocar->paisOrigem = (char *)(malloc(255 * sizeof(char)));
	pilotoAlocar = (Piloto *)(malloc(1 * sizeof(Piloto)));
}*/



// Objetivo: Salvar no arquivo dos pilotos, os dados de mais um piloto
// Parametro: A estrutura contendo os dados do piloto a ser salvo
// Retorno: 0 - se o piloto foi salvo ou 1 - caso ocorrer um erro
int salvarPiloto(Piloto pilotoCadastrar){
	FILE *arquivoPilotos = NULL;
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "ab");
	int pilotoJaCadastrado = verificarPilotoJaCadastrado(pilotoCadastrar), ret = 0;
	if(pilotoJaCadastrado == 0){
		fseek(arquivoPilotos, 0, SEEK_END);
		pilotoCadastrar.id = ftell(arquivoPilotos)/sizeof(Piloto);
		//pilotoCadastrar.id = obtemUltimoIdCadastradoPiloto();
		//pilotoCadastrar.id++;
		
		if(arquivoPilotos == NULL){
			salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'salvarPiloto'\n");
			ret = 1;
		}
		
		if(fwrite(&pilotoCadastrar, sizeof(Piloto), 1, arquivoPilotos) != 1){
			salvarErro("Erro ao salvar os dados de um piloto de 'salvarPiloto'\n");
			ret = 1;
		}
		
	} else if(pilotoJaCadastrado < 0){
		salvarErro("Erro na funcao 'verificarPilotoJaCadastrado' de 'salvarPiloto'\n");
		ret = 1;
	}
	fclose(arquivoPilotos);
	
	return ret;
}



//Objetivo:
Piloto pesquisarPiloto(int idPesquisar){
	FILE *arquivoPilotos;
	Piloto pilotoPesquisar, pilotoErro;
	int ret = 0;
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	pilotoErro.id = 0;
	pilotoErro.idade = 0;
	//pilotoErro.nome = "ERRO";
	//pilotoErro.paisOrigem = "ERRO";
	pilotoErro.sexo = 'E';
	//alocarPiloto(&pilotoPesquisar);
	
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'pesquisarPiloto'\n");
		ret = 1;
	}
	
	while(!feof(arquivoPilotos)){
		if(fread(&pilotoPesquisar, sizeof(pilotoPesquisar), 1, arquivoPilotos) != 1){
			salvarErro("Erro ao ler os dados de um piloto de 'pesquisarPiloto'\n");
			ret = 1;
		}
		if(pilotoPesquisar.id == idPesquisar)
			break;
	}
	fclose(arquivoPilotos);
	
	return ((ret == 0) ? pilotoPesquisar : pilotoErro);
}



// Objetivo:
int apresentarTodosPilotos(Componente tabelaDestino, Janela janelaDestino){
	FILE *arquivoPilotos;
	Piloto pilotoApresentar, pilotoErro;
	int linhaTabela = 2, ret = 0;
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'apresentarTodosPilotos'\n");
		ret = 1;
	}
	
	while(!feof(arquivoPilotos)){
		if(fread(&pilotoApresentar, sizeof(Piloto), 1, arquivoPilotos) != 1){
			if(!feof(arquivoPilotos)){
				salvarErro("Erro ao ler um piloto!");
				ret = 1;
			}
			break;
		}else{
			char stringIdPiloto[4], stringIdadePiloto[4], stringSexoPiloto[3], stringNomeAparecer[12];
			sprintf(stringIdPiloto, "%d", pilotoApresentar.id);
			sprintf(stringIdadePiloto, "%d", pilotoApresentar.idade);
			sprintf(stringSexoPiloto, "%c", pilotoApresentar.sexo);
			strncpy(stringNomeAparecer, pilotoApresentar.nome, 9);
			strcat(stringNomeAparecer, "...");
			pintarDadoTabela(tabelaDestino, linhaTabela, 1, stringIdPiloto, janelaDestino);
			pintarDadoTabela(tabelaDestino, linhaTabela, 2, stringNomeAparecer, janelaDestino);
			pintarDadoTabela(tabelaDestino, linhaTabela, 3, stringIdadePiloto, janelaDestino);
			pintarDadoTabela(tabelaDestino, linhaTabela, 4, stringSexoPiloto, janelaDestino);
			pintarDadoTabela(tabelaDestino, linhaTabela, 5, pilotoApresentar.paisOrigem, janelaDestino);
			linhaTabela++;
		}
	}
	/*
	for(linhaTabela = 2; !feof(arquivoPilotos); linhaTabela++){
		if(fread(&pilotoApresentar, sizeof(Piloto), 1, arquivoPilotos) != 1){
			salvarErro("Erro ao ler um piloto!");
			return 1;
		}
		char stringIdPiloto[4], stringIdadePiloto[4], stringSexoPiloto[3];
		sprintf(stringIdPiloto, "%d", pilotoApresentar.id);
		sprintf(stringIdadePiloto, "%d", pilotoApresentar.idade);
		sprintf(stringSexoPiloto, "%c", pilotoApresentar.sexo);
		pintarDadoTabela(tabelaDestino, linhaTabela, 1, stringIdPiloto, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela, 2, pilotoApresentar.nome, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela, 3, stringIdadePiloto, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela, 4, stringSexoPiloto, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela, 5, pilotoApresentar.paisOrigem, janelaDestino);
		//pintarDadoTabela((Componente){tabelaDestino.painelPertencente, tabelaDestino.area, tabelaDestino.areaAux}, linhaTabela, 1, stringIdPilotoPesquisa);
	}*/
	fclose(arquivoPilotos);
	
	return ret;
}



// Objetivo:
int verificarPilotoJaCadastrado(Piloto pilotoVerificar){
	FILE *arqPilotos;
	Piloto pilotoPesquisa;
	int pilotoJaCadastrado = 0;
	
	arqPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	if(ftell(arqPilotos) == 0) return 0;
	if(arqPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'verificarPilotoJaCadastrado'\n");
		pilotoJaCadastrado -1;
	}
	while(!feof(arqPilotos) && ftell(arqPilotos)>0){
		if(fread(&pilotoPesquisa, sizeof(Piloto), 1, arqPilotos) != 1){
			salvarErro("Erro ao ler os dados de um piloto de 'verificarPilotoJaCadastrado'\n");
			pilotoJaCadastrado -2;
		}
		if(pilotoPesquisa.idade == pilotoVerificar.idade && pilotoPesquisa.nome == pilotoVerificar.nome && 
				pilotoPesquisa.paisOrigem == pilotoVerificar.paisOrigem && pilotoPesquisa.sexo == pilotoVerificar.sexo){
			pilotoJaCadastrado = 1;
			break;
		}
	}
	fclose(arqPilotos);
	
	return pilotoJaCadastrado;
}



// Objetivo:
int obtemUltimoIdCadastradoPiloto(){
	FILE *arqPilotos;
	Piloto pilotoPesquisa;
	int ultimoIdCadastrado = 0;
	
	arqPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	
	if(errno == 2){
		//fclose(fopen(LOCAL_ARQUIVO_PILOTOS, "wb"));
		fclose(arqPilotos);
		ultimoIdCadastrado = 0;
	}
	if(arqPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'apresentarTodosPilotos'\n");
		ultimoIdCadastrado = -1;
	}
	if(ftell(arqPilotos) == 0) return 0;
	
	fseek(arqPilotos, sizeof(Piloto), SEEK_END);
	if(fread(&pilotoPesquisa, sizeof(Piloto), 1, arqPilotos) != 1){
		salvarErro("Erro ao ler os dados de um piloto de 'pesquisarPiloto'\n");
		ultimoIdCadastrado = -2;
	}else{
		ultimoIdCadastrado = pilotoPesquisa.id;
	}
	
	return ultimoIdCadastrado;
}



// Objetivo: 
int alterarPiloto(Piloto pilotoAlterar){
	FILE *arquivoPilotos = NULL;
	int ret = 0;
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "r+b");
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'alterarPiloto'\n");
		ret = 1;
	}	
	int idAtualPilotArquivoTemporario = 0;
	
	fseek(arquivoPilotos, pilotoAlterar.id * sizeof(Piloto), SEEK_SET);
	if(fwrite(&pilotoAlterar, sizeof(Piloto), 1, arquivoPilotos) != 1){
		salvarErro("Erro ao salvar os dados alterados no arquivo temporario de um piloto em 'alterarPiloto'\n");
		ret = 1;
	}
	
	fclose(arquivoPilotos);
	
	return ret;
}



// Objetivo: 
int excluirPiloto(Piloto pilotoExcluir){
	FILE *arquivoPilotos = NULL, *arquivoPilotosTemporario;
	int ret = 0;
	Piloto pilotoTemporario;
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	arquivoPilotosTemporario = fopen(LOCAL_ARQUIVO_PILOTOS_TMP, "wb");
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'excluirPiloto'\n");
		ret = 1;
	}	
	if(arquivoPilotosTemporario == NULL){
		salvarErro("Erro abrir o arquivo temporario para excluir um dos pilotos de 'excluirPiloto'\n");
		ret = 1;
	}	
	int idAtualPilotArquivoTemporario = 0;
	while(!feof(arquivoPilotos)){
		if(fread(&pilotoTemporario, sizeof(Piloto), 1, arquivoPilotos) != 1){
			if(!feof(arquivoPilotos)){
				salvarErro("Erro ao ler os dados do arquivo de um piloto em 'excluirPiloto'\n");
				ret = 1;
			}
			break;
		}else{
			if(idAtualPilotArquivoTemporario != pilotoExcluir.id){
				if(fwrite(&pilotoTemporario, sizeof(Piloto), 1, arquivoPilotosTemporario) != 1){
					salvarErro("Erro ao salvar os dados alterados no arquivo temporario de um piloto em 'excluirPiloto'\n");
					ret = 1;
					break;
				}
			}
			idAtualPilotArquivoTemporario++;
		}
	}
	if(fclose(arquivoPilotos) != 0){		
		salvarErro("Erro ao fechar o arquivo de pilotos em 'excluirPiloto'\n");
		ret = 1;
	}else{
		if(fclose(arquivoPilotosTemporario) != 0){
			salvarErro("Erro ao fechar o arquivo temporario de pilotos em 'excluirPiloto'\n");
			ret = 1;
		}else{
			if(remove(LOCAL_ARQUIVO_PILOTOS) != 0){
				salvarErro("Erro ao remover o arquivo de pilotos em 'excluirPiloto'\n");
				ret = 1;
			}else{
				if(rename(LOCAL_ARQUIVO_PILOTOS_TMP, LOCAL_ARQUIVO_PILOTOS) != 0){
					salvarErro("Erro ao renomear o arquivo temporario de pilotos em 'excluirPiloto'\n");
					ret = 1;
				}
			}
		}
	}
	
	return ret;
}

#endif /* _FUNCOES_PILOTO_C_ */
