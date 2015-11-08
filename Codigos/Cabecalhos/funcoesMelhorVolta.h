#ifndef _FUNCOES_MELHOR_VOLTA_H_
#define _FUNCOES_MELHOR_VOLTA_H_

int salvarMelhorVolta(MelhorVolta melhorVoltaCadastrar);
MelhorVolta pesquisarMelhorVolta(int idPesquisar);
void apresentarMelhoresVoltasPesquisadas(MelhorVolta *melhoresVoltasApresentar, int qtdMelhoresVoltas, Componente tabelaDestino, Janela janelaDestino);
int pesquisarTodasMelhoresVoltas(MelhorVolta **melhoresVoltas);
int verificarMelhorVoltaJaCadastrada(MelhorVolta melhorVoltaVerificar);
//int obtemUltimoIdCadastradoPiloto();
int alterarMelhorVolta(MelhorVolta melhorVoltaAlterar);
int excluirMelhorVolta(MelhorVolta melhorVoltaExcluir);
MelhorVolta pesquisarMelhorVoltaPCircuito(Circuito circuitoMelhorVoltaPesquisar);
MelhorVolta pesquisarMelhorVoltaPPiloto(Piloto pilotoMelhorVoltaPesquisar);

#include <CodigosFontes/funcoesMelhorVolta.c>

#endif /* _FUNCOES_MELHOR_VOLTA_H_ */
