#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
  FILE *arqDev, *novoDev;
  char localDev[127], linha[127], novoIncludes[12], novoLibs[127];
  
  printf("===================================\n");
  printf("Local do arquivo .dev do projeto: ");
  fgets(localDev, 127, stdin);
  
  localDev[strlen(localDev)-1] = '\0';
  
  arqDev = fopen(localDev, "r");
  strcat(localDev, "2.dev");
  novoDev = fopen(localDev, "w");
  if(arqDev == NULL){
    printf("ERRO ao abrir o arquivo!!\n");
    exit(1);
  }
  
  while(!feof(arqDev)){
    fgets(linha, 127, arqDev);
    //printf("%s", strstr(linha, "Includes"));
    if(strstr(linha, "Includes=\"") != NULL){
      printf("Novo local dos includes do projeto: ");
      fgets(novoIncludes, 127, stdin);
  
      novoIncludes[strlen(novoIncludes)-1] = '\0';
      strcpy(linha, "Includes=\"");
      strcat(linha, novoIncludes);
      if(linha[strlen(linha)-1] != '\\')strcat(linha, "\\\n");
      strcat(linha, "\"\n");
    }
    if(strstr(linha, "Libs=\"") != NULL){
      printf("Novo local dos libs do projeto: ");
      fgets(novoLibs, 127, stdin);
  
      novoLibs[strlen(novoLibs)-1] = '\0';
      strcpy(linha, "Libs=\"");
      strcat(linha, novoLibs);
      strcat(linha, "\"\n");
    }
    fputs(linha, novoDev);
  }
  
  printf("===================================\n");  
  return 0;
}
