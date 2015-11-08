#ifndef _FUNCOES_CIRCUITO_C_
#define _FUNCOES_CIRCUITO_C_

#include <stdio.h>
#include <stdlib.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <includesProjeto.h>
#include <Cabecalhos/funcoesPiloto.h>
#include <Cabecalhos/funcoesMelhorVolta.h>



// Objetivo: Salvar no arquivo dos circuitos, os dados de mais um circuito.
// Parametro: A estrutura contendo os dados do piloto a ser salvo.
// Retorno: 0 - se o piloto foi salvo ou 1 - caso ocorrer um erro.
int salvarCircuito(Circuito circuitoCadastrar){
	FILE *arquivoCircuitos = NULL;
	int circuitoJaCadastrado = verificarCircuitoJaCadastrado(circuitoCadastrar), ret = 0;
	
	arquivoCircuitos = fopen(LOCAL_ARQUIVO_CIRCUITOS, "ab");
	if(circuitoJaCadastrado == 0){
		fseek(arquivoCircuitos, 0, SEEK_END);
		circuitoCadastrar.codigo = ftell(arquivoCircuitos)/sizeof(Circuito);
		
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



//Objetivo:
int pesquisarCircuitoPId(int idPesquisar, Circuito *circuitoEncontrado){
	FILE *arquivoCircuitos;
	Circuito circuitoPesquisar;
	int ret = 0;
	
	arquivoCircuitos = fopen(LOCAL_ARQUIVO_CIRCUITOS, "rb");
	if(arquivoCircuitos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos circuitos de 'pesquisarCircuito'\n");
		ret = -1;
	}else{
		while(1){
			if(fread(&circuitoPesquisar, sizeof(Circuito), 1, arquivoCircuitos) != 1){
				if(!feof(arquivoCircuitos)){
					salvarErro("Erro ao ler os dados de um circuito de 'pesquisarCircuito'\n");
					ret = -2;
				}
				break;
			}
			if(circuitoPesquisar.codigo == idPesquisar){
				*circuitoEncontrado = circuitoPesquisar;
				ret = 1;
				break;
			}
		}
		if(fclose(arquivoCircuitos) != 0){
			salvarErro("Erro ao fechar o arquivo com os dados dos circuitos de 'pesquisarCircuito'\n");
			ret = -3;
		}
	}
	
	return ret;
}



//Objetivo:
void apresentarCircuitosPesquisados(Circuito *circuitosApresentar, int inicioVetor, int qtdCircuitos, Componente tabelaDestino, Janela janelaDestino){
  int circuitoAtual = inicioVetor, linhaTabela = 2, qtdLinhas;
	char stringIdCircuito[9], stringTamanhoCircuito[21], stringIdPiloto[9];
	qtdLinhas = tabelaDestino.area.h/tabelaDestino.areaAux.h;
	
	for(linhaTabela = 0; linhaTabela < qtdLinhas; linhaTabela++){
		if(strcmp(circuitosApresentar[circuitoAtual].menorTempo, "-") == 0)
			strcpy(stringIdPiloto, "-");
		else
			sprintf(stringIdPiloto, "%-8d", circuitosApresentar[circuitoAtual].idPiloto);
  	sprintf(stringIdCircuito, "%-8u", circuitosApresentar[circuitoAtual].codigo);
  	sprintf(stringTamanhoCircuito, "%-20lf", circuitosApresentar[circuitoAtual].tamanho);
  	pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 1, stringIdCircuito, janelaDestino);
  	pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 2, circuitosApresentar[circuitoAtual].nome, janelaDestino);
  	pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 3, circuitosApresentar[circuitoAtual].pais, janelaDestino);
  	pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 4, stringTamanhoCircuito, janelaDestino);
  	pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 5, circuitosApresentar[circuitoAtual].menorTempo, janelaDestino);
  	pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 6, stringIdPiloto, janelaDestino);
  	circuitoAtual++;
		if(circuitoAtual >= qtdCircuitos) break;
  }
}



// Objetivo:
int pesquisarTodosCircuitos(Circuito **circuitos){
	FILE *arquivoCircuitos;
	Circuito cuicuitoApresentar;
	int qtdCircuitos = 0;
	char stringIdCircuito[8], stringTamanhoCircuito[21], stringIdPiloto[8];
	
	arquivoCircuitos = fopen(LOCAL_ARQUIVO_CIRCUITOS, "rb");
	if(arquivoCircuitos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'apresentarTodosCircuitos'\n");
		qtdCircuitos = -1;
	}else{
		while(1){
			if(fread(&cuicuitoApresentar, sizeof(Circuito), 1, arquivoCircuitos) != 1){
				if(!feof(arquivoCircuitos)){
					salvarErro("Erro ao ler um circuito em 'apresentarTodosCircuitos'!\n");
					qtdCircuitos = -2;
				}
				break;
			}else{
				*circuitos = (Circuito *)(realloc(*circuitos, (qtdCircuitos+1) * sizeof(Circuito)));
				*(*circuitos+qtdCircuitos) = cuicuitoApresentar;
				qtdCircuitos++;
			}
		}
		if(fclose(arquivoCircuitos) != 0){
			salvarErro("Erro ao fechar o arquivo de circuitos em 'apresentarTodosCircuitos'!\n");
			qtdCircuitos = -3;
		}
	}
	if(qtdCircuitos > 1)
		qsort(*circuitos, qtdCircuitos, sizeof(Circuito), ordenarCircuitoNome);
	
	return qtdCircuitos;
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



//Objetivo:
int pesquisarCircuitoPNome(char *nomePesquisar, Circuito **circuitosEncontrados){
	FILE *arquivoCircuitos;
	Circuito circuitoPesquisar, circuitoErro;
	int qtdCircuitosEncontrados = 0;
	
	arquivoCircuitos = fopen(LOCAL_ARQUIVO_CIRCUITOS, "rb");
	
	if(arquivoCircuitos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'pesquisarCircuitoPNome'\n");
		qtdCircuitosEncontrados = -1;
	}else{
		while(!feof(arquivoCircuitos)){
			if(fread(&circuitoPesquisar, sizeof(Circuito), 1, arquivoCircuitos) != 1){
				salvarErro("Erro ao ler os dados de um piloto de 'pesquisarCircuitoPNome'\n");
				qtdCircuitosEncontrados = -2;
				break;
			}else{
			  if(strstr(circuitoPesquisar.nome, nomePesquisar) != NULL){
			    *circuitosEncontrados = (Circuito *)(realloc(*circuitosEncontrados, (qtdCircuitosEncontrados+1) * sizeof(Circuito)));
			    *(*circuitosEncontrados + qtdCircuitosEncontrados) = circuitoPesquisar;
			    qtdCircuitosEncontrados++;
			  }
			}
		}
	}
	fclose(arquivoCircuitos);
	
	return qtdCircuitosEncontrados;
}



//Objetivo:
int apresentarRelatorio4(Circuito *circuitosApresentar, int inicioVetor, int qtdCircuitos, Componente tabelaDestino, Janela janelaDestino){
  int circuitoAtual = inicioVetor, ret = 0, qtdLinhas, linhaTabela;
  MelhorVolta melhorVoltaCircuitoAtual;
  Piloto pilotoCircuitoAtual;
	char stringIdCircuito[8], stringTamanhoCircuito[10], stringIdPiloto[8], stringNomePiloto[10];
	qtdLinhas = tabelaDestino.area.h/tabelaDestino.areaAux.h;
  
	for(linhaTabela = 0; linhaTabela < qtdLinhas; linhaTabela++){
		sprintf(stringIdCircuito, "%-7d", circuitosApresentar[circuitoAtual].codigo);
		sprintf(stringTamanhoCircuito, "%-20lf", circuitosApresentar[circuitoAtual].tamanho);
		strcpy(stringIdPiloto, "-");
		strcpy(stringNomePiloto, "-");
		if(strcmp(circuitosApresentar[circuitoAtual].menorTempo, "-") != 0){
			if(pesquisarPilotoPId(circuitosApresentar[circuitoAtual].idPiloto, &pilotoCircuitoAtual) <= 0){
				salvarErro("Erro ao pesquisar um piloto em 'apresentarRelatorio4'\n");
				ret = -1;
			}else{
				sprintf(stringIdPiloto, "%-7d", circuitosApresentar[circuitoAtual].idPiloto);
				strncpy(stringNomePiloto, pilotoCircuitoAtual.nome, 9);
			}
		}
		
		pintarDadoTabela(tabelaDestino, linhaTabela + 2, 1, stringIdCircuito, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela + 2, 2, circuitosApresentar[circuitoAtual].nome, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela + 2, 3, circuitosApresentar[circuitoAtual].pais, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela + 2, 4, stringTamanhoCircuito, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela + 2, 5, circuitosApresentar[circuitoAtual].menorTempo, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela + 2, 6, stringIdPiloto, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela + 2, 7, stringNomePiloto, janelaDestino);
		circuitoAtual++;
		if(circuitoAtual >= qtdCircuitos) break;
	}
	
	return ret;
}



int ordenarCircuitoNome(const void * circuito1, const void * circuito2){
	return ( strncmp(((Circuito*)circuito1)->nome, ((Circuito*)circuito2)->nome, 1) );
}


#endif /* _FUNCOES_CIRCUITO_C_ */
