#ifndef OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_ROUNDROBIN_H
#define OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_ROUNDROBIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Process.h"
#include "FCFS.h"

void roundRobin(Process *processes[],
				unsigned int p_len, unsigned int quantum,
				unsigned int *finishedTime,
				unsigned int *responseTime,
				int *ganttChart);

#endif //OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_ROUNDROBIN_H
