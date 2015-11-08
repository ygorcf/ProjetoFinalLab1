#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned int id;
	char nome[255];
	unsigned int idade;
	char sexo;
	char paisOrigem[255];
} Piloto;

int main(void){
  Piloto *variosPilotos = NULL;
  variosPilotos = (Piloto *)(realloc(variosPilotos, 2));
  printf("FOI\n");
  return 0;
}
