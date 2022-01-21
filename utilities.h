#ifndef OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_UTILITIES_H
#define OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_UTILITIES_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "Process.h"

unsigned int minArrivalTime
(
		Process *processes[],
		unsigned int p_len
);

unsigned int findFirstProcessInQueue
(
		Process *processes[],
		unsigned int p_len,
		const bool status_period_0[p_len],
		const bool status_period_1[p_len]
);

unsigned int findShortestProcess
(
		Process *processes[],
		unsigned int p_len,
		unsigned int timeElapsed,
		const bool status_period_0[p_len],
		const bool status_period_1[p_len]
);

unsigned int findFirstProcessInLevel
(
		Process *processes[],
		unsigned int p_len,
		const bool isInLevel[2][p_len],
		unsigned int level,
		const bool status_period_0[p_len],
		const bool status_period_1[p_len]
);

#endif //OS_PROJECT_CPU_SCHEDULING_ALGORITHMS_UTILITIES_H
