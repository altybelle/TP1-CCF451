#include "ProcessManager.h"
#include "../InstructionRunner/InstructionRunner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void initialize(struct CPU* cpu, struct ExecState* exec, struct ReadyState* rs, 
    struct BlockedState *bs, struct PCB* pcb, struct Time* time) {
    (*exec).iPCB = 0;

    initialize_blocked_state(bs);
    initialize_PCB(pcb);
    initialize_program(&(*cpu).prog);
    
    (*cpu).time_slice = 0;
    (*cpu).used_time_slices = 0;
    (*cpu).int_amount = 0;
    (*cpu).integer_value = 0;
    (*cpu).allocated_int_amount = 0;
    (*cpu).current_program_count = 0;
    (*time).time = 0;
    (*time).created_processes_amount = 0;
}

struct Process create_first_process(struct Program *prog, struct Time *time, int instruction_amount, int parent_pid) {
    int i;
    struct Process proc;  
    
    proc.pid = rand() % 10000;
    proc.parent_pid = parent_pid;
    proc.priority = 0;
    proc.cpu_quota = 0;
    proc.process_state.integer = 0;
    proc.process_state.int_amount = 0;
    proc.process_state.allocated_int_amount = 0;
    proc.process_state.count = 0;
    proc.process_state.size = instruction_amount;
    proc.startup_time = (*time).time;
    
    for (i = 0; i < instruction_amount; i++) {
        strcpy(proc.process_state.prog[i], (*prog).inst[i]);
    }

    strcpy(proc.state, "READY");
    (*time).created_processes_amount++;
    return proc;
}

struct Process create_process(struct Process *parent_proc, struct Time *time, int instruction_number) {
    struct Process proc;

    proc.pid = rand() % 10000;
    proc.parent_pid = (*parent_proc).pid;
    proc.priority = (*parent_proc).priority;
    proc.cpu_quota = 0;

    if ((*parent_proc).process_state.allocated_int_amount)
        proc.process_state.integer = (int*) calloc((*parent_proc).process_state.int_amount, sizeof(int));

    proc.process_state.size = (*parent_proc).process_state.size;
    proc.process_state.int_amount = (*parent_proc).process_state.int_amount;
    proc.process_state.allocated_int_amount = (*parent_proc).process_state.allocated_int_amount;
    proc.process_state.count = instruction_number;
    proc.startup_time = (*time).time;

    for (int i = 0; i < (*parent_proc).process_state.size; i++) {
        strcpy(proc.process_state.prog[i], (*parent_proc).process_state.prog[i]);
    }

    strcpy(proc.state, "READY");
    (*time).created_processes_amount++;
    return proc;
}

struct Process put_process_CPU(struct CPU *cpu, struct ReadyState *rs) {
    struct Process proc;

    dequeue_ready_state(rs, &proc);

    (*cpu).prog.size = proc.process_state.size;

    for (int i = 0; i < (*cpu).prog.size; i++) {
        enqueue_program(&(*cpu).prog, proc.process_state.prog[i]);
    }

    (*cpu).current_program_count = proc.process_state.count;
    (*cpu).time_slice = 10;
    (*cpu).used_time_slices = 0;
    (*cpu).int_amount = proc.process_state.int_amount;
    (*cpu).integer_value = proc.process_state.integer;
    (*cpu).allocated_int_amount = proc.process_state.allocated_int_amount;

    return proc;
}

struct Process swap_process_CPU(struct CPU* cpu, struct ReadyState* rs) {
    struct Process proc;

    dequeue_ready_state(rs, &proc);

    (*cpu).prog.size = proc.process_state.size;

    initialize_program(&(*cpu).prog);

    for (int i = 0; i < (*cpu).prog.size; i++) {
        enqueue_program(&(*cpu).prog, proc.process_state.prog[i]);
    }

    (*cpu).current_program_count = proc.process_state.count;
    (*cpu).time_slice = 10;
    (*cpu).used_time_slices = 0;
    (*cpu).int_amount = proc.process_state.int_amount;
    (*cpu).integer_value = proc.process_state.integer;
    (*cpu).allocated_int_amount = proc.process_state.allocated_int_amount;

    return proc;
}

void execute(struct CPU* cpu, struct ExecState* exec, struct ReadyState* rs, struct BlockedState* bs, struct PCB* pcb, struct Process* proc, struct Time* time) {

    run_instructions(cpu, proc, exec, rs, bs, pcb, time);

    if ((*proc).priority >= 0 && (*proc).priority <= 3) {
        (*cpu).used_time_slices += (int)pow(2, (*proc).priority);
    } else {
        puts("Error: Failed to update used time slice data.");
    }

    (*proc).process_state.count = (*cpu).current_program_count;
    (*proc).cpu_quota = (*cpu).used_time_slices;
    (*proc).process_state.allocated_int_amount = (*cpu).allocated_int_amount;
    (*proc).process_state.int_amount = (*cpu).int_amount;

    for (int i = 0; i < (*proc).process_state.size; i++) {
        strcpy((*proc).process_state.prog[i], (*cpu).prog.inst[i]);
    }

    if ((*cpu).allocated_int_amount)
        (*proc).process_state.integer = (*cpu).integer_value;

    (*pcb).procs[(*exec).iPCB] = *proc;

    if ((*cpu).used_time_slices >= (*cpu).time_slice) {
        if ((*proc).priority < 3 && (*proc).priority >= 0) {
            printf("Priority from PID %d changed from %d to %d.", (*proc).pid, (*proc).priority, (*pcb).procs[(*exec).iPCB].priority + 1);
            (*proc).priority++;
            (*pcb).procs[(*exec).iPCB].priority++;
        }

        enqueue_blocked_state(bs, proc);
        *proc = swap_process_CPU(cpu, rs);
    } else if (!strcmp((*proc).state,"BLOCKED")) {
        *proc = swap_process_CPU(cpu, rs);
    }
}

void execute2(struct CPU* cpu, struct ExecState* exec, struct ReadyState* rs, struct BlockedState* bs, struct PCB* pcb, struct Process* proc, struct Time* time) {

    run_instructions(cpu, proc, exec, rs, bs, pcb, time);

    if ((*proc).priority >= 0 && (*proc).priority <= 3) {
        (*cpu).used_time_slices += (int)pow(2, (*proc).priority);
    } else {
        puts("Error: Failed to update used time slice data.");
    }

    (*proc).process_state.count = (*cpu).current_program_count;
    (*proc).cpu_quota = (*cpu).used_time_slices;
    (*proc).process_state.allocated_int_amount = (*cpu).allocated_int_amount;
    (*proc).process_state.int_amount = (*cpu).int_amount;

    for (int i = 0; i < (*proc).process_state.size; i++) {
        strcpy((*proc).process_state.prog[i], (*cpu).prog.inst[i]);
    }

    if((*cpu).allocated_int_amount)
        (*proc).process_state.integer = (*cpu).integer_value;
    (*pcb).procs[(*exec).iPCB] = *proc;

    if ((*cpu).used_time_slices >= (*cpu).time_slice) {
        if ((*proc).priority > 0 && (*proc).priority <= 3) {
            printf("Priority from PID %d changed from %d to %d.", (*proc).pid, (*proc).priority, (*pcb).procs[(*exec).iPCB].priority + 1);
            (*proc).priority++;
            (*pcb).procs[(*exec).iPCB].priority++;
        }
        enqueue_blocked_state(bs, proc);
        *proc = swap_process_CPU(cpu,rs);
    } else if ((*cpu).used_time_slices < (*cpu).time_slice) {
        if ((*proc).priority > 0 && (*proc).priority <= 3){
            printf("Priority from PID %d changed from %d to %d.", (*proc).pid, (*proc).priority, (*pcb).procs[(*exec).iPCB].priority + 1);
            (*proc).priority--;
            (*pcb).procs[(*exec).iPCB].priority--;
        }
    } else if (!strcmp((*proc).state,"BLOCKED")) {
        *proc = swap_process_CPU(cpu,rs);
    }
}

void print_whole_system(struct CPU* cpu, struct ReadyState* rs, struct BlockedState* bs, struct PCB* pcb) {
    puts("=============== SYSTEM INFO ===============");
    print_CPU(cpu);
    print_ready_state(rs);
    print_blocked_state(bs);
    print_PCB(pcb);
}