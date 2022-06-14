#ifndef PROCESSO_H
#define PROCESSO_H

#include "../EstadoProcesso/EstadoProcesso.h"

typedef struct Processo {
    signed int pid;
    signed int pid_pai;
    char estado[15];
    unsigned int prioridade;
    unsigned int tempo_inicializacao;
    unsigned int cota_cpu;
    EstadoProcesso estado_processo;
} Processo;

void imprimir_processo(Processo*);

#endif // PROCESSO_H