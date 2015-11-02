#ifndef _FUNCOES_MENU_H_
#define _FUNCOES_MENU_H_


int checarEventoMenuPrincipal(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuPilotos(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuNovoPiloto(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuEscolhePais(char *strDestinoPaisNatal);
int checarEventoMenuDescricaoPiloto(int idPiloto, Janela janelaDestino, Painel painelDestino);
int checarEventoMenuAlteraPiloto(Piloto *pilotoAlterar, Janela janelaDestino, Painel painelDestino);
int checarEventoMenuCircuitos(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuNovoCircuito(Janela janelaDestino, Painel painelDestino);

#include <CodigosFontes/funcoesMenu.c>

#endif
