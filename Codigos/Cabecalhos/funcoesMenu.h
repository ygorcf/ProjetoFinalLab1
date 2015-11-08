#ifndef _FUNCOES_MENU_H_
#define _FUNCOES_MENU_H_


int checarEventoMenuPrincipal(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuPilotos(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuNovoPiloto(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuEscolhePais(char *strDestinoPaisNatal);
int checarEventoMenuDescricaoPiloto(int idPiloto, Janela janelaDestino, Painel painelDestino, int aparecerOpcoes);
int checarEventoMenuAlteraPiloto(Piloto *pilotoAlterar, Janela janelaDestino, Painel painelDestino);
int checarEventoMenuCircuitos(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuNovoCircuito(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuDescricaoCircuito(int idCircuito, Janela janelaDestino, Painel painelDestino, int aparecerOpcoes);
int checarEventoMenuAlteraCircuito(Circuito *circuitoAlterar, Janela janelaDestino, Painel painelDestino);
int checarEventoMenuMelhoresVoltas(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuNovaMelhorVolta(Janela janelaDestino, Painel painelDestino);
int checarEventoMenuEscolhePiloto(char *strDestinoNomePiloto, int *intDestinoIdPiloto);
int checarEventoMenuDescricaoMelhorVolta(int idMelhorVolta, Janela janelaDestino, Painel painelDestino, int aparecerOpcoes);
int checarEventoMenuAlteraMelhorVolta(MelhorVolta *melhorVoltaAlterar, Janela janelaDestino, Painel painelDestino);

#include <CodigosFontes/funcoesMenu.c>

#endif
