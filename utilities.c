#include "utilities.h"

unsigned int minArrivalTime(Process *processes[], const unsigned int p_len)
{
	unsigned int minimum = UINT_MAX;
	for (int i = 0; i < p_len; i++) {
		if (getArrivalTime(processes[i]) < minimum) {
			minimum = getArrivalTime(processes[i]);
		}
	}
	return minimum;
}

unsigned int findFirstProcessInQueue(Process *processes[], const unsigned int p_len,
									 const bool status_period_0[p_len], const bool status_period_1[p_len])
{
	unsigned int minimum = UINT_MAX;
	unsigned int index;
	for (int i = 0; i < p_len; i++) {
		if (getArrivalTime(processes[i]) < minimum && !(status_period_0[i] && status_period_1[i])) {
			minimum = getArrivalTime(processes[i]);
			index = i;
		}
	}
	return index;
}

unsigned int findShortestProcess (Process *processes[], unsigned int p_len, unsigned int timeElapsed,
								  const bool status_period_0[p_len], const bool status_period_1[p_len])

{
	unsigned int minimum = UINT_MAX;
	unsigned int index;

	bool flag = false;
	for (int i = 0; i < p_len; i++) {
		if (getArrivalTime(processes[i]) <= timeElapsed) {
			if (getBurstTime(processes[i], 0) < minimum && !status_period_0[i] && !status_period_1[i]) {
				minimum = getBurstTime(processes[i], 0);
				index = i;
				flag = true;
			}
			else if (getBurstTime(processes[i], 1) < minimum && status_period_0[i] && !status_period_1[i]) {
				minimum = getBurstTime(processes[i], 1);
				index = i;
				flag = true;
			}
		}
	}
	if (flag) {
		return index;
	}

	for (int i = 0; i < p_len; i++) {
		if (getArrivalTime(processes[i]) - timeElapsed < minimum && !status_period_0[i] && !status_period_1[i]) {
			minimum = getArrivalTime(processes[i]) - timeElapsed;
			index = i;
		} else if (getArrivalTime(processes[i]) - timeElapsed < minimum && status_period_0[i] && !status_period_1[i]) {
			minimum = getArrivalTime(processes[i]) - timeElapsed;
			index = i;
		}
	}
	return index;
}

unsigned int findFirstProcessInLevel(Process *processes[], unsigned int p_len,
									 const bool isInLevel[2][p_len], unsigned int level,
									 const bool status_period_0[p_len], const bool status_period_1[p_len])
{
	unsigned int minimum = UINT_MAX;
	unsigned int index;

	for (int l = 0; l < 3; l++) {
		for (int i = 0; i < p_len; i++) {
			if (l == level && isInLevel[level][i]) {
				if (getArrivalTime(processes[i]) < minimum && !(status_period_0[i] && status_period_1[i])) {
					minimum = getArrivalTime(processes[i]);
					index = i;
				}
			}
		}
	}
	return index;
}