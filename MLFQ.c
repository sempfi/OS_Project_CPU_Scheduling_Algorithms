#include "MLFQ.h"

void MLFQ(Process *processes[], unsigned int p_len, unsigned int quantum_0, unsigned int quantum_1,
		  unsigned int *finishedTime, unsigned int *responseTime, int *ganttChart)
{

	bool status_period_0[p_len];
	bool status_period_1[p_len];
	bool allocatedOnce[p_len];
	bool isInLevel[3][p_len];

	unsigned int quantum[] = {quantum_0, quantum_1};

	for (int i = 0; i < p_len; i++) {
		status_period_0[i] = false;
		status_period_1[i] = false;
		allocatedOnce[i] = false;

		isInLevel[0][i] = true;
		isInLevel[1][i] = false;
		isInLevel[2][i] = false;
	}

	unsigned int timeElapsed = minArrivalTime(processes, p_len);

	int level = 0;
	while (level < 3) {
		unsigned int currentProcess = findFirstProcessInLevel(processes, p_len,
															  isInLevel, level,
															  status_period_0, status_period_1);

		if (getArrivalTime(processes[currentProcess]) > timeElapsed) {
			if (getArrivalTime(processes[findFirstProcessInLevel(processes, p_len, isInLevel, level+1,
																 status_period_0, status_period_1)]) <= timeElapsed) {
				currentProcess = findFirstProcessInLevel(processes, p_len, isInLevel, level+1,
														 status_period_0, status_period_1);
				isInLevel[level][currentProcess] = true;
				isInLevel[level+1][currentProcess] = false;
			}
			else {
				for (unsigned int t = timeElapsed; t < getArrivalTime(processes[currentProcess]); t++) {
					// '-1' identifies idle state.
					ganttChart[t] = -1;
				}
				timeElapsed = getArrivalTime(processes[currentProcess]);
			}
		}
		if (!allocatedOnce[currentProcess]) {
			responseTime[currentProcess] = timeElapsed - getArrivalTime(processes[currentProcess]);
			allocatedOnce[currentProcess] = true;
		}

		bool period;
		if (!status_period_0[currentProcess]) {
			period = 0;
		}
		else if (status_period_0[currentProcess] && !status_period_1[currentProcess]) {
			period = 1;
		}

		//else { exit(1); }

		if ((level == 0 && isInLevel[0][currentProcess]) || (level == 1 && isInLevel[1][currentProcess])) {
			if (getBurstTime(processes[currentProcess], period) >= quantum[level]) {
				for (unsigned int t = timeElapsed; t < timeElapsed + quantum[level]; t++) {
					ganttChart[t] = (int) currentProcess;
				}
				setBurstTime(processes[currentProcess], period,
							 getBurstTime(processes[currentProcess], period) - quantum[level]);

				timeElapsed += quantum[level];
				setArrivalTime(processes[currentProcess], timeElapsed);
				isInLevel[0][currentProcess] = false;
				isInLevel[1][currentProcess] = true;
			}
			else {
				for (unsigned int t = timeElapsed; t < timeElapsed + getBurstTime(processes[currentProcess], period); t++) {
					ganttChart[t] = (int) currentProcess;
				}
				timeElapsed += getBurstTime(processes[currentProcess], period);
				setBurstTime(processes[currentProcess], period, 0);
			}
		}

		else if (level == 2 && isInLevel[2][currentProcess]) {
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

		if (period == 1 && getBurstTime(processes[currentProcess], 1) == 0) {
			status_period_1[currentProcess] = true;
			finishedTime[currentProcess] = timeElapsed;
			isInLevel[level][currentProcess] = false;
		}

		bool flag = false;
		for (int i = 0; i < p_len; i++) {
			if (isInLevel[level][i]) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			level++;
		}
	}
}
