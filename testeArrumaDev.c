#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(void){
  FILE *arqDev, *novoDev;
  //char localDev[127], linha[127], novoIncludes[12], novoLibs[127];
  char linha[255], novoIncludes[127], novoLibs[127], nomeDev[127];
  int x;
  
	int tamTextDir = GetCurrentDirectory(0, NULL);
	char *dir, *localDev;
	dir = (char *)(malloc(tamTextDir * sizeof(char)));
	GetCurrentDirectory(tamTextDir, dir);
	strcat(dir, "\\");
  
  printf("===================================\n");
  /*printf("Local do arquivo .dev do projeto: ");
  fgets(localDev, 127, stdin);
  printf("Nome do arquivo .dev do projeto: ");
  fgets(nomeDev, 127, stdin);*/
  
  memset(nomeDev, '\0', sizeof(nomeDev));
  strcpy(nomeDev, "dadosDev");
  printf("%s\n", nomeDev);
  
  //localDev[strlen(localDev)-1] = '\0';
	localDev = (char *)(malloc((tamTextDir+strlen(nomeDev)) * sizeof(char)));
  memset(localDev, '\0', sizeof(localDev));
  strcat(localDev, nomeDev);
  
  for(x = 0; x < strlen(localDev); x++)
  	if(localDev[x] == '\\') localDev[x] = '/';
  
  arqDev = fopen(localDev, "r");
  strcpy(localDev, dir);
  strcat(localDev, "projetoFinal.dev");
  novoDev = fopen(localDev, "w");
  printf("1\n");
  if(arqDev == NULL){
    printf("ERRO ao abrir o arquivo!!\n");
    exit(1);
  }
  
  printf("1\n");
  while(!feof(arqDev)){
    fgets(linha, 127, arqDev);
    //printf("%s", strstr(linha, "Includes"));
    if(strstr(linha, "Includes=\"") != NULL){
      /*printf("Novo local dos includes do projeto: ");
      fgets(novoIncludes, 127, stdin);
  
      novoIncludes[strlen(novoIncludes)-1] = '\0';*/
      strcpy(linha, "Includes=\"");
      strcat(linha, dir);
      strcat(linha, "include\\\";\"");
      strcat(linha, dir);
      strcat(linha, "Codigos\\\"\n");
      //if(linha[strlen(linha)-1] != '\\')strcat(linha, "\\\n");
      //strcat(linha, "\"\n");
      
    }
    if(strstr(linha, "Libs=\"") != NULL){
      /*printf("Novo local dos libs do projeto: ");
      fgets(novoLibs, 127, stdin);
  
      novoLibs[strlen(novoLibs)-1] = '\0';*/
      strcpy(linha, "Libs=\"");
      strcat(linha, dir);
      strcat(linha, "lib\\\"\n");
    }
    fputs(linha, novoDev);
  }
  
  printf("===================================\n"); 
	//system("PAUSE"); 
  return 0;
}
