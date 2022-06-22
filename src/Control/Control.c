#include "./Control.h"
#include "../Common.h"
#include "../ProcessManager/ProcessManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int execute_control(){
    FILE *f;
    int pid;
    struct Program prog;
    Instructions inst;
    int desc[2], s_desc[2]; 
    char sent[BUFFER], received[BUFFER];
    int inst_amount = 0;
    
    if (pipe(desc) < 0) { 
        perror("Error: Pipe error.");
        return -1; 
    }
    if ((pid = fork()) < 0){ 
        perror("Error: Fork error.");
        exit(1);
    }
  
    if (pid > 0) {
        close(desc[0]);
        int a = 0;
        while (a != 1 && a != 2) {
            printf("Do you wanna use file mode (1) or interactive mode (2)? R: ");
            scanf("%d", &a);
            if (a != 1 && a != 2) {
                printf("\nError: Invalid input!\n");
            }
        }
        
        if (a == 1) {
            read_file(sent); 
        } else {
            read_terminal(sent);
        }
        
        printf("String sent from Control %i to the Manager. Content: %s\n", getpid(), sent);
        write(desc[1], sent, sizeof(sent) + 1);
        exit(0);
        return 1; 
    }
    
    int dequeued;
    struct CPU cpu;
    struct ExecState exec;
    struct ReadyState rs;
    struct BlockedState bs;
    struct PCB pcb;
    struct Time time;
    struct Process u_proc;

    if (pipe(s_desc) < 0) {
        perror("Error: Pipe error.");
        return -1;
    }
    initialize(&cpu, &exec, &rs, &bs, &pcb, &time);

    f = fopen("./FILES/INPUT/PROG.txt", "r");

    if (!f) {
        puts("Error: coudln't open PROG.txt file.");
    } else {
        while((fgets(inst, sizeof(inst), f))){
                enqueue_program(&prog, inst);
                inst_amount++;
            }
        fclose(f);
    }

    prog.size = inst_amount;

    struct Process proc = create_first_process(&prog, &time, inst_amount, getpid());

    close(desc[1]);
    read(desc[0],  received, sizeof(received));
    printf("String received from PID %i Manager and sent from Control. Content: '%s'\n", getpid(), received);
    enqueue_ready_state(&rs, &proc);
    enqueue_PCB(&pcb, &proc);

    proc = put_process_CPU(&cpu, &rs);
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
        scanf("%c",&command);
        sent[i] = command;
        strcat(sent, " ");
        i += 2;
    } while (command != 'M');
}

int read_file(char *sent){
    FILE *f;
    char str[2];
    f = fopen("./FILES/INPUT/CTRL.txt","r");
    if (!f){
      puts("Error: couldn't open CTRL file.");
      return 0;
    } 
      
    while(fscanf(f, "%s", str) != EOF) {
        strcat(sent, str);
        strcat(sent, " ");
    }
    
    fclose(f);
    return 1;
}


