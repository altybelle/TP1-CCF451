#ifndef _PCB_H_
#define _PCB_H_

#include "../Process/Process.h"
#include "../Common.h"

struct PCB {
    struct Process procs[PROGRAM_MAX];
    int back, front;
};

void initialize_PCB(struct PCB*);
int is_PCB_empty(struct PCB*);
void enqueue_PCB(struct PCB*, struct Process*);
int dequeue_PCB(struct PCB*, struct Process*, int);
void print_PCB(struct PCB*);

#endif // _PCB_H_