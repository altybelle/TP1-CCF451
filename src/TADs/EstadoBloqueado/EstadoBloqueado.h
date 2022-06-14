#include "../Processo/Processo.h"

#ifndef ESTADO_BLOQUEADO_H_
#define ESTADO_BLOQUEADO_H_

typedef struct EstadoBloqueado {
    Processo proc;
    struct EstadoBloqueado *proximo;
} EstadoBloqueado;

void inserir_eb(EstadoBloqueado**, Processo); /* Insere na fila */
EstadoBloqueado *remover_eb(EstadoBloqueado**); /* Remove item da fila */
void imprimir_ebs(EstadoBloqueado*); /* Imprime a fila */ 

#endif // ESTADO_BLOQUEADO_H_