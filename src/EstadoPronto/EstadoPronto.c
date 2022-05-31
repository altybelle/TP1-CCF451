#include "EstadoPronto.h"

#include <stdio.h>
#include <stdlib.h>

void insere_ep(EstadoPronto** estado, int num) {
    EstadoPronto *aux = NULL;
    EstadoPronto *novo = NULL;

    novo = (EstadoPronto*) malloc(sizeof(EstadoPronto));

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

void insere_prioridade_ep(EstadoPronto** estado, int num) {
    EstadoPronto *aux = NULL;
    EstadoPronto *novo = NULL;

    novo = (EstadoPronto*) malloc(sizeof(EstadoPronto));

    novo->valor = num;
    novo->proximo = NULL;
    if (*estado == NULL) {
        *estado = novo;
    } else {
        if (num > 255) { /* Condição arbitrária para prioridade */
            if ((*estado)->valor < 256) { /* Checa se é a primeira prioridade */
                novo->proximo = *estado;
                *estado = novo;
            } else {
                aux = *estado;
                while (aux->proximo && aux->proximo->valor > 255)
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
    printf("Estados Prontos\n");
    while (estado) {
        printf("%d ", estado->valor);
        estado = estado->proximo;
    }

}
