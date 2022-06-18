#ifndef _BLOCKED_STATE_H_
#define _BLOCKED_STATE_H_

#include "../Process/Process.h"
#include "../Common.h"

struct BlockedState {
    struct Process procs[PROGRAM_MAX];
    int back, front;
};

void initialize_blocked_state(struct BlockedState*);
int is_blocked_state_empty(struct BlockedState*);
void enqueue_blocked_state(struct BlockedState*, struct Process*);
int dequeue_blocked_state(struct BlockedState*, struct Process*);
void print_blocked_state(struct BlockedState*);

#endif // _BLOCKED_STATE_H_
