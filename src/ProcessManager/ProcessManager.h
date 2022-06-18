#ifndef _PROCESS_MANAGER_H_
#define _PROCESS_MANAGER_H_

#include "../Control/Control.h"
#include "../Process/Process.h"
#include "../ExecState/ExecState.h"
#include "../ReadyState/ReadyState.h"
#include "../BlockedState/BlockedState.h"
#include "../PCB/PCB.h"
#include "../CPU/CPU.h"
#include "../Time/Time.h"

void initialize(struct CPU*, struct ExecState*, struct ReadyState*, struct BlockedState*, struct PCB*, struct Time*);
struct Process create_first_process(struct Program*, struct Time*, int, int);
struct Process create_process(struct Time*, struct Process*, int);
struct Process put_process_CPU(struct CPU*, struct ReadyState*);
struct Process swap_process_CPU(struct CPU*, struct ReadyState*);
void exec(struct CPU*, struct ExecState*, struct ReadyState*, struct BlockedState*, struct PCB*, struct Process*, struct Time*);
void exec2(struct CPU*, struct ExecState*, struct ReadyState*, struct BlockedState*, struct PCB*, struct Process*, struct Time*);


#endif // _PROCESS_MANAGER_H_
