#ifndef _CPU_H_
#define _CPU_H_

#include "../Program/Program.h"

struct CPU {
  struct Program prog;
  int current_program_count;
  int *integer_value;
  int allocated_integers;
  int integer_count;
  int time_slice;
  int used_time_slices;
};

void print_CPU(struct CPU*);

#endif // _CPU_H_
