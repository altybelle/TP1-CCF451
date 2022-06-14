#include "Controle.h"
#include "../Processo/Processo.h"
#include "../Programa/Programa.h"
#include "../TabelaPCB/TabelaPCB.h"
#include "../GerenciadorProcessos/GerenciadorProcessos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int executa_controle() {
    int i;
    signed int pid;
    int desc[2], desc_f[2];
    
    char entrada[STRING_MAX], saida[STRING_MAX];
    ConjuntoInstrucoes instrucoes;

    FILE *arq;
    Programa *prog;
    int quantidade_instrucoes = 0;

    if (pipe(desc) < 0) {
        perror("Falha no processo de PIPE.\n");
        return FAILURE;
    }

    if ((pid = fork()) < 0) {
        perror("Falha no processo de FORK.\n");
        exit(FAILURE);
    }

    if (pid > 0) {
        close(desc[0]);
        le_arquivo(saida);

        printf("Controle enviou seguinte string para o Gerenciador sob o PID %i: %s\n", getpid(), saida);

        write(desc[1], saida, sizeof(saida) + 1);
        exit(SUCCESS);
        return 1;
    } else {
        EstadoEmExecucao exec;
        EstadoBloqueado *eb;
        EstadoPronto *ep;
        TabelaPCB *pcb;
        Tempo tempo;
        CPU cpu;

        Processo processo_livre;

        if (pipe(desc_f) < 0) {
            perror("Falha no processo de PIPE.\n");
            return FAILURE;
        }

        // TODO: Inicializar gerenciador

        arq = fopen("Arquivos/Entrada/prog.txt", "r");
        
        if (!arq) { 
            printf("Não foi possivel abrir o arquivo 'prog.txt'.\n");
        } else {
            while ((fgets(instrucoes, sizeof(instrucoes), arq))) {
                inserir_prog(&prog, instrucoes);
                quantidade_instrucoes++;
            }
            fclose(arq);
        }

        prog->tamanho = quantidade_instrucoes;
        // TODO: Criar primeiro processo simulado
        // Processo proc = criar_processo_simulado();

        close(desc[1]);

        read(desc[0], entrada, sizeof(entrada));
        printf("Gerenciador recebeu a seguinte string enviada pelo Controle sob PID %i: %s\n", getpid(), entrada);

        // inserir_ep(&ep, proc);
        // inserir_pcb(&pcb, proc);

        // TODO: Colocar processo na CPU
        // proc = inserir_processo_CPU(cpu, ep);

        for (i = 0; i < strlen(entrada); i++) {
            switch(entrada[i]) {
                case 'U':
                    // TODO: exec(&tempo, &cpu, &exec, eb, ep, &proc);
                    break;
                case 'L':
                    // TODO:
                    // EstadoBloqueado *primeiro_eb = remover_eb(&eb);
                    // if (primeiro_eb) {
                    //      inserir_ep(&ep, processo_livre);   
                    // }
                case 'I':
                    // TODO: Imprimir estado atual do sistema
                    break;
                case 'M':
                    // TODO: Imprimir tempo médio e ciclo
                    exit(0);
                    break;
            }
        }
    }
    return SUCCESS;
}

int le_arquivo(char *saida) {
    FILE *arq = fopen("Arquivos/Entrada/ctrl.txt", "r");
    char dados[2];
    if (!arq) return FAILURE;

    while (fscanf(arq, "%s", dados) != EOF) {
        strcat(saida, dados);
        strcat(saida, " ");
    }
    fclose(arq);
    return SUCCESS;
}