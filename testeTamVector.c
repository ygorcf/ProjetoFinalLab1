// Aluno: Ygor Cruz

/*
  Objetivo:
  
  Entrada:
  
  Saida:
*/

#include <stdio.h>
#include <conio.c>

int main(void){
	int *x;
	x = (int *)(malloc(23 * sizeof(int)));
	printf("%d\n\n", sizeof(x)/sizeof(int));
	
	system("PAUSE");
	return 0;
}

