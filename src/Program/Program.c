#include "Program.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_program(struct Program *prog) {
    (*prog).back = (*prog).front = 0;
}

int is_program_empty(struct Program *prog) {
    return ((*prog).back == (*prog).front);
}

void enqueue_program(struct Program *prog, char *instructions) {
    if (!(((*prog).back % PROGRAM_MAX + 1) == (*prog).front)) { //verificando se a fila nao esta cheia
        (*prog).back = (*prog).back % PROGRAM_MAX + 1;
        strcpy((*prog).inst[(*prog).back], instructions); // copiando as instrucoes
        return;
    }
    puts("Error: the program's queue is already full.");
}

int dequeue_program(struct Program *prog, char *instructions, int index) {
    int is_empty = (is_program_empty(prog));
    int index_surpass_back = ((*prog).back <= index);

    if (is_empty) return -1;
    if (index_surpass_back) return 0; // nao se encontra na fila

    strcpy(instructions, (*prog).inst[index]); // passando as instrucoes para o programa na cpu
    return 1;
}