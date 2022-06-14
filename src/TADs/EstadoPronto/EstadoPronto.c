#include "EstadoPronto.h"

#include <stdio.h>
#include <stdlib.h>

void insere_ep(EstadoPronto** estado, Processo proc) {
    EstadoPronto *aux = NULL;
    EstadoPronto *novo = NULL;

    novo = (EstadoPronto*) malloc(sizeof(EstadoPronto));

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

void insere_prioridade_ep(EstadoPronto** estado, Processo proc) {
    EstadoPronto *aux = NULL;
    EstadoPronto *novo = NULL;

    novo = (EstadoPronto*) malloc(sizeof(EstadoPronto));

    novo->proc = proc;
    novo->proximo = NULL;
    if (*estado == NULL) {
        *estado = novo;
    } else {
        if (proc.prioridade > 255) { /* Condição arbitrária para prioridade */
            if ((*estado)->proc.prioridade < 256) { /* Checa se é a primeira prioridade */
                novo->proximo = *estado;
                *estado = novo;
            } else {
                aux = *estado;
                while (aux->proximo && aux->proximo->proc.prioridade > 255)
                    aux = aux->proximo;
                novo->proximo = aux->proximo;
                aux->proximo = novo;
            }
        } else {
            aux = *estado;
            while (aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
        } 
    }
}

EstadoPronto *remover_ep(EstadoPronto** estado) {
    EstadoPronto *aux = NULL;
    
    if (*estado) {
        aux = *estado;
        *estado = aux->proximo;
    } else {
        printf("A lista está vazia!");
    }

    return aux;
}


void imprimir_ep(EstadoPronto* estado) {
    printf("Lista de Estados Prontos: \n");
    while (estado) {
        imprime_processo(&estado->proc);
        estado = estado->proximo;
    }

}
