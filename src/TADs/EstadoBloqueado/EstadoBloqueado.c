#include "EstadoBloqueado.h"

#include <stdio.h>
#include <stdlib.h>

void insere_eb(EstadoBloqueado** estado, Processo proc) {
    EstadoBloqueado *aux = NULL;
    EstadoBloqueado *novo = NULL;

    novo = (EstadoBloqueado*) malloc(sizeof(EstadoBloqueado));

    novo->proc = proc;
    novo->proximo = NULL;
    
    if (*estado == NULL) { 
        *estado = novo; 
    }
    else  {
        aux = *estado;
        while (aux->proximo)
            aux = aux->proximo;
        aux->proximo = novo;
    }
}

EstadoBloqueado *remover_eb(EstadoBloqueado** estado) {
    EstadoBloqueado *aux = NULL;
    
    if (*estado) {
        aux = *estado;
        *estado = aux->proximo;
    } else {
        printf("A lista está vazia!");
    }

    return aux;
}

void imprimir_eb(EstadoBloqueado* estado) {
    printf("Lista de Estados Bloqueados: \n");
    while (estado) {
        imprime_processo(&estado->proc);
        estado = estado->proximo;
    }

}
