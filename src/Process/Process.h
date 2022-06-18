#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "../ProcessState/ProcessState.h"

#define STATE_MAX 15

struct Process {
    int pid, parent_pid;
    int startup_time;
    int cpu_quota;
    char state[STATE_MAX];
    int priority;  
    struct ProcessState process_state;
} Process;

void print_process(struct Process*);

#endif // _PROCESS_H_