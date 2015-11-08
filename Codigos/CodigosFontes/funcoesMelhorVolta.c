#ifndef _FUNCOES_MELHOR_VOLTA_C_
#define _FUNCOES_MELHOR_VOLTA_C_

#include <stdio.h>
#include <stdlib.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <includesProjeto.h>
#include <Cabecalhos/funcoesPiloto.h>
#include <Cabecalhos/funcoesCircuito.h>




// Objetivo: 
int salvarMelhorVolta(MelhorVolta melhorVoltaCadastrar){
	FILE *arquivoMelhoresVoltas = NULL;
	int melhorVoltaJaCadastrada = verificarMelhorVoltaJaCadastrada(melhorVoltaCadastrar), ret = 0;
	Circuito circuitoMelhorVolta;
	
	if(melhorVoltaJaCadastrada == 0){
		fseek(arquivoMelhoresVoltas, 0, SEEK_END);
		melhorVoltaCadastrar.id = ftell(arquivoMelhoresVoltas)/sizeof(MelhorVolta);
		//pilotoCadastrar.id = obtemUltimoIdCadastradoPiloto();
		//pilotoCadastrar.id++;
		
		arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS, "ab");
		if(arquivoMelhoresVoltas == NULL){
			salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'salvarMelhorVolta'\n");
			ret = -2;
		}else{
			if(fwrite(&melhorVoltaCadastrar, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				salvarErro("Erro ao salvar os dados de uma melhor volta de 'salvarMelhorVolta'\n");
				ret = -3;
			}else{
				if(pesquisarCircuitoPId(melhorVoltaCadastrar.idCircuito, &circuitoMelhorVolta) != 1){
					salvarErro("Erro ao pesquisar circuito de uma melhor volta de 'salvarMelhorVolta'\n");
					ret = -4;
				}else{
					if(strcmp(circuitoMelhorVolta.menorTempo, "-") == 0 || (strcmp(circuitoMelhorVolta.menorTempo, melhorVoltaCadastrar.tempo) > 0)){
						strcpy(circuitoMelhorVolta.menorTempo, melhorVoltaCadastrar.tempo);
						circuitoMelhorVolta.idPiloto = melhorVoltaCadastrar.idPiloto;
						if(alterarCircuito(circuitoMelhorVolta) != 0){
							salvarErro("Erro ao alterar circuito de uma melhor volta de 'salvarMelhorVolta'\n");
							ret = -5;
						}
					}
				}
			}
			if(fclose(arquivoMelhoresVoltas) != 0){
				salvarErro("Erro ao fechar arquivo de melhores voltas em 'salvarMelhorVolta'\n");
				ret = -6;
			}
		}
	} else if(melhorVoltaJaCadastrada < 0){
		salvarErro("Erro na funcao 'verificarMelhorVoltaJaCadastrada' de 'salvarMelhorVolta'\n");
		ret = -7;
	}
	
	return ret;
}



int pesquisarMelhorVoltaPId(int idPesquisar, MelhorVolta *melhorVoltaEncontrada){
	FILE *arquivoMelhoresVoltas;
	MelhorVolta melhorVoltaPesquisar;
	int ret = 0;
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'pesquisarMelhorVoltaPId'\n");
		ret = -1;
	}else{
		while(1){
			if(fread(&melhorVoltaPesquisar, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				if(!feof(arquivoMelhoresVoltas)){
					salvarErro("Erro ao ler os dados de uma melhor volta de 'pesquisarMelhorVoltaPId'\n");
					ret = -2;
				}
			}
			if(melhorVoltaPesquisar.id == idPesquisar){				
				*melhorVoltaEncontrada = melhorVoltaPesquisar;
				ret = 1;
				break;
			}
		}
		if(fclose(arquivoMelhoresVoltas) != 0){
			salvarErro("Erro ao fechar arquivo com os dados das melhores voltas de 'pesquisarMelhorVoltaPId'\n");
			ret = -3;
		}
	}
	
	return ret;
}



//Objetivo:
void apresentarMelhoresVoltasPesquisadas(MelhorVolta *melhoresVoltasApresentar, int inicioVetor, int qtdMelhoresVoltas, Componente tabelaDestino, Janela janelaDestino){
  int melhorVoltaAtual = inicioVetor, linhaTabela, qtdLinhas;
	char stringIdMelhorVolta[9], stringIdCircuitoMelhorVolta[9], stringIdPilotoMelhorVolta[9];
	qtdLinhas = tabelaDestino.area.h/tabelaDestino.areaAux.h;
	
	for(linhaTabela = 0; linhaTabela < qtdLinhas; linhaTabela++){
		sprintf(stringIdMelhorVolta, "%-8u", melhoresVoltasApresentar[melhorVoltaAtual].id);
		sprintf(stringIdCircuitoMelhorVolta, "%-8u", melhoresVoltasApresentar[melhorVoltaAtual].idCircuito);
		sprintf(stringIdPilotoMelhorVolta, "%-8u", melhoresVoltasApresentar[melhorVoltaAtual].idPiloto);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 1, stringIdMelhorVolta, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 2, stringIdPilotoMelhorVolta, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 3, stringIdCircuitoMelhorVolta, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 4, melhoresVoltasApresentar[melhorVoltaAtual].nomeEquipe, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 5, melhoresVoltasApresentar[melhorVoltaAtual].data, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 6, melhoresVoltasApresentar[melhorVoltaAtual].tempo, janelaDestino);
		melhorVoltaAtual++;
		if(melhorVoltaAtual >= qtdMelhoresVoltas) break;
	}
}



// Objetivo:
int pesquisarTodasMelhoresVoltas(MelhorVolta **melhoresVoltas){
	FILE *arquivoMelhoresVoltas;
	MelhorVolta melhorVoltaApresentar;
	int linhaTabela = 2, qtdMelhoresVoltas = 0;
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS, "rb");
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'pesquisarTodasMelhoresVoltas'\n");
		qtdMelhoresVoltas = -1;
	}else{
		while(1){
			if(fread(&melhorVoltaApresentar, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				if(!feof(arquivoMelhoresVoltas)){
					salvarErro("Erro ao ler uma melhor volta em 'pesquisarTodasMelhoresVoltas'!");
					qtdMelhoresVoltas = -2;
				}
				break;
			}else{
				*melhoresVoltas = (MelhorVolta *)(realloc(*melhoresVoltas, (qtdMelhoresVoltas+1) * sizeof(MelhorVolta)));
				*(*melhoresVoltas+qtdMelhoresVoltas) = melhorVoltaApresentar;
				qtdMelhoresVoltas++;
			}
		}
		if(fclose(arquivoMelhoresVoltas) != 0){
			salvarErro("Erro ao fechar o arquivo de melhores voltas em 'pesquisarTodasMelhoresVoltas'!");
			qtdMelhoresVoltas = -3;
		}
	}
	
	return qtdMelhoresVoltas;
}



// Objetivo:
int verificarMelhorVoltaJaCadastrada(MelhorVolta melhorVoltaVerificar){
	FILE *arquivoMelhoresVoltas;
	MelhorVolta melhorVoltaPesquisa;
	int melhorVoltaJaCadastrada = 0;
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS, "rb");
	
	fseek(arquivoMelhoresVoltas, 0, SEEK_END);
	if(ftell(arquivoMelhoresVoltas) == 0) return 0;
	fseek(arquivoMelhoresVoltas, 0, SEEK_SET);
	
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'verificarMelhorVoltaJaCadastrada'\n");
		melhorVoltaJaCadastrada -1;
	}else{
		while(!feof(arquivoMelhoresVoltas)){
			if(fread(&melhorVoltaPesquisa, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				salvarErro("Erro ao ler os dados de uma melhor volta de 'verificarMelhorVoltaJaCadastrada'\n");
				melhorVoltaJaCadastrada -2;
			}else{
				if(strcmp(melhorVoltaPesquisa.data, melhorVoltaVerificar.data) == 0 && 
						melhorVoltaPesquisa.idCircuito == melhorVoltaVerificar.idCircuito && 
						melhorVoltaPesquisa.idPiloto == melhorVoltaVerificar.idPiloto && 
						strcmp(melhorVoltaPesquisa.nomeEquipe, melhorVoltaVerificar.nomeEquipe) == 0 && 
						strcmp(melhorVoltaPesquisa.tempo, melhorVoltaVerificar.tempo) == 0){
					melhorVoltaJaCadastrada = 1;
					break;
				}
			}
		}
	}
	fclose(arquivoMelhoresVoltas);
	
	return melhorVoltaJaCadastrada;
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
int alterarMelhorVolta(MelhorVolta melhorVoltaAlterar){
	FILE *arquivoMelhoresVoltas = NULL;
	int ret = 0;
	Circuito circuitoMelhorVolta;
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS, "r+b");
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'alterarMelhorVolta'\n");
		ret = -1;
	} else {
		fseek(arquivoMelhoresVoltas, melhorVoltaAlterar.id * sizeof(MelhorVolta), SEEK_SET);
		if(fwrite(&melhorVoltaAlterar, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
			salvarErro("Erro ao salvar os dados alterados no arquivo de uma melhor volta em 'alterarMelhorVolta'\n");
			ret = -2;
		}else{
			if(pesquisarCircuitoPId(melhorVoltaAlterar.idCircuito, &circuitoMelhorVolta) != 1){
				salvarErro("Erro ao pesquisar circuito de uma melhor volta de 'alterarMelhorVolta'\n");
				ret = -3;
			}else{
				if(strcmp(circuitoMelhorVolta.menorTempo, "-") == 0 || (strcmp(circuitoMelhorVolta.menorTempo, melhorVoltaAlterar.tempo) > 0)){
					strcpy(circuitoMelhorVolta.menorTempo, melhorVoltaAlterar.tempo);
					circuitoMelhorVolta.idPiloto = melhorVoltaAlterar.idPiloto;
					if(alterarCircuito(circuitoMelhorVolta) != 0){
						salvarErro("Erro ao alterar circuito de uma melhor volta de 'alterarMelhorVolta'\n");
						ret = -4;
					}
				}
			}
		}
		if(fclose(arquivoMelhoresVoltas) != 0){
			salvarErro("Erro ao fechar o arquivo das melhores voltas em 'alterarMelhorVolta'\n");
			ret = -5;
		}
	}	
	
	return ret;
}



// Objetivo: 
int excluirMelhorVolta(MelhorVolta melhorVoltaExcluir){
	FILE *arquivoMelhoresVoltas = NULL, *arquivoMelhoresVoltasTemporario = NULL;
	int ret = 0, idAtualMelhorVoltaArquivoTemporario = 0;
	MelhorVolta melhorVoltaTemporaria;
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS, "rb");
	if (arquivoMelhoresVoltas == NULL){
		salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'excluirMelhorVolta'\n");
		ret = 1;
	}
	else{
		arquivoMelhoresVoltasTemporario = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS_TMP, "wb");
		if (arquivoMelhoresVoltasTemporario == NULL){
			salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'excluirMelhorVolta'\n");
			ret = 1;			
		}else{		
			while(!feof(arquivoMelhoresVoltas)){
				if(fread(&melhorVoltaTemporaria, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
					if(!feof(arquivoMelhoresVoltas)){
						salvarErro("Erro ao ler os dados do arquivo de uma melhor volta em 'excluirMelhorVolta'\n");
						ret = 1;
					}
					break;
				}else{
				  if(idAtualMelhorVoltaArquivoTemporario > melhorVoltaExcluir.id){
				    melhorVoltaTemporaria.id = melhorVoltaTemporaria.id - 1;
				  }
					if(idAtualMelhorVoltaArquivoTemporario != melhorVoltaExcluir.id){
						if(fwrite(&melhorVoltaTemporaria, sizeof(MelhorVolta), 1, arquivoMelhoresVoltasTemporario) != 1){
							salvarErro("Erro ao salvar os dados alterados no arquivo temporario de uma melhor volta em 'excluirMelhorVolta'\n");
							ret = 1;
							break;
						}
					}
					idAtualMelhorVoltaArquivoTemporario++;
				}
			}
			if (ret != 0){			
				if(fclose(arquivoMelhoresVoltas) != 0){		
					salvarErro("Erro ao fechar o arquivo de melhores voltas em 'excluirMelhorVolta'\n");
					ret = 1;
				}else{
					if(fclose(arquivoMelhoresVoltasTemporario) != 0){
						salvarErro("Erro ao fechar o arquivo temporario de melhores voltas em 'excluirMelhorVolta'\n");
						ret = 1;
					}else{
						if(remove(LOCAL_ARQUIVO_MELHORES_VOLTAS) != 0){
							salvarErro("Erro ao remover o arquivo de melhores voltas em 'excluirMelhorVolta'\n");
							ret = 1;
						}else{
							if(rename(LOCAL_ARQUIVO_MELHORES_VOLTAS_TMP, LOCAL_ARQUIVO_MELHORES_VOLTAS) != 0){
								salvarErro("Erro ao renomear o arquivo temporario de melhores voltas em 'excluirMelhorVolta'\n");
								ret = 1;
							}
						}
					}
				}			
			}		
		}
	}	
	return ret;
}



MelhorVolta pesquisarMelhorVoltaPCircuito(Circuito circuitoMelhorVoltaPesquisar){
	FILE *arquivoMelhoresVoltas;
	MelhorVolta melhorVoltaPesquisar, melhorVoltaErro;
	int ret = 0;
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	melhorVoltaErro.id = -1;
	melhorVoltaErro.idCircuito = -1;
	melhorVoltaErro.idPiloto = -1;
	strcpy(melhorVoltaErro.data, "ERRO");
	strcpy(melhorVoltaErro.tempo, "ERRO");
	strcpy(melhorVoltaErro.nomeEquipe, "ERRO");
	
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'pesquisarMelhorVoltaPCircuito'\n");
		ret = 1;
	}else{
		while(!feof(arquivoMelhoresVoltas)){
			if(fread(&melhorVoltaPesquisar, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				salvarErro("Erro ao ler os dados de uma melhor volta de 'pesquisarMelhorVoltaPCircuito'\n");
				ret = 1;
			}
			if(melhorVoltaPesquisar.idCircuito == circuitoMelhorVoltaPesquisar.codigo)
				break;
		}
	}
	fclose(arquivoMelhoresVoltas);
	
	return ((ret == 0) ? melhorVoltaPesquisar : melhorVoltaErro);
}



MelhorVolta pesquisarMelhorVoltaPPiloto(Piloto pilotoMelhorVoltaPesquisar){
	FILE *arquivoMelhoresVoltas;
	MelhorVolta melhorVoltaPesquisar, melhorVoltaErro;
	int ret = 0;
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_PILOTOS, "rb");
	melhorVoltaErro.id = -1;
	melhorVoltaErro.idCircuito = -1;
	melhorVoltaErro.idPiloto = -1;
	strcpy(melhorVoltaErro.data, "ERRO");
	strcpy(melhorVoltaErro.tempo, "ERRO");
	strcpy(melhorVoltaErro.nomeEquipe, "ERRO");
	
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'pesquisarMelhorVoltaPCircuito'\n");
		ret = 1;
	}else{
		while(!feof(arquivoMelhoresVoltas)){
			if(fread(&melhorVoltaPesquisar, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				salvarErro("Erro ao ler os dados de uma melhor volta de 'pesquisarMelhorVoltaPCircuito'\n");
				ret = 1;
			}
			if(melhorVoltaPesquisar.idPiloto == pilotoMelhorVoltaPesquisar.id)
				break;
		}
	}
	fclose(arquivoMelhoresVoltas);
	
	return ((ret == 0) ? melhorVoltaPesquisar : melhorVoltaErro);
}



//Objetivo:
int pesquisarMelhoresVoltasEntreDatas(char *nomeEquipePesquisar, char *dataInicio, char *dataFim, MelhorVolta **melhoresVoltasEncontradas){
	FILE *arquivoMelhoresVoltas;
	int qtdMelhoresVoltasEncontradas = 0;
	MelhorVolta melhorVoltaSalva;
	
	Piloto pilotoPesquisar, pilotoErro;
	time_t dataInicioSegundos, dataFimSegundos, dataMelhorVoltaSegundos;
	
	dataInicioSegundos = converteDataPSegundos(dataInicio);
	dataFimSegundos = converteDataPSegundos(dataFim);
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS, "rb");	
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'pesquisarMelhoresVoltasEntreDatas'\n");
		qtdMelhoresVoltasEncontradas = -1;
	}else{
		while(1){
			if(fread(&melhorVoltaSalva, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				if(!feof(arquivoMelhoresVoltas)){
					salvarErro("Erro ao ler os dados de uma melhor volta de 'pesquisarMelhoresVoltasEntreDatas'\n");
					qtdMelhoresVoltasEncontradas = -2;
				}
				break;
			}else{
			  dataMelhorVoltaSegundos = converteDataPSegundos(melhorVoltaSalva.data);
			  if(difftime(dataInicioSegundos, dataMelhorVoltaSegundos) <= 0 && difftime(dataMelhorVoltaSegundos, dataFimSegundos) <= 0 && strcmp(melhorVoltaSalva.nomeEquipe, nomeEquipePesquisar) == 0){
          *melhoresVoltasEncontradas = (MelhorVolta *)(realloc(*melhoresVoltasEncontradas, (qtdMelhoresVoltasEncontradas+1) * sizeof(MelhorVolta)));
          *(*melhoresVoltasEncontradas + qtdMelhoresVoltasEncontradas) = melhorVoltaSalva;
          qtdMelhoresVoltasEncontradas++;
        }
			}
		}
		if(fclose(arquivoMelhoresVoltas) != 0){
			salvarErro("Erro ao fechar arquivo com os dados das melhores voltas de 'pesquisarMelhoresVoltasEntreDatas'\n");
			qtdMelhoresVoltasEncontradas = -3;
		}
	}
	
	return qtdMelhoresVoltasEncontradas;
}



//Objetivo:
int pesquisarMelhoresVoltasMenorQTempo(char *tempoMax, MelhorVolta **melhoresVoltasEncontradas){
	FILE *arquivoMelhoresVoltas;
	int qtdMelhoresVoltasEncontradas = 0;
	MelhorVolta melhorVoltaSalva;
	
	time_t milisegundosTempoMax, tempoMelhorVoltaMilisegundos;
	
	milisegundosTempoMax = converteTempoPMilesimosSegundo(tempoMax);
	
	arquivoMelhoresVoltas = fopen(LOCAL_ARQUIVO_MELHORES_VOLTAS, "rb");	
	if(arquivoMelhoresVoltas == NULL){
		salvarErro("Erro abrir o arquivo com os dados das melhores voltas de 'pesquisarMelhoresVoltasMenorQTempo'\n");
		qtdMelhoresVoltasEncontradas = -1;
	}else{
		while(1){
			if(fread(&melhorVoltaSalva, sizeof(MelhorVolta), 1, arquivoMelhoresVoltas) != 1){
				if(!feof(arquivoMelhoresVoltas)){
					salvarErro("Erro ao ler os dados de uma melhor volta de 'pesquisarMelhoresVoltasMenorQTempo'\n");
					qtdMelhoresVoltasEncontradas = -2;
				}
				break;
			}else{
			  tempoMelhorVoltaMilisegundos = converteTempoPMilesimosSegundo(melhorVoltaSalva.tempo);
			  if(difftime(milisegundosTempoMax, tempoMelhorVoltaMilisegundos) >= 0){
          *melhoresVoltasEncontradas = (MelhorVolta *)(realloc(*melhoresVoltasEncontradas, (qtdMelhoresVoltasEncontradas+1) * sizeof(MelhorVolta)));
          *(*melhoresVoltasEncontradas + qtdMelhoresVoltasEncontradas) = melhorVoltaSalva;
          qtdMelhoresVoltasEncontradas++;
        }
			}
		}
		if(fclose(arquivoMelhoresVoltas) != 0){
			salvarErro("Erro ao fechar arquivo com os dados das melhores voltas de 'pesquisarMelhoresVoltasMenorQTempo'\n");
			qtdMelhoresVoltasEncontradas = -3;
		}
	}
	
	return qtdMelhoresVoltasEncontradas;
}



//Objetivo:
void apresentarRelatorio5(MelhorVolta *melhoresVoltasApresentar, int inicioVetor, int qtdMelhoresVoltas, Componente tabelaDestino, Janela janelaDestino){
  int melhorVoltaAtual = inicioVetor, linhaTabela, qtdLinhas;
	char stringIdPiloto[9];
	Circuito circuitoMelhorVolta;
	Piloto pilotoMelhorVolta;
	qtdLinhas = tabelaDestino.area.h/tabelaDestino.areaAux.h;
	
	for(linhaTabela = 0; linhaTabela < qtdLinhas; linhaTabela++){
		pesquisarPilotoPId(melhoresVoltasApresentar[melhorVoltaAtual].idPiloto, &pilotoMelhorVolta);
		pesquisarCircuitoPId(melhoresVoltasApresentar[melhorVoltaAtual].idCircuito, &circuitoMelhorVolta);
		sprintf(stringIdPiloto, "%-8u", melhoresVoltasApresentar[melhorVoltaAtual].idPiloto);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 1, stringIdPiloto, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 2, pilotoMelhorVolta.nome, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 3, melhoresVoltasApresentar[melhorVoltaAtual].data, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 4, circuitoMelhorVolta.nome, janelaDestino);
		melhorVoltaAtual++;
		if(melhorVoltaAtual >= qtdMelhoresVoltas) break;
	}
}



//Objetivo:
void apresentarRelatorio6(MelhorVolta *melhoresVoltasApresentar, int inicioVetor, int qtdMelhoresVoltas, Componente tabelaDestino, Janela janelaDestino){
  int melhorVoltaAtual = inicioVetor, linhaTabela, qtdLinhas;
	Circuito circuitoMelhorVolta;
	Piloto pilotoMelhorVolta;
	qtdLinhas = tabelaDestino.area.h/tabelaDestino.areaAux.h;
	
	for(linhaTabela = 0; linhaTabela < qtdLinhas; linhaTabela++){
		pesquisarPilotoPId(melhoresVoltasApresentar[melhorVoltaAtual].idPiloto, &pilotoMelhorVolta);
		pesquisarCircuitoPId(melhoresVoltasApresentar[melhorVoltaAtual].idCircuito, &circuitoMelhorVolta);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 1, pilotoMelhorVolta.nome, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 2, circuitoMelhorVolta.nome, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 3, melhoresVoltasApresentar[melhorVoltaAtual].nomeEquipe, janelaDestino);
		pintarDadoTabela(tabelaDestino, (linhaTabela + 2), 4, melhoresVoltasApresentar[melhorVoltaAtual].tempo, janelaDestino);
		melhorVoltaAtual++;
		if(melhorVoltaAtual >= qtdMelhoresVoltas) break;
	}
}


#endif /* _FUNCOES_MELHOR_VOLTA_C_ */
