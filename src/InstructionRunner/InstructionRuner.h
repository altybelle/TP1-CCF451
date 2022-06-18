#ifndef RODAINSTRUCAO_H
#define RODAINSTRUCAO_H
#include "../Process_Manager/ProcessManager.h"
//Criei mais esse .h pois n sabia onde implementar a funcao para simular execução em cpu de instrucao.
void RodaInstrucao(Cpu *cpu, Time *time, EstadoEmExec *estadoexec, PcbTable *pcbTable, EstadoBloqueado *estadobloqueado, EstadoPronto *estadopronto, Processo *processo);
#endif
