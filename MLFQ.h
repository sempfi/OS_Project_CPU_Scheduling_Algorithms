#ifndef OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_MLFQ_H
#define OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_MLFQ_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "Process.h"
#include "FCFS.h"
#include "RoundRobin.h"
#include "utilities.h"

void MLFQ
(
		Process *processes[],
		unsigned int p_len,
		unsigned int quantum_0,
		unsigned int quantum_1,
		unsigned int *finishedTime,
		unsigned int *responseTime,
		int *ganttChart
);

#endif //OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_MLFQ_H
