#ifndef _FUNCOES_PILOTO_H_
#define _FUNCOES_PILOTO_H_

int salvarPiloto(Piloto pilotoCadastrar);
int pesquisarPilotoPId(int idPesquisar, Piloto *pilotoEncontrado);
int pesquisarPilotoPNome(char *nomePesquisar, Piloto **pilotosEncontrados);
void apresentarPilotosPesquisados(Piloto *pilotosApresentar, int qtdPilotos, Componente tabelaDestino, Janela janelaDestino);
int apresentarTodosPilotos(Componente tabelaDestino, Janela janelaDestino);
int verificarPilotoJaCadastrado(Piloto pilotoVerificar);
int obtemUltimoIdCadastradoPiloto();
int alterarPiloto(int idAntigo, Piloto pilotoAlterar);
int excluirPiloto(Piloto pilotoExcluir);
int ordenarPilotoNome(const void * piloto1, const void * piloto2);

#include <CodigosFontes/funcoesPiloto.c>

#endif /* _FUNCOES_PILOTO_H_ */
