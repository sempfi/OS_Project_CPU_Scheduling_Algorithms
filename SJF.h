#ifndef OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_SJF_H
#define OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_SJF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "Process.h"
#include "utilities.h"

void SJF
(
		Process *processes[],
		unsigned int p_len,
		unsigned int *finishedTimeProcesses,
		unsigned int *responseTime,
		int *ganttChart
);

#endif //OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_SJF_H
