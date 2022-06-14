#ifndef PROGRAMA_H_
#define PROGRAMA_H_

#define TAM_INSTRUCAO 20
typedef unsigned char ConjuntoInstrucoes[TAM_INSTRUCAO];

typedef struct Programa {
  int tamanho;
  ConjuntoInstrucoes instrucoes;
  struct Programa *proximo;
} Programa;

void inserir_prog(Programa**, ConjuntoInstrucoes); /* Insere na fila */
Programa *remover_prog(Programa**); /* Remove item da fila */

#endif // PROGRAMA_H_