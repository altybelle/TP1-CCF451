#include "InstructionRunner.h"
#include "../Common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void token_retrieve_1(Instructions inst, const char* tk_s, char* token, char* temp, int* i) {
    token = strtok(inst, tk_s);
    while (token) {
        if ((*i) == 1)
            temp = token;
        token = strtok(NULL, tk_s);
        (*i)++;
    }
}
void token_retrieve_2(Instructions inst, const char* tk_s, char* token, char* temp, char* temp2, int* i) {
    token = strtok(inst, tk_s);
    while (token) {
        if ((*i) == 1)
            temp = token;
        else
            temp2 = token;
        token = strtok(NULL, tk_s);
        (*i)++;
    }
}

void run_instructions(struct CPU* cpu, struct Process* proc, struct ExecState* exec, 
                     struct ReadyState* rs, struct BlockedState* bs, struct PCB* pcb, struct Time* time) {
    FILE *f = NULL;
    char *token = NULL;
    char command;
    char path[40];
    int i, j, x, y;
    char *temp = NULL, *temp2 = NULL;
    const char tk_s[2] = " ";
    char new_file[20] = "";
    Instructions inst;
    struct Process new_proc;
    
    strcpy(inst, "");

    int program_end = dequeue_program(&(*cpu).prog, inst, (*cpu).current_program_count);
    if (program_end == -1) {
        dequeue_PCB(pcb, proc, (*exec).iPCB);
        *proc = swap_process_CPU(cpu, rs);
        return;
    } else if (program_end == 0) {
        printf("Ended process. PID: %d", (*pcb).procs[(*exec).iPCB].pid);
        dequeue_PCB(pcb, proc, (*exec).iPCB);
        *proc = swap_process_CPU(cpu, rs);
        return;
    }
    
    i = x = y = 0;
    j = 2;
    command = inst[0];

    strcpy(path, "./FILES");

    switch (command) {
        case 'A':
            token_retrieve_2(inst, tk_s, token, temp, temp2, &i);
            x = atoi(temp);
            y = atoi(temp2);
            (*cpu).integer_value[x] += y;
            (*cpu).current_program_count++;
            (*time).time++;
        break;
        case 'B':
            enqueue_blocked_state(bs, proc);
            (*cpu).current_program_count++;
            (*time).time++;
        break;
        case 'D':
            token_retrieve_1(inst, tk_s, token, temp, &i);
            x = atoi(temp);
            if (!(*cpu).allocated_int_amount) {
                (*cpu).integer_value = (int*) calloc((*cpu).int_amount, sizeof(int));
                (*cpu).allocated_int_amount++;
                (*cpu).integer_value[x] = 0;
            } else {
                (*cpu).integer_value[x] = 0;
            }
            (*cpu).current_program_count++;
            (*time).time++;
        break;
        case 'F':
            token_retrieve_1(inst, tk_s, token, temp, &i);
            x = atoi(temp);
            new_proc = create_process(proc, time, x);
            if ((*proc).process_state.allocated_int_amount)
                for (int it = 0; it < (*proc).process_state.int_amount; it++) 
                    (*proc).process_state.integer[it] = (*cpu).integer_value[it];
            enqueue_ready_state(rs, &new_proc);
            enqueue_PCB(pcb, &new_proc);
            (*cpu).current_program_count++;
            (*time).time++;

        break;
        case 'N':
            token_retrieve_1(inst, tk_s, token, temp, &i);
            x = atoi(temp);
            (*cpu).int_amount = x;
            (*cpu).current_program_count++;
            (*time).time++;
        break;
        case 'R':
            while (j < 25 && inst[j+1] != 't' && inst[j] != '.') {
                new_file[j - 2] = inst[j];
                j++;
            }

            strcat(new_file, ".txt");
            strcat(path, new_file);

            f = fopen(path, "r");
            if (!f) { 
                puts("Error: file couldn't be opened.");
            } else {
                int inst_amount = 0;
                initialize_program(&(*cpu).prog);
                while ((fgets(inst, sizeof(inst), f))) {
                    enqueue_program(&(*cpu).prog, inst);
                    inst_amount++;
                }
                (*cpu).prog.size = inst_amount;
                fclose(f);
            }

            free((*cpu).integer_value);
            (*cpu).current_program_count = 0;
            (*time).time++;
        break;
        case 'S':
            token_retrieve_2(inst, tk_s, token, temp, temp2, &i);
            x = atoi(temp);
            y = atoi(temp2);
            (*cpu).integer_value[x] -= y;
            (*cpu).current_program_count++;
            (*time).time++;
        break;
        case 'T':
            dequeue_PCB(pcb, proc, (*exec).iPCB);
            *proc = swap_process_CPU(cpu, rs);
            (*time).time++;
        break;
        case 'V':
            token_retrieve_2(inst, tk_s, token, temp, temp2, &i);
            x = atoi(temp);
            y = atoi(temp2);
            (*cpu).integer_value[x] = y;
            (*cpu).current_program_count++;
            (*time).time++;
        break;
        default:
            puts("Error: the program couldn't interpret this command.");
            (*cpu).current_program_count++;
            (*time).time++;

    }

}