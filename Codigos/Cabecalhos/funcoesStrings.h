#ifndef _FUNCOES_STRINGS_H_
#define _FUNCOES_STRINGS_H_

#include <stdio.h>
#include <stdlib.h>

char *rTirarCaracter(char *stringTirarCaracter);
char *rRemoveQuebraLinha(char *stringTirarQuebraLinha);
time_t converteDataPSegundos(char *data);
time_t converteTempoPMilesimosSegundo(char *tempo);
int strENumero(char *strVerificar);
int validaCamposBrancos(int qtdCampos, ... );

#include <CodigosFontes/funcoesStrings.c>

#endif /* _FUNCOES_STRINGS_H_ */
