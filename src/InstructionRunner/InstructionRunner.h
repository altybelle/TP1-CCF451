#ifndef _INSTRUCTION_RUNNER_H_
#define _INSTRUCTION_RUNNER_H_

#include "../ProcessManager/ProcessManager.h"

void run_instructions(struct CPU*, struct Process*, struct ExecState*, struct ReadyState*, struct BlockedState*, struct PCB*, struct Time*);  

#endif // _INSTRUCTION_RUNNER_H_
