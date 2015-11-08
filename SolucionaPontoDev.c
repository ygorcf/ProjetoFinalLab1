// Aluno: Ygor Cruz

/*
  Objetivo: Criar Arquivo .dev com as configuracoes do projeto final
  
  Entrada: Nenhuma
  
  Saida: Informacoes sobre o que esta sendo executado e se o arquivo .dev foi criado com 
					sucesso ou nao
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

int main(void){
  FILE *arqDadosDev, *novoDev;
  char linha[255], novoIncludes[127], novoLibs[127], nomeDev[127], *dir, *localDev;
  int erro = 0, tamTextDir = GetCurrentDirectory(0, NULL);
	
  system("color 0a");
  printf("===================================\n");
	dir = (char *)(malloc(tamTextDir * sizeof(char)));
	GetCurrentDirectory(tamTextDir, dir);
	strcat(dir, "\\");
	printf("- Diretorio atual encontrado com sucesso!\n  %s\n", dir);
  
  memset(nomeDev, '\0', sizeof(nomeDev));
  strcpy(nomeDev, dir);
  strcat(nomeDev, "dadosDev");
  printf("- Arquivo Pre-configurado:\n  %s\n", nomeDev);
  
	arqDadosDev = fopen("dadosDev", "r");
	
  if(arqDadosDev == NULL){
  	system("color 0c");
    printf("\n**** ERRO ao abrir o arquivo pre-configurado!! ****\n");
    erro = 1;
	}
	
	localDev = (char *)(malloc((tamTextDir+20) * sizeof(char)));
  memset(localDev, '\0', sizeof(localDev));
  strcpy(localDev, dir);
  strcat(localDev, "projetoFinal.dev");
  novoDev = fopen(localDev, "w");
  if(novoDev == NULL){
  	system("color 0c");
    printf("\n**** ERRO ao abrir o novo arquivo!! ****\n");
    erro = 1;
	}
	
  while(!feof(arqDadosDev) && erro != 1){
    fgets(linha, 127, arqDadosDev);
    if(strncmp(linha, "Includes=", 9) == 0){
      strcpy(linha, "Includes=\"");
      strcat(linha, dir);
      strcat(linha, "include\";\"");
      strcat(linha, dir);
      strcat(linha, "Codigos\"\n");
      printf("- Alterado com sucesso linha dos includes!\n");
    }else if(strncmp(linha, "Libs=", 5) == 0){
      strcpy(linha, "Libs=\"");
      strcat(linha, dir);
      strcat(linha, "lib\"\n");
      printf("- Alterado com sucesso linha dos libs!\n");
    }
    fputs(linha, novoDev);
  }
  fclose(arqDadosDev);
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

