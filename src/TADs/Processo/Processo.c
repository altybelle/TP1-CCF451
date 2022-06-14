#include "Processo.h"

void imprime_processo(Processo *proc) {
    puts("=============== Processo ===============");
    printf("PID: %d\n", proc->pid);
    printf("PID do Pai: %d\n", proc->pid_pai);
    printf("Estado: %s\n", proc->estado);
    printf("Prioridade: %d\n", proc->prioridade);
    printf("Tempo de Inicializacao: %d\n", proc->tempo_inicializacao);
    printf("Tempo de CPU: %d\n", proc->cota_cpu);
    imprimir_eproc(&proc->estado_processo);
    puts("========================================");
}