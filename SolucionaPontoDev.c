#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(void){
  FILE *arqDev, *novoDev;
  char linha[255], novoIncludes[127], novoLibs[127], nomeDev[127];
  int erro = 0;
  
  printf("===================================\n");
  system("color 0a");
	int tamTextDir = GetCurrentDirectory(0, NULL);
	char *dir, *localDev;
	dir = (char *)(malloc(tamTextDir * sizeof(char)));
	GetCurrentDirectory(tamTextDir, dir);
	strcat(dir, "\\");
	printf("- Diretorio atual encontrado com sucesso!\n  %s\n", dir);
  
  memset(nomeDev, '\0', sizeof(nomeDev));
  strcpy(nomeDev, "dadosDev");
  printf("- Arquivo Pre-configurado:\n  %s\n", nomeDev);
  /*
  for(x = 0; x < strlen(localDev); x++)
  	if(localDev[x] == '\\') localDev[x] = '/';
  */
  if((arqDev = fopen(nomeDev, "r")) == NULL){
  	system("color 0c");
    printf("\n**** ERRO ao abrir o arquivo pre-configurado!! ****\n");
    erro = 1;
	}
  
	localDev = (char *)(malloc((tamTextDir+strlen(nomeDev)) * sizeof(char)));
  memset(localDev, '\0', sizeof(localDev));
  strcpy(localDev, dir);
  strcat(localDev, "projetoFinal.dev");
  if((novoDev = fopen(localDev, "w")) == NULL){
  	system("color 0c");
    printf("\n**** ERRO ao abrir o novo arquivo!! ****\n");
    erro = 1;
	}
  
  while(!feof(arqDev) && erro != 1){
    fgets(linha, 127, arqDev);
    if(strstr(linha, "Includes=\"") != NULL){
      strcpy(linha, "Includes=\"");
      strcat(linha, dir);
      strcat(linha, "include\\\";\"");
      strcat(linha, dir);
      strcat(linha, "Codigos\\\"\n");
      printf("- Alterado com sucesso linha dos includes!\n");
    }else if(strstr(linha, "Libs=\"") != NULL){
      strcpy(linha, "Libs=\"");
      strcat(linha, dir);
      strcat(linha, "lib\\\"\n");
      printf("- Alterado com sucesso linha dos libs!\n");
    }
    fputs(linha, novoDev);
  }
  fclose(arqDev);
  fclose(novoDev);
  printf("\n===================================\n"); 
  
  if(erro == 1)
    printf("\n**** ERRO ao criar o arquivo .dev!!! ****\n");
	else
	printf("\n- Arquivo .dev criado com SUCESSO!\n");
  
  printf("\n===================================\n"); 
  printf("\nPressione uma tecla...\n\n");
  getch();
  return 0;
}
