#include "ExecutorInstrucoes.h"

#include <stdio.h>
#include <stdlib.h>

void executar_instrucao(Tempo *tempo, CPU *cpu, EstadoEmExecucao *exec, TabelaPCB *pcb, 
                      EstadoPronto *ep, EstadoBloqueado *eb, Processo *proc) {
    FILE *arq;
    char comando;
    ConjuntoInstrucoes instrucoes;
    
    Processo novo_proc;



}