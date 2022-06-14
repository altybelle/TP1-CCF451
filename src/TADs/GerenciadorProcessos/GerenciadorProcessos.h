#ifndef GERENCIADOR_PROCESSOS_H_
#define GERENCIADOR_PROCESSOS_H_

#include "../Processo/Processo.h"
#include "../EstadoPronto/EstadoPronto.h"
#include "../EstadoBloqueado/EstadoBloqueado.h"
#include "../Programa/Programa.h"

typedef struct Tempo {
    unsigned int tempo;
    unsigned int quantidade_processos;
} Tempo;

typedef struct CPU {
    Programa prog;
    int contador_programa;
    int *valor_inteiro;
    int espaco_alocado;
    int quantidade_inteiros;
    int parcela_tempo;
    int parcela_tempo_utilizada;
} CPU;

typedef struct EstadoEmExecucao {
    int indice_tabela_pcb;
} EstadoEmExecucao;

void exec();
void exec2();
void imprimir_CPU(CPU*);

#endif // GERENCIADOR_PROCESSOS_H_