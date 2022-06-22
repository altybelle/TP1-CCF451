#include "ProcessManager.h"
#include "../InstructionRunner/InstructionRunner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


//inicializa as variaveis para o inicio do gerenciador de processos
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

// cria o primeiro processo
struct Process create_first_process(struct Program *prog, struct Time *time, int instruction_amount, int parent_pid) {
    int i;
    struct Process proc;  
    
    // inicializando as variaveis corretamente
    proc.pid = rand() % 10000; // process id aleatorio
    proc.parent_pid = parent_pid;
    proc.priority = 0;
    proc.cpu_quota = 0;
    proc.process_state.integer = 0;
    proc.process_state.int_amount = 0;
    proc.process_state.allocated_int_amount = 0;
    proc.process_state.count = 0;
    proc.process_state.size = instruction_amount;
    proc.startup_time = (*time).time; // tempo de inicializacao o tempo atual
    
    for (i = 0; i < instruction_amount; i++) {
        strcpy(proc.process_state.prog[i], (*prog).inst[i]); // copia as instrucoes para o processo criado
    }

    strcpy(proc.state, "READY"); // coloca ele como pronto
    (*time).created_processes_amount++; //incrementa a quantidade de processos criados no total
    return proc;
}

// cria processos
struct Process create_process(struct Process *parent_proc, struct Time *time, int instruction_number) {
    struct Process proc;

    // inicializando as variaveis corretamente
    proc.pid = rand() % 10000; // process id aleatorio
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
        strcpy(proc.process_state.prog[i], (*parent_proc).process_state.prog[i]); // passando as instruções
    }

    strcpy(proc.state, "READY"); // coloca ele como pronto
    (*time).created_processes_amount++; //incrementa a quantidade de processos criados no total
    return proc;
}

// coloca o processo na CPU
struct Process put_process_CPU(struct CPU *cpu, struct ReadyState *rs) {
    struct Process proc;

    dequeue_ready_state(rs, &proc); // retira o processo da fila de processos prontos

    (*cpu).prog.size = proc.process_state.size; //colocando o tamanho na cpu

    for (int i = 0; i < (*cpu).prog.size; i++) {
        enqueue_program(&(*cpu).prog, proc.process_state.prog[i]); // enfileirando o processo para ser executado na CPU
    }

    (*cpu).current_program_count = proc.process_state.count;
    (*cpu).time_slice = 10;
    (*cpu).used_time_slices = 0;
    (*cpu).int_amount = proc.process_state.int_amount;
    (*cpu).integer_value = proc.process_state.integer;
    (*cpu).allocated_int_amount = proc.process_state.allocated_int_amount;

    return proc;
}

// troca de processo a ser executado na CPU
struct Process swap_process_CPU(struct CPU* cpu, struct ReadyState* rs) {
    struct Process proc;

    dequeue_ready_state(rs, &proc); // retira o processo da fila de processos prontos

    (*cpu).prog.size = proc.process_state.size; // colocando na CPU

    initialize_program(&(*cpu).prog); // retirando o primeiro da fila na CPU

    for (int i = 0; i < (*cpu).prog.size; i++) {
        enqueue_program(&(*cpu).prog, proc.process_state.prog[i]); // enfileirando o processo para ser executado na CPU
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

    run_instructions(cpu, proc, exec, rs, bs, pcb, time); // executa as instrucoes do programa

    if ((*proc).priority >= 0 && (*proc).priority <= 3) {
        (*cpu).used_time_slices += (int)pow(2, (*proc).priority); // somando a fracao de tempo utilizada na CPU como sendo 2 elevado a prioridade
    } else {
        puts("Error: Failed to update used time slice data.");
    }

    (*proc).process_state.count = (*cpu).current_program_count;
    (*proc).cpu_quota = (*cpu).used_time_slices;
    (*proc).process_state.allocated_int_amount = (*cpu).allocated_int_amount;
    (*proc).process_state.int_amount = (*cpu).int_amount;

    for (int i = 0; i < (*proc).process_state.size; i++) { // obtendo o programa da CPU
        strcpy((*proc).process_state.prog[i], (*cpu).prog.inst[i]);
    }

    if ((*cpu).allocated_int_amount)
        (*proc).process_state.integer = (*cpu).integer_value;

    (*pcb).procs[(*exec).iPCB] = *proc;

    if ((*cpu).used_time_slices >= (*cpu).time_slice) { // verificando se usou um tempo maior ou igual a fatia de tempo definida e incrementando sua prioridade
        if ((*proc).priority < 3 && (*proc).priority >= 0) {
            printf("Priority from PID %d changed from %d to %d.", (*proc).pid, (*proc).priority, (*pcb).procs[(*exec).iPCB].priority + 1);
            (*proc).priority++;
            (*pcb).procs[(*exec).iPCB].priority++;
        }

        enqueue_blocked_state(bs, proc);
        *proc = swap_process_CPU(cpu, rs);
    } else if (!strcmp((*proc).state,"BLOCKED")) { // troca de processo caso esteja bloqueado
        *proc = swap_process_CPU(cpu, rs);
    }
}

void execute2(struct CPU* cpu, struct ExecState* exec, struct ReadyState* rs, struct BlockedState* bs, struct PCB* pcb, struct Process* proc, struct Time* time) {

    run_instructions(cpu, proc, exec, rs, bs, pcb, time); // executa as instrucoes do programa

    if ((*proc).priority >= 0 && (*proc).priority <= 3) {
        (*cpu).used_time_slices += (int)pow(2, (*proc).priority); // somando a fracao de tempo utilizada na CPU como sendo 2 elevado a prioridade
    } else {
        puts("Error: Failed to update used time slice data.");
    }

    (*proc).process_state.count = (*cpu).current_program_count;
    (*proc).cpu_quota = (*cpu).used_time_slices;
    (*proc).process_state.allocated_int_amount = (*cpu).allocated_int_amount;
    (*proc).process_state.int_amount = (*cpu).int_amount;

    for (int i = 0; i < (*proc).process_state.size; i++) { // obtendo o programa da CPU
        strcpy((*proc).process_state.prog[i], (*cpu).prog.inst[i]);
    }

    if((*cpu).allocated_int_amount)
        (*proc).process_state.integer = (*cpu).integer_value;
    (*pcb).procs[(*exec).iPCB] = *proc;

    if ((*cpu).used_time_slices >= (*cpu).time_slice) { // verificando se usou um tempo maior ou igual a fatia de tempo definida e incrementando sua prioridade
        if ((*proc).priority > 0 && (*proc).priority <= 3) {
            printf("Priority from PID %d changed from %d to %d.", (*proc).pid, (*proc).priority, (*pcb).procs[(*exec).iPCB].priority + 1);
            (*proc).priority++;
            (*pcb).procs[(*exec).iPCB].priority++;
        }
        enqueue_blocked_state(bs, proc);
        *proc = swap_process_CPU(cpu,rs);
    } else if ((*cpu).used_time_slices < (*cpu).time_slice) {  // verificando se usou um tempo menor que a fatia de tempo definida e decrementando sua prioridade
        if ((*proc).priority > 0 && (*proc).priority <= 3){
            printf("Priority from PID %d changed from %d to %d.", (*proc).pid, (*proc).priority, (*pcb).procs[(*exec).iPCB].priority + 1);
            (*proc).priority--;
            (*pcb).procs[(*exec).iPCB].priority--;
        }
    } else if (!strcmp((*proc).state,"BLOCKED")) { // troca de processo caso esteja bloqueado
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