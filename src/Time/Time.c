#include "Time.h"

#include <stdio.h>

void print_average_cycle_time(struct Time* time) {
    double avg_time = 0;
    avg_time = ((*time).time / (*time).created_processes_amount); // mostra a media do tempo gasto para cada processo criado
    printf("The average cycle time was %.2lf.\n", avg_time); 
}