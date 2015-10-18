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
	
	
	janela = criarJanela("Minha janela", 560, 480);
	painel = criarPainel(janela);
	fonte = abrirFonte("Ubuntu-M.ttf", 16);
	
	pintarTextoPainel("Ola mundo!", painel, 0, 0, fonte, corFonte);
	/*---------------*/
	
	char inputText[255] = {"Some Text!"};
	Componente compSomeText;
	compSomeText = pintarTextoPainel(inputText, painel, 0, 32, fonte, corFonte);
		
	pintarTextoPainel("Digitar...", painel, 0, 16, fonte, corFonte);
	retangulo = compSomeText.area;
	retangulo.x = (retangulo.x - 10 > 0) ? retangulo.x - 10 : retangulo.x;
	retangulo.y = (retangulo.y - 10 > 0) ? retangulo.y - 10 : retangulo.y;
	retangulo.w = (retangulo.w + 10 > 0) ? retangulo.w + 10 : retangulo.w;
	retangulo.h = (retangulo.h + 10 > 0) ? retangulo.h + 10 : retangulo.h;
	
	Cor corBorda = {0,100,0,255};
	Cor corFundo = {255,255,255,255};
	
	//pintarRetanguloCBordasPainel(100, 100, 100, 100, 10, corBorda, corFundo, painel);
	Componente tabela;
	tabela = pintarTabelaPainel(10, 100, 540, 300, 1, corBorda, corFundo, 5, 5, painel);
	//printf("2\n");
	pintarDadoTabela(tabela, 1, 1, 5, "Radouken!", fonte, corFonte);
	pintarDadoTabela(tabela, 3, 4, 5, "CHUPA!", fonte, corFonte);
	pintarDadoTabela(tabela, 3, 5, 5, "PAO", fonte, corFonte);
	pintarDadoTabela(tabela, 4, 5, 5, "DE", fonte, corFonte);
	pintarDadoTabela(tabela, 5, 5, 5, "BATATA", fonte, corFonte);
	//SDL_RenderDrawRect(painel, &retangulo);
	atualizarPainel(painel);
	
	SDL_StartTextInput();
	SDL_Event event; //um evento enviado pela SDL
    while(!sair) //rodar enquanto nao for para encerrar :)
    {
    	int renderText = 0;
        while(SDL_PollEvent(&event)) //checar eventos
        {
        	//printf("%d\n", event.type);
            if(event.type == SDL_QUIT) //fechar a janela?
            {
                sair = 1; //sair do loop principal
            }
            else if(event.type == SDL_MOUSEBUTTONUP) //fechar a janela?
            {
            	SDL_Point posMouse;
                SDL_GetMouseState(&posMouse.x, &posMouse.y);
                if(pontoDentroRetangulo(&posMouse, &compSomeText.area)){
                	
									SDL_DestroyRenderer(painel);
                	painel = criarPainel(janela);
									SDL_RenderPresent(painel);
                	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Limpando Tela", "Tela Limpa!", janela);
									
									printf("Pronto para digitar texto\n");
								}
            }
						if( event.type == SDL_KEYDOWN )
                    {
                        //Handle backspace
                        if( event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0 )
                        {
                            //lop off character
                            //inputText.pop_back();
                            rTirarCaracter(inputText);
                            char strAux[strlen(inputText)];
                            memset(strAux, ' ', sizeof(strAux));
                            pintarTextoPainel(strAux, painel, 0, 16, fonte, corFonte);
														atualizarPainel(painel);
                            renderText = 1;
                        }
                        /*//Handle copy
                        else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                        {
                            SDL_SetClipboardText( inputText );
                            printf("COPY\n");
                        }
                        //Handle paste
                        else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
                        {
                            strcpy(inputText, SDL_GetClipboardText());
                            renderText = 1;
                            printf("PASTE\n");
                        }*/
                    }
										if( event.type == SDL_TEXTINPUT )
		                    {
		                        //Not copy or pasting
		                        if( !( ( event.text.text[ 0 ] == 'c' || event.text.text[ 0 ] == 'C' ) && ( event.text.text[ 0 ] == 'v' || event.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
		                        {
		                            //Append character
		                            strcat(inputText, event.text.text);
		                            printf("%s", inputText);
		                            renderText = 1;
                            		printf("APPEND CHAR\n");
		                        }
		                    }
        }
        
                if( renderText )
                {
                    //Text is not empty
                    if( inputText != "" )
                    {
                        //Render new text
                        compSomeText = pintarTextoPainel(inputText, painel, 0, 32, fonte, corFonte);
												printf("RENDER NEW TEXT\n");
                    }
                    //Text is empty
                    else
                    {
                        //Render space texture
                        compSomeText = pintarTextoPainel(" ", painel, 0, 32, fonte, corFonte);
                        printf("RENDER SPACE\n");
                    }
                }
        //SDL_Delay(3000);
				SDL_RenderPresent(painel);
        //SDL_Flip(screen); //atualizar a tela
        //SDL_UpdateWindowSurface(janela);
    }
	
            SDL_StopTextInput();
		
	finalizarTudo(arqErros);
	return 0;
}



int pontoDentroRetangulo(SDL_Point *ponto, SDL_Rect *rect){
	if((ponto->x <= (rect->w+rect->x) && ponto->x >= rect->x) && 
			(ponto->y <= (rect->h+rect->y) && ponto->y >= rect->y)) return 1;
	return 0;
}
