#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "../Common.h"

struct Program {
  Instructions inst[20];
  int back, front;
  int size;
} Program;

void initialize_program(struct Program*);
int is_program_empty(struct Program*);
void enqueue_program(struct Program*, char*);
int dequeue_program(struct Program *, char*, int);

#endif // _PROGRAM_H_
