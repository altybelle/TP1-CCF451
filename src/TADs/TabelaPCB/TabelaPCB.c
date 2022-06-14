#include "TabelaPCB.h"

#include <stdio.h>
#include <stdlib.h>

void insere_pcb(TabelaPCB** tabela, Processo proc) {
    TabelaPCB *aux = NULL;
    TabelaPCB *novo = NULL;

    novo = (TabelaPCB*) malloc(sizeof(TabelaPCB));

    novo->proc = proc;
    novo->proximo = NULL;
    
    if (*tabela == NULL) { 
        *tabela = novo; 
    }
    else  {
        aux = *tabela;
        while (aux->proximo)
            aux = aux->proximo;
        aux->proximo = novo;
    }
}

TabelaPCB *remover_pcb(TabelaPCB** tabela) {
    TabelaPCB *aux = NULL;
    
    if (*tabela) {
        aux = *tabela;
        *tabela = aux->proximo;
    } else {
        printf("A lista está vazia!");
    }

    return aux;
}

void imprimir_pcb(TabelaPCB* tabela) {
    printf("Tabela PCB: \n");
    while (tabela) {
        imprime_processo(&tabela->proc);
        tabela = tabela->proximo;
    }

}
