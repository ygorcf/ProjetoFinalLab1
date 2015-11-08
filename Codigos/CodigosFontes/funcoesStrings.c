#ifndef _FUNCOES_STRINGS_C_
#define _FUNCOES_STRINGS_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
//#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


/*
// Objetivo: Criar uma string formatada
// Parametro: O formato que vai ficar a string e os dados necessarios no formato
// Retorno: Um ponteiro para a string formatada
char *rsprintf(char *dst, char *formato, ...){
	//dst = (char *)malloc(strlen(formato) * sizeof(char));
	//memset(dst, '\0', sizeof(dst));
	vsprintf(dst, formato, dadosNecessarios);
	va_end(dadosNecessarios);
	return dst;
}*/



// Objetivo: Diminuir um caracter da string
// Parametro: O endereco da string que ira ser retirado o caracter
// Retorno: Um ponteiro para a nova string
char *rTirarCaracter(char *stringTirarCaracter){
	stringTirarCaracter[strlen(stringTirarCaracter)-1] = '\0';
	return stringTirarCaracter;
}



// Objetivo: Retirar o quebrador de linhas no final da string
// Parametro: O endereco da string que ira ser retirado o quebrador de linha
// Retorno: Um ponteiro para a nova string
char *rRemoveQuebraLinha(char *stringTirarQuebraLinha){
	if(stringTirarQuebraLinha[strlen(stringTirarQuebraLinha)-1] == '\n')
		rTirarCaracter(stringTirarQuebraLinha);
	return stringTirarQuebraLinha;
}



// Objetivo: 
time_t converteDataPSegundos(char *data){
  int dia = atoi(strtok(data, "/"));
  int mes = atoi(strtok(NULL, "/"));
  int ano = atoi(strtok(NULL, "/"));
  time_t segundosData;
  struct tm dataTm;
  dataTm.tm_mday = dia;
  dataTm.tm_mon = mes;
  dataTm.tm_year = ano;
  dataTm.tm_min = 0;
  dataTm.tm_sec = 0;
  dataTm.tm_hour = 0;
  
  if((segundosData = mktime(&dataTm)) == -1)
    salvarErro("Erro ao converter data para segundos em 'converteParaSegundos'\n");
  
  return segundosData;
}



// Objetivo: 
time_t converteTempoPMilesimosSegundo(char *tempo){
  int minutos = atoi(strtok(tempo, ":"));
  int segundos = atoi(strtok(NULL, "'"));
  int milesimos = atoi(strtok(NULL, "'"));
  
	time_t segundosTempo = (minutos * 60 * 1000) + milesimos + (segundos * 1000);
  
	return segundosTempo;
}



// Objetivo: 
int strENumero(char *strVerificar){
  int ret = 1, posicaoStr;
  
  for(posicaoStr = 0; posicaoStr < strlen(strVerificar); posicaoStr++){
    if(!isdigit(strVerificar[posicaoStr])){
      ret = 0;
      break;
    }
  }
  
  return ret;
}
// Objetivo: Validar todos os campos, para ver se estão vazios.
// Parâmetros: Endereço da memória que contenha a string de 1 campo e se desejar, mais endereços que contenham strings de outros campos.
// Retorno: 1(inválido) ou 0(válido).
int validaCamposBrancos(int qtdCampos, ... ){
	va_list campos;
	va_start(campos, qtdCampos);
	char *tmp = (char *)malloc(127 * sizeof(char));
	int x = 0, ret = 1;
	
	while (x < qtdCampos){
		tmp = va_arg(campos, char*);
		if(strlen(tmp) < 1){
			ret = 0;
			break;
		}
		x++;
	}
	va_end(campos);
	
	return ret;  
}

#endif /* _FUNCOES_STRINGS_C_ */
