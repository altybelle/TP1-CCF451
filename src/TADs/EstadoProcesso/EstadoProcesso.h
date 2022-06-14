#ifndef ESTADO_PROCESSO_H_
#define ESTADO_PROCESSO_H_

#include "../Programa/Programa.h"

typedef struct EstadoProcesso {
    int quantidade_inteiros;
    int *inteiro;
    int contador;
    int tamanho;
    Programa programa[20];
} EstadoProcesso;

void imprimir_eprocs(EstadoProcesso*);

#endif // ESTADO_PROCESSO_H_