#include "EstadoProcesso.h"

#include <stdio.h>

void imprimir_eproc(EstadoProcesso *eproc) {
    int i;
    printf("Quantidade de variaveis inteiras: %d\n", eproc->quantidade_inteiros);
    if (eproc->tamanho) {
        for (i = 0; i < eproc->quantidade_inteiros; i++) {
            printf("Valor inteiro da variavel %d: %d\n", i, eproc->inteiro[i]);
        }
        printf("Contador de programa: %d\n", eproc->contador);
        printf("Programa de processo: ");
        for (i = 0; i < eproc->tamanho; i++) 
            printf("%s\t", eproc->programa[i]);
        printf("\n");
    }
}