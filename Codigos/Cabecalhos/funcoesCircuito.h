#ifndef _FUNCOES_CIRCUITO_H_
#define _FUNCOES_CIRCUITO_H_

int salvarCircuito(Circuito circuitoCadastrar);
int pesquisarCircuitoPId(int idPesquisar, Circuito *circuitoEncontrado);
int apresentarTodosCircuitos(Componente tabelaDestino, Janela janelaDestino);
int verificarCircuitoJaCadastrado(Circuito circuitoVerificar);
int alterarCircuito(Circuito circuitoAlterar);
int ordenarCircuitoNome(const void * circuito1, const void * circuito2);

#include <CodigosFontes/funcoesCircuito.c>

#endif /* _FUNCOES_CIRCUITO_H_ */
