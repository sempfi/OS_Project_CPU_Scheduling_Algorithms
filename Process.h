#ifndef OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_PROCESS_H
#define OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Process Process;

unsigned int getProcessID(const Process *process);
void setProcessID(Process *process, unsigned int _pid);

unsigned int getArrivalTime(const Process *process);
void setArrivalTime(Process *process, unsigned int arrivalTime);

unsigned int getBurstTime(const Process *process, bool period);
void setBurstTime(Process *process, bool period, unsigned int burstTime);

unsigned int getIOTime(const Process *process);
void setIOTime(Process *process, unsigned int io_time);

Process* createProcess(unsigned int pid, unsigned int at, unsigned int bt_1, unsigned int iot, unsigned int bt_2);

#endif //OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_PROCESS_H
