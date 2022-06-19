#ifndef _TIME_H_
#define _TIME_H_

struct Time {
    int time;
    int created_processes_amount;
};

void print_average_cycle_time(struct Time*);

#endif // _TIME_H_