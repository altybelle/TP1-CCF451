#include "./Control.h"
#include "../Common.h"
#include "../ProcessManager/ProcessManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int execute_control(){
    FILE *f = NULL; // ponteiro para o arquivo de entrada
    int pid; // id do processo
    struct Program prog; // programa que ira receber a entrada
    Instructions inst; // variavel que recebera as instruções do programa
    int desc[2], s_desc[2]; // file descriptors para o pipe
    char sent[BUFFER], received[BUFFER]; // variaveis para o recebimento das mensagens via pipe
    int inst_amount = 0; // tamanho do programa que recebe a entrada
    
    if (pipe(desc) < 0) {  // tenta abrir o pipe
        perror("Error: Pipe error.");
        return -1; 
    }
    if ((pid = fork()) < 0){ // tenta executar o fork
        perror("Error: Fork error.");
        exit(1);
    }
  
    // aqui é executado dentro do processo filho
    if (pid > 0) {
        close(desc[0]); // fechando a saída do pipe

        // definindo se funcionara no modo de arquivo ou interativo
        int a = 0;
        while (a != 1 && a != 2) {
            printf("Do you wanna use file mode (1) or interactive mode (2)? R: ");
            scanf("%d", &a);
            if (a != 1 && a != 2) {
                printf("\nError: Invalid input!\n");
            }
        }
        
        // 
        if (a == 1) {
            read_file(sent); // escreve em sent o arquivo de entrada
        } else {
            read_terminal(sent); // le do terminal a entrada
        }
        
        printf("String sent from Control %i to the Manager. Content: %s\n", getpid(), sent);
        write(desc[1], sent, sizeof(sent) + 1); // entra no pipe a entrada
        exit(0);
        return 1; 
    }
    

    // daqui pra baixo é o processo pai
    int dequeued; // verifica caso existe um processo para passar do estado bloqueado para o pronto
    struct CPU cpu;
    struct ExecState exec; // armazena o indice do processo em execução
    struct ReadyState rs; // armazena a fila de processos prontos
    struct BlockedState bs; // armazena a fila de processos bloqueados
    struct PCB pcb; // armazena os processos
    struct Time time; // armazena a unidade de tempo atual
    struct Process u_proc; // armazena o processo para passar do estado bloqueado para o pronto

    if (pipe(s_desc) < 0) { // verifica caso o pipe foi efetuado com sucesso
        perror("Error: Pipe error.");
        return -1;
    }
    initialize(&cpu, &exec, &rs, &bs, &pcb, &time);

    f = fopen("./FILES/INPUT/PROG.txt", "r"); // abrindo o programa

    if (!f) {
        puts("Error: coudln't open PROG.txt file.");
    } else {
        while((fgets(inst, sizeof(inst), f))){
                enqueue_program(&prog, inst); // enfileirando o programa 
                inst_amount++;
            }
        fclose(f);
    }

    prog.size = inst_amount; // armazenando seu tamanho

    struct Process proc = create_first_process(&prog, &time, inst_amount, getpid());

    close(desc[1]); // fechando a entrada do pipe
    read(desc[0],  received, sizeof(received)); // leitura do pipe

    printf("String received from PID %i Manager and sent from Control. Content: '%s'\n\n", getpid(), received);

    enqueue_ready_state(&rs, &proc); // enfileirando o primeiro programa como pronto
    enqueue_PCB(&pcb, &proc); // enfileirando em PCB

    proc = put_process_CPU(&cpu, &rs); // coloca o processo para ser executado na cpu
    for (int j = 0; j < strlen(received); j++) {
        switch (received[j]) {
            case 'I':
                print_whole_system(&cpu, &rs, &bs, &pcb);
                break;
            case 'L':
                dequeued = dequeue_blocked_state(&bs, &u_proc);
                if (dequeued)
                    enqueue_ready_state(&rs, &u_proc);
                break;
            case 'M':
                print_average_cycle_time(&time);
                exit(0);
                break;
            case 'U':
                execute(&cpu, &exec, &rs, &bs, &pcb, &proc, &time);
                break;
            default:
                break;
        }
    }
    return 0;
}

void read_terminal(char *sent){
    int i = 0;
    char command;
    printf("Insert a command: ");
    do {
        scanf("%c",&command); // obtendo o comando do terminal
        sent[i] = command;
        strcat(sent, " "); // concatenando na string de entrada
        i += 2;
    } while (command != 'M');
}

int read_file(char *sent){
    FILE *f;
    char str[2];
    f = fopen("./FILES/INPUT/CTRL.txt","r"); // abrindo o arquivo
    if (!f){
      puts("Error: couldn't open CTRL file.");
      return 0;
    } 
      
    while(fscanf(f, "%s", str) != EOF) { // concatenando em uma string
        strcat(sent, str);
        strcat(sent, " ");
    }
    
    fclose(f);
    return 1;
}


