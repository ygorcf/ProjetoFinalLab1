#ifndef _FUNCOES_CIRCUITO_H_
#define _FUNCOES_CIRCUITO_H_

int salvarCircuito(Circuito circuitoCadastrar);
int apresentarTodosCircuitos(Componente tabelaDestino, Janela janelaDestino);
int verificarCircuitoJaCadastrado(Circuito circuitoVerificar);
int alterarCircuito(Circuito circuitoAlterar);

#include <CodigosFontes/funcoesCircuito.c>

#endif /* _FUNCOES_CIRCUITO_H_ */
