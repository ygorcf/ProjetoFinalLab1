#ifndef _INICIA_TERMINA_H_
#define _INICIA_TERMINA_H_

#ifndef _SDL_H
#include <SDL2/SDL.h>
#endif
#ifndef _SDL_TTF_H
#include <SDL2/SDL_ttf.h>
#endif

int inicializarTudo(FILE *arquivoErros);
void finalizarTudo(FILE *arquivoErros);

#include <CodigosFontes/iniciaTermina.c>

#endif
