#include "CPU.h"

#include <stdio.h>

void print_CPU(struct CPU* cpu) {
    int i;
    puts("=============== CPU INFO ===============");
    puts("Program in CPU:");
    for (i = 0; i < (*cpu).prog.size; i++)
        printf("%s", (*cpu).prog.inst[i]);
    printf("\n");
    printf("Current program counter: %d\n", (*cpu).current_program_count);
    printf("Integer amount: %d\n", (*cpu).int_amount);
    if ((*cpu).allocated_int_amount) {
        for (i = 0; i < (*cpu).int_amount; i++)
            printf("Integer %d value: %d\n", i, (*cpu).integer_value[i]);
    }
    printf("Available time slice: %d\n", (*cpu).time_slice);
    printf("Used time slices: %d\n", (*cpu).used_time_slices);
}