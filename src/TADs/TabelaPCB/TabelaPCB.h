#ifndef TABELA_PCB_H_
#define TABELA_PCB_H_

#include "../Processo/Processo.h"

typedef struct TabelaPCB {
    Processo proc;
    struct TabelaPCB *proximo;
} TabelaPCB;


void insere_pcb(TabelaPCB**, Processo); /* Insere na fila */
TabelaPCB *remover_pcb(TabelaPCB**); /* Remove item da fila */
void imprimir_pcb(TabelaPCB*); /* Imprime a fila */ 

#endif // TABELA_PCB_H_
