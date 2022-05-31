#include "EstadoBloqueado.h"

#include <stdio.h>
#include <stdlib.h>

void insere_eb(EstadoBloqueado** estado, int num) {
    EstadoBloqueado *aux = NULL;
    EstadoBloqueado *novo = NULL;

    novo = (EstadoBloqueado*) malloc(sizeof(EstadoBloqueado));

    novo->valor = num;
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
    printf("Estados Prontos\n");
    while (estado) {
        printf("%d ", estado->valor);
        estado = estado->proximo;
    }

}
