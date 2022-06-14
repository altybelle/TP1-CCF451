#include "../Processo/Processo.h"

#ifndef ESTADO_PRONTO_H_
#define ESTADO_PRONTO_H_

typedef struct EstadoPronto {
    Processo proc;
    struct EstadoPronto *proximo;
} EstadoPronto;

void inserir_ep(EstadoPronto**, Processo); /* Insere na fila */
void inserir_prioridade_ep(EstadoPronto**, Processo); /* Insere com prioridade na fila */
EstadoPronto *remover_ep(EstadoPronto**); /* Remove item da fila */
void imprimir_eps(EstadoPronto*); /* Imprime a fila */ 

#endif // ESTADO_PRONTO_H_