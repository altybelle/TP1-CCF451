#include "GerenciadorProcessos.h"

#include <stdio.h>

void imprime_CPU(CPU *cpu) {
    int i;
    puts("=============== CPU INFO ===============");
    printf("Programa na CPU: ");
    for (i = 0; i < cpu->prog.tamanho; i++)
        printf("%s\t", cpu->prog.instrucoes[i]);
    printf("\n");
    printf("Contador de Programa atual: %d\n", cpu->contador_programa);
    printf("Quantidade de variaveis: %d\n", cpu->quantidade_inteiros);
    if (cpu->valor_inteiro)
        for (i = 0; i < cpu->quantidade_inteiros; i++)
            printf("Valor inteiro da variavel %d: %d\n", i, cpu->valor_inteiro[i]);
    printf("Parcela de tempo disponivel: %d\n", cpu->parcela_tempo);
    printf("Parcela de tempo utilizada: %d\n", cpu->parcela_tempo_utilizada);
    puts("========================================");
}