#include "ReadyState.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_ready_state(struct ReadyState* rs) {
    rs->back = rs->front = 0;
}

int is_ready_state_empty(struct ReadyState* rs) {
    return (rs->back == rs->front);
}

void enqueue_ready_state(struct ReadyState* rs, struct Process* proc) {
    if (!((rs->back % PROGRAM_MAX + 1) == rs->front)) {
        rs->procs[rs->back] = *proc;
        rs->back = rs->back % PROGRAM_MAX + 1;
        strcpy(proc->state, "READY");
        printf("The process was successfully added to the Ready State queue. PID: %d.\n", proc->pid);
        return;
    }
    puts("Error: The Ready State queue is already full.");
}

int dequeue_ready_state(struct ReadyState* rs, struct Process* proc) {
    if (!is_ready_state_empty(rs)) {
        *proc = rs->procs[rs->front];
        rs->front = rs->front % PROGRAM_MAX + 1;
        return 1;
    }
    puts("Error: The Ready State queue is empty.");
    return 0;
}

void print_ready_state(struct ReadyState* rs) {
    int i;
    puts("=============== Ready State queue ===============");
    for (i = rs->front; i < rs->back; i++) {
        printf("Process %d: \n", i);
        print_process(&rs->procs[i]);
        puts("=================================================");
    }
}
