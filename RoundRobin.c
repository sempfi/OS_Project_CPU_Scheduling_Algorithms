#include "RoundRobin.h"

void roundRobin(Process *processes[], unsigned int p_len, unsigned int quantum,
				unsigned int *finishedTime, unsigned int *responseTime, int *ganttChart)
{
	bool status_period_0[p_len];
	bool status_period_1[p_len];
	bool allocatedOnce[p_len];
	bool allFinished = false;

	for (int i = 0; i < p_len; i++) {
		status_period_0[i] = false;
		status_period_1[i] = false;
		allocatedOnce[i] = false;
	}

	unsigned int timeElapsed = minArrivalTime(processes, p_len);

	while (!allFinished) {

		// Retain the earliest process in the ready queue.
		unsigned int currentProcess = findFirstProcessInQueue(processes, p_len, status_period_0, status_period_1);
		if (!allocatedOnce[currentProcess]) {
			responseTime[currentProcess] = timeElapsed - getArrivalTime(processes[currentProcess]);
			allocatedOnce[currentProcess] = true;
		}

		// Checking if we have some idle CPU time by comparing the time in which the last process gave up the CPU,
		// And the new process has arrived.
		if (getArrivalTime(processes[currentProcess]) > timeElapsed) {
			for (unsigned int t = timeElapsed; t < getArrivalTime(processes[currentProcess]); t++) {
				// '-1' identifies idle state.
				ganttChart[t] = -1;
			}
			timeElapsed = getArrivalTime(processes[currentProcess]);
		}

		// The variable "period" identifies which burst time must happen.
		bool period;
		if (!status_period_0[currentProcess]) {
			period = 0;
		}
		else if (status_period_0[currentProcess] && !status_period_1[currentProcess]) {
			period = 1;
		}

		else { exit(1); }

		if (getBurstTime(processes[currentProcess], period) > quantum) {
			for (unsigned int t = timeElapsed; t < timeElapsed + quantum; t++) {
				ganttChart[t] = (int) currentProcess;
			}
			setBurstTime(processes[currentProcess], period,
						 getBurstTime(processes[currentProcess], period) - quantum);

			timeElapsed += quantum;
			setArrivalTime(processes[currentProcess], timeElapsed);
		}
		else {
			for (unsigned int t = timeElapsed; t < timeElapsed + getBurstTime(processes[currentProcess], period); t++) {
				ganttChart[t] = (int) currentProcess;
			}
			timeElapsed += getBurstTime(processes[currentProcess], period);
			setBurstTime(processes[currentProcess], period, 0);
		}

		if (period == 0 && getBurstTime(processes[currentProcess], 0) == 0) {
			status_period_0[currentProcess] = true;
			setArrivalTime(processes[currentProcess], timeElapsed + getIOTime(processes[currentProcess]));
		}

		// After the second period is done, the process is finished, and we can store the time
		// in which the process ended.
		if (period == 1 && getBurstTime(processes[currentProcess], 1) == 0) {
			status_period_1[currentProcess] = true;
			finishedTime[currentProcess] = timeElapsed;
		}

		bool flag = false;
		for (int i = 0; i < p_len; i++) {
			if (!status_period_0[i] || !status_period_1[i]) {
				flag = true;
				break;
			};
		}
		allFinished = !flag;
	}
}
