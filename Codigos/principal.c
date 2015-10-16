// Aluno: Ygor Cruz e Gustavo Arthur

/*
  Objetivo: Gerenciar os testes realizados na Formula 1
  
  Entrada:
  
  Saida:
*/

#include <stdio.h>
#include <conio.c>

#include "includesProjeto.h"

int main(int argc, char* args[]){
	FILE *arqErros;
	arqErros = criaArquivoErros("errosProjeto.txt");
	inicializarTudo(arqErros);
	
	Janela janela;
	Painel painel;
	Fonte fonte;
	Superficie superficie;
	Textura textura;
	Retangulo retangulo;
	Cor corFonte;
	int sair = 0, copiouTextura = 1;
	
	corFonte.r = 178;
	corFonte.g = 34;
	corFonte.b = 34;
	corFonte.opacidade = 255;
	
	
	janela = criarJanela(arqErros, "Minha janela", 560, 480);
	painel = criarPainel(arqErros, janela);
	fonte = abrirFonte(arqErros, "Ubuntu-M.ttf", 16);
	superficie = textoParaSuperficie(arqErros, fonte, "Ola mundo!", corFonte);
	
	retangulo.x = 0;
	retangulo.y = 0;
	retangulo.h = superficie->h;
	retangulo.w = superficie->w;
	
	textura = superficieParaTextura(arqErros, painel, superficie);
	limparSuperficie(superficie);
	copiouTextura = copiarTexturaPainel(arqErros, painel, textura, retangulo);
	/*---------------*/
	
	superficie = textoParaSuperficie(arqErros, fonte, "Limpar", corFonte);
	
	retangulo.x = 0;
	retangulo.y = 16;
	retangulo.h = superficie->h;
	retangulo.w = superficie->w;
	
	textura = superficieParaTextura(arqErros, painel, superficie);
	limparSuperficie(superficie);
	copiouTextura = copiarTexturaPainel(arqErros, painel, textura, retangulo);
	
	atualizarPainel(painel);
	
	SDL_Event event; //um evento enviado pela SDL
    while(!sair) //rodar enquanto nao for para encerrar :)
    {
        while(SDL_PollEvent(&event)) //checar eventos
        {
            if(event.type == SDL_QUIT) //fechar a janela?
            {
                sair = 1; //sair do loop principal
            }
            if(event.type == SDL_MOUSEBUTTONUP) //fechar a janela?
            {
            	SDL_Point posMouse;
                SDL_GetMouseState(&posMouse.x, &posMouse.y);
                if(pontoDentroRetangulo(&posMouse, &retangulo)){
                	SDL_DestroyRenderer(painel);
                	painel = criarPainel(arqErros, janela);
									SDL_RenderPresent(painel);
                	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Limpando Tela", "Tela Limpa!", janela);
								}
            }
        }
        //SDL_Delay(3000);
				SDL_RenderPresent(painel);
        //SDL_Flip(screen); //atualizar a tela
        //SDL_UpdateWindowSurface(janela);
    }
	
		
	finalizarTudo(arqErros);
	return 0;
}



int pontoDentroRetangulo(SDL_Point *ponto, SDL_Rect *rect){
	if((ponto->x <= (rect->w+rect->x) && ponto->x >= rect->x) && 
			(ponto->y <= (rect->h+rect->y) && ponto->y >= rect->y)) return 1;
	return 0;
}
