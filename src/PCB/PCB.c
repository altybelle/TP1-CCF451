#include "PCB.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_PCB(struct PCB* pcb) {
    (*pcb).back = (*pcb).front = 0;
}

int is_PCB_empty(struct PCB* pcb) {
    return ((*pcb).back == (*pcb).front);
}

// enfileira o PCB
void enqueue_PCB(struct PCB* pcb, struct Process* proc) {
    if (!(((*pcb).back % PROGRAM_MAX + 1) == (*pcb).front)) { // checa se a tabela nao esta cheia e enfileira mais um processo caso nao esteja
        (*pcb).procs[(*pcb).back] = *proc;
        (*pcb).back = (*pcb).back % PROGRAM_MAX + 1;
        strcpy((*proc).state, "READY");
        printf("The process was successfully added to the PCB table. PID: %d.\n", (*proc).pid);
        return;
    }
    puts("Error: The PCB table is already full.");
}

// desenfileira um processo da PCB
int dequeue_PCB(struct PCB* pcb, struct Process* proc, int index) {
    int i;
    if (!(is_PCB_empty(pcb) || (*pcb).back <= index)) { // checa se a tabela nao esta vazia e desenfileira mais um processo caso nao esteja
        *proc = (*pcb).procs[index];
        (*pcb).back--;
        for (i = index; i < (*pcb).back; i++) {
            (*pcb).procs[i] = (*pcb).procs[i + 1];
        }
        return 1;
    }
    puts("Error: The PCB Table is empty.");
    return 0;
}

void print_PCB(struct PCB* pcb) {
    int i;
    puts("=============== PCB queue ===============");
    for (i = (*pcb).front; i < (*pcb).back; i++) {
        printf("Process %d: \n", i);
        print_process(&(*pcb).procs[i]);
        puts("=========================================");
    }
}