#ifndef PROGRAMA_H_
#define PROGRAMA_H_

#define TAM_INSTRUCAO 20
typedef unsigned char ConjuntoInstrucoes[TAM_INSTRUCAO];

typedef struct Programa {
  ConjuntoInstrucoes instrucoes[TAM_INSTRUCAO];
  int tamanho;
  int frente, tras;
} Programa;

#endif // PROGRAMA_H_