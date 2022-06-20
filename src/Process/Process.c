#include "Process.h"

#include <stdio.h>

void print_process(struct Process* proc) {
    int i;
    printf("PID: %d\n", (*proc).pid);
    printf("Parent PID: %d\n", (*proc).parent_pid);
    printf("CPU startup time: %d\n", (*proc).startup_time);
    printf("CPU quota time: %d\n", (*proc).cpu_quota);
    printf("State: %s\n", (*proc).state);
    printf("Priority: %d\n", (*proc).parent_pid);
    printf("Variable count: %d\n", (*proc).process_state.count);
    if ((*proc).process_state.allocated_int_amount) 
        for (i = 0; i < (*proc).process_state.int_amount; i++)
            printf("Integer %d value: %d\n", i, (*proc).process_state.integer[i]);
    printf("Program counter: %d\n", (*proc).process_state.count);
    puts("Process' program: ");
    for (i = 0; i < (*proc).process_state.size; i++)
        printf("%s", (*proc).process_state.prog[i]);
}