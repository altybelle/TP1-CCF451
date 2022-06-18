#ifndef _PROCESS_STATE_H_
#define _PROCESS_STATE_H_

#include "../Common.h"

struct ProcessState {
    int *integer;
    Instructions prog[20];
    int int_amount;
    int allocated_int_amount;
    int count;
    int size;
} ProcessState;

#endif // PROCESS_STATE_H_