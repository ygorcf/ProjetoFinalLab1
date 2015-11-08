#ifndef _FUNCOES_MELHOR_VOLTA_H_
#define _FUNCOES_MELHOR_VOLTA_H_

int salvarMelhorVolta(MelhorVolta melhorVoltaCadastrar);
int pesquisarMelhorVoltaPId(int idPesquisar, MelhorVolta *melhorVoltaEncontrada);
void apresentarMelhoresVoltasPesquisadas(MelhorVolta *melhoresVoltasApresentar, int inicioVetor, int qtdMelhoresVoltas, Componente tabelaDestino, Janela janelaDestino);
int pesquisarTodasMelhoresVoltas(MelhorVolta **melhoresVoltas);
int verificarMelhorVoltaJaCadastrada(MelhorVolta melhorVoltaVerificar);
//int obtemUltimoIdCadastradoPiloto();
int alterarMelhorVolta(MelhorVolta melhorVoltaAlterar);
int excluirMelhorVolta(MelhorVolta melhorVoltaExcluir);
MelhorVolta pesquisarMelhorVoltaPCircuito(Circuito circuitoMelhorVoltaPesquisar);
MelhorVolta pesquisarMelhorVoltaPPiloto(Piloto pilotoMelhorVoltaPesquisar);
int pesquisarMelhoresVoltasEntreDatas(char *nomeEquipePesquisar, char *dataInicio, char *dataFim, MelhorVolta **melhoresVoltasEncontradas);
int pesquisarMelhoresVoltasMenorQTempo(char *tempoMax, MelhorVolta **melhoresVoltasEncontradas);
void apresentarRelatorio5(MelhorVolta *melhoresVoltasApresentar, int inicioVetor, int qtdMelhoresVoltas, Componente tabelaDestino, Janela janelaDestino);

#include <CodigosFontes/funcoesMelhorVolta.c>

#endif /* _FUNCOES_MELHOR_VOLTA_H_ */
