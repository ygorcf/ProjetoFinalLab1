#ifndef _FUNCOES_PILOTO_H_
#define _FUNCOES_PILOTO_H_

//void alocarPiloto(Piloto *pilotoAlocar);
int salvarPiloto(Piloto pilotoCadastrar);
Piloto pesquisarPiloto(int idPesquisar);
int apresentarTodosPilotos(Componente tabelaDestino, Janela janelaDestino);
int verificarPilotoJaCadastrado(Piloto pilotoVerificar);
int obtemUltimoIdCadastradoPiloto();
int alterarPiloto(Piloto pilotoAlterar);
int excluirPiloto(Piloto pilotoExcluir);

#include <CodigosFontes/funcoesPiloto.c>

#endif /* _FUNCOES_PILOTO_H_ */
