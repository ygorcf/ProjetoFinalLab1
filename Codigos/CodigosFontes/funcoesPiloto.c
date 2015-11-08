#ifndef _FUNCOES_PILOTO_C_
#define _FUNCOES_PILOTO_C_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <includesProjeto.h>
#include <time.h>
#include <Cabecalhos/funcoesCircuito.h>
#include <Cabecalhos/funcoesMelhorVolta.h>

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
	if(arquivoPilotos == NULL){
		salvarErro("Erro ao abrir o arquivo com os dados dos pilotos em 'salvarPiloto'\n");
		ret = -1;
	}else{
		if(pilotoJaCadastrado == 0){	
			if(fwrite(&pilotoCadastrar, sizeof(Piloto), 1, arquivoPilotos) != 1){
				salvarErro("Erro ao salvar os dados de um piloto de 'salvarPiloto'\n");
				ret = -2;
			}
		}else if(pilotoJaCadastrado < 0){
			salvarErro("Erro na funcao 'verificarPilotoJaCadastrado' de 'salvarPiloto'\n");
			ret = -3;
		}else{
			ret = 1;
		}
		if(fclose(arquivoPilotos) != 0){
			salvarErro("Erro ao fechar arquivo de pilotos em 'salvarPiloto'\n");
			ret = -4;
		}
	}
	
	return ret;
}



//Objetivo:
int pesquisarPilotoPId(int idPesquisar, Piloto *pilotoEncontrado){
	FILE *arquivoPilotos;
	Piloto pilotoPesquisar;
	int ret = 0;
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");	
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'pesquisarPiloto'\n");
		ret = -1;
	}else{
		while(1){
			if(fread(&pilotoPesquisar, sizeof(Piloto), 1, arquivoPilotos) != 1){
				if(!feof(arquivoPilotos)){
					salvarErro("Erro ao ler os dados de um piloto de 'pesquisarPiloto'\n");
					ret = -2;
				}
				break;
			}
			if(pilotoPesquisar.id == idPesquisar){
				*pilotoEncontrado = pilotoPesquisar;
				ret = 1;
				break;
			}
		}
		if(fclose(arquivoPilotos)){
			salvarErro("Erro ao fechar o arquivo de pilotos de 'pesquisarPilotoPId'\n");
			ret = -3;
		}
	}
	
	return ret;
}



//Objetivo:
int pesquisarPilotoPNome(char *nomePesquisar, Piloto **pilotosEncontrados){
	FILE *arquivoPilotos;
	Piloto pilotoPesquisar;
	int qtdPilotosEncontrados = 0;
	//pilotosEncontrados = NULL;
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'pesquisarPilotoPNome'\n");
		qtdPilotosEncontrados = -1;
	}else{
		while(!feof(arquivoPilotos)){
			if(fread(&pilotoPesquisar, sizeof(Piloto), 1, arquivoPilotos) != 1){
				if(!feof(arquivoPilotos)){
					salvarErro("Erro ao ler os dados de um piloto de 'pesquisarPilotoPNome'\n");
					qtdPilotosEncontrados = -2;
				}
				break;
			}else{
			  if(strstr(pilotoPesquisar.nome, nomePesquisar) != NULL){
			    *pilotosEncontrados = (Piloto *)(realloc(*pilotosEncontrados, (qtdPilotosEncontrados+1) * sizeof(Piloto)));
			    *(*pilotosEncontrados + qtdPilotosEncontrados) = pilotoPesquisar;
			    qtdPilotosEncontrados++;
			  }
			}
		}
	}
	
	fclose(arquivoPilotos);
	
	return qtdPilotosEncontrados;
}



//Objetivo:
void apresentarPilotosPesquisados(Piloto *pilotosApresentar, int inicioVetor, int qtdPilotos, Componente tabelaDestino, Janela janelaDestino){
  int pilotoAtual = inicioVetor, linhaTabela, qtdLinhas;
	char stringIdPiloto[9], stringIdadePiloto[4], stringSexoPiloto[3];
	qtdLinhas = tabelaDestino.area.h/tabelaDestino.areaAux.h;
	
	for(linhaTabela = 0; linhaTabela < qtdLinhas; linhaTabela++){
		sprintf(stringIdPiloto, "%-8u", pilotosApresentar[pilotoAtual].id);
		sprintf(stringIdadePiloto, "%3u", pilotosApresentar[pilotoAtual].idade);
		sprintf(stringSexoPiloto, "%c", pilotosApresentar[pilotoAtual].sexo);
		pintarDadoTabela(tabelaDestino, linhaTabela+2, 1, stringIdPiloto, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela+2, 2, pilotosApresentar[pilotoAtual].nome, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela+2, 3, stringIdadePiloto, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela+2, 4, stringSexoPiloto, janelaDestino);
		pintarDadoTabela(tabelaDestino, linhaTabela+2, 5, pilotosApresentar[pilotoAtual].paisOrigem, janelaDestino);
		pilotoAtual++;
		if(pilotoAtual >= qtdPilotos) break;
	}
}



// Objetivo:
int pesquisarTodosPilotos(Piloto **pilotos){
	FILE *arquivoPilotos;
	Piloto pilotoApresentar;
	int linhaTabela = 2, qtdPilotos = 0, contadorPilotos;
	char stringIdPiloto[4], stringIdadePiloto[4], stringSexoPiloto[2];
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'pesquisarTodosPilotos'\n");
		qtdPilotos = -1;
	}else{
		while(1){
			if(fread(&pilotoApresentar, sizeof(Piloto), 1, arquivoPilotos) != 1){
				if(!feof(arquivoPilotos)){
					salvarErro("Erro ao ler um piloto em 'pesquisarTodosPilotos'!\n");
					qtdPilotos = -2;
				}
				break;
			}else{
				*pilotos = (Piloto *)(realloc(*pilotos, (qtdPilotos+1) * sizeof(Piloto)));
				*(*pilotos+qtdPilotos) = pilotoApresentar;
				qtdPilotos++;
			}
		}
		if(fclose(arquivoPilotos) != 0){
			salvarErro("Erro ao fechar o arquivo de pilotos em 'pesquisarTodosPilotos'!\n");
			qtdPilotos = -3;
		}
	}
	if(qtdPilotos > 1)
		qsort(*pilotos, qtdPilotos, sizeof(Piloto), ordenarPilotoNome);
	
	return qtdPilotos;
}



// Objetivo:
int verificarPilotoJaCadastrado(Piloto pilotoVerificar){
	FILE *arqPilotos;
	Piloto pilotoPesquisa;
	int pilotoJaCadastrado = 0;
	
	arqPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	if(arqPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'verificarPilotoJaCadastrado'\n");
		pilotoJaCadastrado -1;
	}else{
		while(1){
			if(fread(&pilotoPesquisa, sizeof(Piloto), 1, arqPilotos) != 1){
				if(!feof(arqPilotos)){
					salvarErro("Erro ao ler os dados de um piloto de 'verificarPilotoJaCadastrado'\n");
					pilotoJaCadastrado -2;
				}
				break;
			}
			if((pilotoPesquisa.idade == pilotoVerificar.idade && 
					 pilotoPesquisa.nome == pilotoVerificar.nome && 
					 pilotoPesquisa.paisOrigem == pilotoVerificar.paisOrigem && 
					 pilotoPesquisa.sexo == pilotoVerificar.sexo) || 
					 (pilotoPesquisa.id == pilotoVerificar.id)){
				pilotoJaCadastrado = 1;
				break;
			}
		}
		if(fclose(arqPilotos) != 0){
			salvarErro("Erro ao ler os dados de um piloto de 'verificarPilotoJaCadastrado'\n");
			pilotoJaCadastrado -3;
		}
	}
	
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
int alterarPiloto(int idAntigo, Piloto pilotoAlterar){
	FILE *arquivoPilotos = NULL;
	int ret = 0;
	Piloto pilotoSalvo;
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "r+b");
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'alterarPiloto'\n");
		ret = -1;
	}else{
		while(1){
			if(fread(&pilotoSalvo, sizeof(Piloto), 1, arquivoPilotos) != 1){
				if(!feof(arquivoPilotos)){
					salvarErro("Erro ler os dados do arquivo com os dados dos pilotos de 'alterarPiloto'\n");
					ret = -2;
				}
				break;
			}else{
				if(pilotoSalvo.id == idAntigo){
					if(fseek(arquivoPilotos, -sizeof(Piloto), SEEK_CUR) != 0){
						salvarErro("Erro abrir ao posicionar o arquivo com os dados dos pilotos de 'alterarPiloto'\n");
						ret = -3;
					}else{
						if(fwrite(&pilotoAlterar, sizeof(Piloto), 1, arquivoPilotos) != 1){
							salvarErro("Erro ao salvar os dados alterados no arquivo temporario de um piloto em 'alterarPiloto'\n");
							ret = -4;
						}else break;
					}
				}
			}
		}
		if(fclose(arquivoPilotos) != 0){
			salvarErro("Erro abrir ao fechar o arquivo com os dados dos pilotos de 'alterarPiloto'\n");
			ret = -5;
		}
	}
	
	return ret;
}



// Objetivo: 
int excluirPiloto(Piloto pilotoExcluir){
	FILE *arquivoPilotos = NULL, *arquivoPilotosTemporario;
	int ret = 1;
	Piloto pilotoTemporario;
	
	arquivoPilotos = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	if(arquivoPilotos == NULL){
		salvarErro("Erro abrir o arquivo com os dados dos pilotos de 'excluirPiloto'\n");
		ret = -1;
	}else{
		arquivoPilotosTemporario = fopen(LOCAL_ARQUIVO_PILOTOS_TMP, "wb");
		if(arquivoPilotosTemporario == NULL){
			salvarErro("Erro abrir o arquivo temporario para excluir um dos pilotos de 'excluirPiloto'\n");
			ret = -2;
		}	else{
			while(1){
				if(fread(&pilotoTemporario, sizeof(Piloto), 1, arquivoPilotos) != 1){
					if(!feof(arquivoPilotos)){
						salvarErro("Erro ao ler os dados do arquivo de um piloto em 'excluirPiloto'\n");
						ret = -3;
					}
					break;
				}else{	    
					if(pilotoTemporario.id != pilotoExcluir.id){
						if(fwrite(&pilotoTemporario, sizeof(Piloto), 1, arquivoPilotosTemporario) != 1){
							salvarErro("Erro ao salvar os dados alterados no arquivo temporario de um piloto em 'excluirPiloto'\n");
							ret = -4;
							break;
						}
					}else{
						ret = 0;
					}
				}
			}
			if(fclose(arquivoPilotosTemporario) != 0){
				salvarErro("Erro ao fechar o arquivo temporario de pilotos em 'excluirPiloto'\n");
				ret = -5;
			}
		}
		if(fclose(arquivoPilotos) != 0){	
			salvarErro("Erro ao fechar o arquivo de pilotos em 'excluirPiloto'\n");
			ret = -6;
		}
	}
	if(ret == 0){
		if(remove(LOCAL_ARQUIVO_PILOTOS) != 0){
			salvarErro("Erro ao remover o arquivo de pilotos em 'excluirPiloto'\n");
			ret = -7;
		}else{
			if(rename(LOCAL_ARQUIVO_PILOTOS_TMP, LOCAL_ARQUIVO_PILOTOS) != 0){
				salvarErro("Erro ao renomear o arquivo temporario de pilotos em 'excluirPiloto'\n");
				ret = -8;
			}
		}
	}
	
	return ret;
}



//Objetivo:
int pesquisarPilotosCircuito(Circuito circuitoPilotoPesquisar, char *dataPesquisar, Piloto **pilotosEncontrados){
	Piloto pilotoPesquisar;
	int qtdPilotosEncontrados = 0;
	FILE *arquivoMelhoresVoltas;
	MelhorVolta melhorVoltaPesquisada;
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS, "rb");
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro ao abrir arquivo de melhores voltas em 'pesquisarPilotosCircuito'\n");
		qtdPilotosEncontrados = -1;
	}else{
		while(1){
			if(fread(&melhorVoltaPesquisada, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				if(!feof(arquivoMelhoresVoltas)){
					salvarErro("Erro ao ler melhor volta em 'pesquisarPilotosCircuito'\n");
					qtdPilotosEncontrados = -2;
				}
				break;
			}else{
				if(melhorVoltaPesquisada.idCircuito == circuitoPilotoPesquisar.codigo){
					if(strcmp(circuitoPilotoPesquisar.menorTempo, "-") != 0){
						if(pesquisarPilotoPId(circuitoPilotoPesquisar.idPiloto, &pilotoPesquisar) != 1){
							salvarErro("Erro ao pesquisar piloto em 'pesquisarPilotosCircuito'\n");
							qtdPilotosEncontrados = -3;
						}else{
							if(strlen(dataPesquisar) == 0 || (strlen(dataPesquisar) == 10 && strcmp(dataPesquisar, melhorVoltaPesquisada.data) == 0)){
								*pilotosEncontrados = (Piloto*)(realloc(*pilotosEncontrados, (qtdPilotosEncontrados+1) * sizeof(Piloto)));
								*(*pilotosEncontrados+qtdPilotosEncontrados) = pilotoPesquisar;
								qtdPilotosEncontrados++;
							}
						}
					}
				}
			}
		}
		if(fclose(arquivoMelhoresVoltas) != 0){
			salvarErro("Erro ao fechar arquivo de  melhores voltas em 'pesquisarPilotosCircuito'\n");
			qtdPilotosEncontrados = -4;
		}
	}
	
	return qtdPilotosEncontrados;
}



int ordenarPilotoNome(const void * piloto1, const void * piloto2){
	return ( strncmp(((Piloto*)piloto1)->nome, ((Piloto*)piloto2)->nome, 1) );
}

#endif /* _FUNCOES_PILOTO_C_ */
