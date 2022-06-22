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
    char temp[BUFFER], temp2[BUFFER];
    const char tk_s[2] = " ";
    char new_file[20] = "";
    Instructions inst;
    struct Process new_proc;
    
    strcpy(inst, "");

    int program_end = dequeue_program(&(*cpu).prog, inst, (*cpu).current_program_count);
    if (program_end == -1) { // checa se nao ha instrucoes e retira o programa da tabela
        dequeue_PCB(pcb, proc, (*exec).iPCB);
        *proc = swap_process_CPU(cpu, rs);
        return;
    } else if (program_end == 0) { // checa se nao ha mais instrucoes a serem feitas e retira o programa da tabela
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
            token_retrieve_2(inst, tk_s, token, temp, temp2, &i); // retira os valores da instrucao
            x = atoi(temp); // obtendo o indice
            y = atoi(temp2); // obtendo o valor a ser adicionado
            (*cpu).integer_value[x] += y; // adiciona n para a variavel na posicao x
            (*cpu).current_program_count++; // incrementa o contador de programa
            (*time).time++; // incrementa o tempo
        break;
        case 'B':
            enqueue_blocked_state(bs, proc);
            (*cpu).current_program_count++; // incrementa o contador de programa
            (*time).time++; // incrementa o tempo
        break;
        case 'D':
            token_retrieve_1(inst, tk_s, token, temp, &i); // retira os valores
            x = atoi(temp); // obtendo o indice da variavel
            if (!(*cpu).allocated_int_amount) {
                (*cpu).integer_value = (int*) calloc((*cpu).int_amount, sizeof(int)); // alocando espaco para ela
                (*cpu).allocated_int_amount++; // coloca como sendo 1 a memoria alocada
                (*cpu).integer_value[x] = 0; // inicializa a variavel como sendo 0
            } else {
                (*cpu).integer_value[x] = 0; // inicializa a variavel como sendo 0
            }
            (*cpu).current_program_count++; // incrementa o contador de programa
            (*time).time++; // incrementa o tempo
        break;
        case 'F':
            token_retrieve_1(inst, tk_s, token, temp, &i); // retira os valores
            x = atoi(temp); // obtendo o valor do deslocamento
            new_proc = create_process(proc, time, x); // criando o novo processo filho
            if ((*proc).process_state.allocated_int_amount)
                for (int it = 0; it < (*proc).process_state.int_amount; it++) 
                    (*proc).process_state.integer[it] = (*cpu).integer_value[it]; // inicializa as variaveis iguais
            enqueue_ready_state(rs, &new_proc); // coloca o processo filho como pronto
            enqueue_PCB(pcb, &new_proc); // coloca o processo filho dentro da tabela
            (*cpu).current_program_count++; // incrementa o contador de programa
            (*time).time++; // incrementa o tempo

        break;
        case 'N':
            token_retrieve_1(inst, tk_s, token, temp, &i); // retira os valores
            x = atoi(temp); // obtem o valor da quantidade de variaveis
            (*cpu).int_amount = x; // coloca o valor na cpu
            (*cpu).current_program_count++; // incrementa o contador de programa
            (*time).time++; // incrementa o tempo
        break;
        case 'R':
            while (j < 25 && inst[j+1] != 't' && inst[j] != '.') {
                new_file[j - 2] = inst[j];
                j++;
            }

            // obtendo o caminho do arquivo do programa
            strcat(new_file, ".txt");
            strcat(path, new_file);

            f = fopen(path, "r");
            if (!f) { 
                puts("Error: file couldn't be opened.");
            } else {
                int inst_amount = 0;
                initialize_program(&(*cpu).prog); // inicializa o programa
                while ((fgets(inst, sizeof(inst), f))) {
                    enqueue_program(&(*cpu).prog, inst); // coloca na frente da fila
                    inst_amount++;
                }
                (*cpu).prog.size = inst_amount; // coloca o tamanho do novo programa
                fclose(f);
            }

            free((*cpu).integer_value); // libera os valores do antigo programa
            (*cpu).current_program_count = 0; // volta o contador do programa para 0
            (*time).time++; // incrementa o tempo
        break;
        case 'S':
            token_retrieve_2(inst, tk_s, token, temp, temp2, &i); // retira os valores
            x = atoi(temp); // obtem o indice
            y = atoi(temp2); // obtem o valor a ser subtraido
            (*cpu).integer_value[x] -= y; // subtrai y do inteiro na posicao x
            (*cpu).current_program_count++; // incrementa o contador de programa
            (*time).time++; // incrementa o tempo
        break;
        case 'T':
            dequeue_PCB(pcb, proc, (*exec).iPCB); // retira o processo da tabela de processos
            *proc = swap_process_CPU(cpu, rs); // troca o processo pelo proximo
            (*time).time++; // incrementa o tempo
        break;
        case 'V':
            token_retrieve_2(inst, tk_s, token, temp, temp2, &i); // retira os valores
            x = atoi(temp); // obtem o indice
            y = atoi(temp2); // obtem o valor que a variavel vai receber
            (*cpu).integer_value[x] = y; // faz o valor na posicao x se tornar y
            (*cpu).current_program_count++; // incrementa o contador de programa
            (*time).time++; // incrementa o tempo
        break;
        default:
            puts("Error: the program couldn't interpret this command.");
            (*cpu).current_program_count++; // incrementa o contador de programa
            (*time).time++; // incrementa o tempo

    }

}