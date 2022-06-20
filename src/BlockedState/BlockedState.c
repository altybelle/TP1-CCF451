#include "BlockedState.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_blocked_state(struct BlockedState* bs) {
    (*bs).back = (*bs).front = 0;
}

int is_blocked_state_empty(struct BlockedState* bs) {
    return ((*bs).back == (*bs).front);
}

void enqueue_blocked_state(struct BlockedState* bs, struct Process* proc) {
    if (!(((*bs).back % PROGRAM_MAX + 1) == (*bs).front)) {
        (*bs).procs[(*bs).back] = *proc;
        (*bs).back = (*bs).back % PROGRAM_MAX + 1;
        strcpy(proc->state, "BLOCKED");
        printf("The process was successfully added to the Blocked State queue. PID: %d.\n", proc->pid);
        return;
    }
    puts("Error: The Blocked State queue is already full.");
}

int dequeue_blocked_state(struct BlockedState* bs, struct Process* proc) {
    if (!is_blocked_state_empty(bs)) {
        *proc = (*bs).procs[(*bs).front];
        (*bs).front = (*bs).front % PROGRAM_MAX + 1;
        return 1;
    }
    puts("Error: The Blocked State queue is empty.");
    return 0;
}

void print_blocked_state(struct BlockedState* bs) {
    int i;
    puts("=============== Blocked State queue ===============");
    for (i = (*bs).front; i < (*bs).back; i++) {
        printf("Process %d: \n", i);
        print_process(&(*bs).procs[i]);
        puts("===================================================");
    }
}