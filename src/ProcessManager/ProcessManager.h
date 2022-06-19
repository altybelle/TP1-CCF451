#ifndef _PROCESS_MANAGER_H_
#define _PROCESS_MANAGER_H_

#include "../CPU/CPU.h"
#include "../PCB/PCB.h"
#include "../Time/Time.h"
#include "../Control/Control.h"
#include "../Process/Process.h"
#include "../Program/Program.h"
#include "../ExecState/ExecState.h"
#include "../ReadyState/ReadyState.h"
#include "../BlockedState/BlockedState.h"

void initialize(struct CPU*, struct ExecState*, struct ReadyState*, struct BlockedState*, struct PCB*, struct Time*);
struct Process create_first_process(struct Program*, struct Time*, int, int);
struct Process create_process(struct Process*, struct Time*, int);
struct Process put_process_CPU(struct CPU*, struct ReadyState*);
struct Process swap_process_CPU(struct CPU*, struct ReadyState*);
void exec(struct CPU*, struct ExecState*, struct ReadyState*, struct BlockedState*, struct PCB*, struct Process*, struct Time*);
void exec2(struct CPU*, struct ExecState*, struct ReadyState*, struct BlockedState*, struct PCB*, struct Process*, struct Time*);
void print_whole_system(struct CPU*, struct ReadyState*, struct BlockedState*, struct PCB*);

#endif // _PROCESS_MANAGER_H_
