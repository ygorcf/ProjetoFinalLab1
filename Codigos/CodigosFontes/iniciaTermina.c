#ifndef _INICIA_TERMINA_C_
#define _INICIA_TERMINA_C_



// Objetivo: Inicializar tudo que sera necessario
// Parametro: Um ponteiro FILE que aponta para o arquivo onde sera salvo os 
//						 erros
// Retorno: 0 - Se tudo foi executado com succeso
//					1 - Se ocorreu um erro
int inicializarTudo(FILE *arquivoErros){
	// Inicializa a SDL_2 e verifica se ocorreu um erro
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		fprintf(arquivoErros, 
						"Erro na funcao 'SDL_Init' de 'inicializarTudo': %s\n", 
						SDL_GetError());
		return 1;
	}
    
  // Inicializa a SDL_TTF_2 e verifica se ocorreu um erro
	if(TTF_Init() != 0){
		fprintf(arquivoErros, 
						"Erro na funcao 'TTF_Init' de 'inicializarTudo': %s\n", 
						TTF_GetError());
		return 1;
	}
	
	return 0;
}



// Objetivo: Finalizar tudo que sera necessario
// Parametro: Um ponteiro FILE que aponta para o arquivo onde
//					 sera salvo os erros
void finalizarTudo(FILE *arquivoErros){
	// Fecha o arquivo de erros e verifica se ocorreu um erro
	if(fclose(arquivoErros) != 0){
		// Se ocorrer um erro encerra a execucao do programa
		exit(1);
	}
	
	// Finaliza a SDL_TTF_2
	TTF_Quit();
	// Finaliza a SDL_2
  SDL_Quit();
}
#endif
