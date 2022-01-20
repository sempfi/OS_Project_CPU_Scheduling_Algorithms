#ifndef OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_FCFS_H
#define OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_FCFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "Process.h"


void FCFS (
		Process *processes[],
		unsigned int p_len,
		unsigned int *finishedTime,
		unsigned int *responseTime,
		int *ganttChart
);

unsigned int findFirstProcessInQueue (
			Process *processes[],
			unsigned int p_len,
			const bool status_period_0[p_len],
			const bool status_period_1[p_len]
);

#endif //OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_FCFS_H
