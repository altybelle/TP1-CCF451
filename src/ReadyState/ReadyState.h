#ifndef _READY_STATE_H_
#define _READY_STATE_H_

#include "../Process/Process.h"
#include "../Common.h"

struct ReadyState {
    struct Process procs[PROGRAM_MAX];
    int back, front;
};

void initialize_ready_state(struct ReadyState*);
int is_ready_state_empty(struct ReadyState*);
void enqueue_ready_state(struct ReadyState*, struct Process*);
int dequeue_ready_state(struct ReadyState*, struct Process*);
void print_ready_state(struct ReadyState*);

#endif // _READY_STATE_H_
