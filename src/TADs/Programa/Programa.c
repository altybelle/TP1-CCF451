#include "Programa.h"

#include <stdio.h>
#include <stdlib.h>

void inserir_prog(Programa** prog, ConjuntoInstrucoes instrucoes) {
    Programa *aux = NULL;
    Programa *novo = NULL;

    novo = (Programa*) malloc(sizeof(Programa));

    strcpy(novo->instrucoes, instrucoes);
    novo->proximo = NULL;
    
    if (*prog == NULL) { 
        *prog = novo; 
    }
    else  {
        aux = *prog;
        while (aux->proximo)
            aux = aux->proximo;
        aux->proximo = novo;
    }
}

Programa *remover_prog(Programa** prog) {
    Programa *aux = NULL;
    
    if (*prog) {
        aux = *prog;
        *prog = aux->proximo;
    } else {
        printf("A lista está vazia!");
    }

    return aux;
}