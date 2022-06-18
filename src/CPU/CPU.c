#include "CPU.h"

#include <stdio.h>

void print_CPU(struct CPU* cpu) {
    int i;
    printf("=============== CPU INFO ===============");
    printf("Program in CPU:\n");
    for (i = 0; i < cpu->prog.size; i++)
        printf("%s\t", cpu->prog.inst[i]);
    printf("\n");
    printf("Current program counter: %d\n", cpu->current_program_count);
    printf("Integer amount: %d\n", cpu->integer_count);
    if (cpu->allocated_integers) {
        for (i = 0; i < cpu->integer_count; i++)
            printf("Integer %d value: %d\n", i, cpu->integer_value[i]);
    }
    printf("Available time slice: %d\n", cpu->time_slice);
    printf("Used time slices: %d\n", cpu->used_time_slices);
    puts("=========================================");
}