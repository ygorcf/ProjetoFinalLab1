#ifndef _FUNCOES_CIRCUITO_H_
#define _FUNCOES_CIRCUITO_H_

int salvarCircuito(Circuito circuitoCadastrar);
int pesquisarCircuitoPId(int idPesquisar, Circuito *circuitoEncontrado);
void apresentarCircuitosPesquisados(Circuito *circuitosApresentar, int inicioVetor, int qtdCircuitos, Componente tabelaDestino, Janela janelaDestino);
int pesquisarTodosCircuitos(Circuito **circuitos);
int verificarCircuitoJaCadastrado(Circuito circuitoVerificar);
int alterarCircuito(Circuito circuitoAlterar);
int pesquisarCircuitoPNome(char *nomePesquisar, Circuito **circuitosEncontrados);
int ordenarCircuitoNome(const void * circuito1, const void * circuito2);

#include <CodigosFontes/funcoesCircuito.c>

#endif /* _FUNCOES_CIRCUITO_H_ */
