#ifndef _FUNCOES_CIRCUITO_C_
#define _FUNCOES_CIRCUITO_C_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <includesProjeto.h>

#define LOCAL_ARQUIVO_CIRCUITOS "Dados/Circuitos.guyg"
/*


// Objetivo: Alocar a quantidade de memória necessaria para uma nova estrutura do 
//						tipo piloto
// Retorno: A estrutura do novo piloto que foi alocado
void alocarPiloto(Piloto *pilotoAlocar){
	pilotoAlocar->nome = (char *)(malloc(255 * sizeof(char)));
	pilotoAlocar->paisOrigem = (char *)(malloc(255 * sizeof(char)));
	pilotoAlocar = (Piloto *)(malloc(1 * sizeof(Piloto)));
}*/
/*


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
*/



// Objetivo: Salvar no arquivo dos circuitos, os dados de mais um circuito.
// Parametro: A estrutura contendo os dados do piloto a ser salvo.
// Retorno: 0 - se o piloto foi salvo ou 1 - caso ocorrer um erro.
int salvarCircuito(Circuito circuitoCadastrar){
	FILE *arquivoCircuitos = NULL;
	arquivoCircuitos = fopen(LOCAL_ARQUIVO_CIRCUITOS, "ab");
	int circuitoJaCadastrado = verificarCircuitoJaCadastrado(circuitoCadastrar), ret = 0;
	if(circuitoJaCadastrado == 0){
		fseek(arquivoCircuitos, 0, SEEK_END);
		circuitoCadastrar.codigo = ftell(arquivoCircuitos)/sizeof(Circuito);
		//pilotoCadastrar.id = obtemUltimoIdCadastradoPiloto();
		//pilotoCadastrar.id++;
		
		if(arquivoCircuitos == NULL){
			salvarErro("Erro abrir o arquivo com os dados dos circuitos de 'salvarCircuito'\n");
			ret = 1;
		} else {
			if(fwrite(&circuitoCadastrar, sizeof(Circuito), 1, arquivoCircuitos) != 1){
				salvarErro("Erro ao salvar os dados de um circuito de 'salvarCircuito'\n");
				ret = 1;
			}
		}
	} else if(circuitoJaCadastrado < 0){
		salvarErro("Erro na funcao 'verificarPilotoJaCadastrado' de 'salvarPiloto'\n");
		ret = 1;
	}
	fclose(arquivoCircuitos);
	
	return ret;
}



// Objetivo:
int apresentarTodosCircuitos(Componente tabelaDestino, Janela janelaDestino){
	FILE *arquivoCircuitos;
	Circuito cuicuitoApresentar;
	int linhaTabela = 2, ret = 0;
	
	arquivoCircuitos = fopen(LOCAL_ARQUIVO_CIRCUITOS, "rb");
	if(arquivoCircuitos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'apresentarTodosCircuitos'\n");
		ret = 1;
	} else {
		while(!feof(arquivoCircuitos)){
			if(fread(&cuicuitoApresentar, sizeof(Circuito), 1, arquivoCircuitos) != 1){
				if(!feof(arquivoCircuitos)){
					salvarErro("Erro ao ler um circuito em 'apresentarTodosCircuitos'!\n");
					ret = 1;
				}
				break;
			}else{
				char stringIdCircuito[8], stringTamanhoCircuito[10];
				sprintf(stringIdCircuito, "%d", cuicuitoApresentar.codigo);
				sprintf(stringTamanhoCircuito, "%d", cuicuitoApresentar.tamanho);
				pintarDadoTabela(tabelaDestino, linhaTabela, 1, stringIdCircuito, janelaDestino);
				pintarDadoTabela(tabelaDestino, linhaTabela, 2, cuicuitoApresentar.nome, janelaDestino);
				pintarDadoTabela(tabelaDestino, linhaTabela, 3, cuicuitoApresentar.pais, janelaDestino);
				pintarDadoTabela(tabelaDestino, linhaTabela, 4, stringTamanhoCircuito, janelaDestino);
				pintarDadoTabela(tabelaDestino, linhaTabela, 5, cuicuitoApresentar.menorTempo, janelaDestino);
				linhaTabela++;
			}
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
	fclose(arquivoCircuitos);
	
	return ret;
}



// Objetivo:
int verificarCircuitoJaCadastrado(Circuito circuitoVerificar){
	FILE *arquivoCircuitos;
	Circuito circuitoPesquisa;
	int circuitoJaCadastrado = 0;
	
	arquivoCircuitos = fopen(LOCAL_ARQUIVO_CIRCUITOS, "rb");
	if(arquivoCircuitos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'verificarPilotoJaCadastrado'\n");
		circuitoJaCadastrado = -1;
	}else{
		while(!feof(arquivoCircuitos)){
			if(fread(&circuitoPesquisa, sizeof(Circuito), 1, arquivoCircuitos) != 1){
				if(!feof(arquivoCircuitos)){
					salvarErro("Erro ao ler os dados de um piloto de 'verificarPilotoJaCadastrado'\n");
					circuitoJaCadastrado = -2;
				}
				break;
			}
			if(circuitoPesquisa.menorTempo == circuitoVerificar.menorTempo && circuitoPesquisa.nome == circuitoVerificar.nome && 
					circuitoPesquisa.pais == circuitoVerificar.pais && circuitoPesquisa.tamanho == circuitoVerificar.tamanho){
				circuitoJaCadastrado = 1;
				break;
			}
		}
	}
	fclose(arquivoCircuitos);
	
	return circuitoJaCadastrado;
}
/*


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
*/


// Objetivo: 
int alterarCircuito(Circuito circuitoAlterar){
	FILE *arquivoCircuitos = NULL;
	int ret = 0;
	
	arquivoCircuitos = fopen(LOCAL_ARQUIVO_CIRCUITOS, "r+b");
	if(arquivoCircuitos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'alterarCircuito'\n");
		ret = 1;
	}	else {
		fseek(arquivoCircuitos, circuitoAlterar.codigo * sizeof(Circuito), SEEK_SET);
		if(fwrite(&circuitoAlterar, sizeof(Circuito), 1, arquivoCircuitos) != 1){
			salvarErro("Erro ao salvar os dados alterados no arquivo de um circuito em 'alterarCircuito'\n");
			ret = 1;
		}
	}
	fclose(arquivoCircuitos);
	
	return ret;
}

#endif /* _FUNCOES_CIRCUITO_C_ */
