#include "SRTF.h"
#define MAX_TIME 1000

void SRTF(Process *processes[], unsigned int p_len,
		 unsigned int *finishedTime, unsigned int *responseTime, int *ganttChart)
{
	bool status_period_0[p_len];
	bool status_period_1[p_len];
	bool allFinished = false;
	bool allocatedOnce[p_len];
	for (int i = 0; i < p_len; i++) {
		status_period_0[i] = false;
		status_period_1[i] = false;
		allocatedOnce[i] = false;
	}

	unsigned int timeElapsed = minArrivalTime(processes, p_len);

	while (!allFinished) {
		unsigned int currentProcess = findShortestProcess(processes, p_len, timeElapsed,
														  status_period_0, status_period_1);

		if (getArrivalTime(processes[currentProcess]) > timeElapsed) {
			for (unsigned int s = timeElapsed; s < getArrivalTime(processes[currentProcess]); s++) {
				// '-1' identifies idle state.
				ganttChart[s] = -1;
			}
			timeElapsed = getArrivalTime(processes[currentProcess]);
		}

		if (!allocatedOnce[currentProcess]) {
			responseTime[currentProcess] = timeElapsed - getArrivalTime(processes[currentProcess]);
			allocatedOnce[currentProcess] = true;
		}

		// The variable "period" identifies which burst time must happen.
		bool period;
		if (!status_period_0[currentProcess]) {
			period = 0;
		}
		else if (status_period_0[currentProcess] && !status_period_1[currentProcess]) {
			period = 1;
		}

		else {
			exit(1);
		}

		ganttChart[timeElapsed] = (int) currentProcess;
		timeElapsed++;

		// After the first period is done, we update the arrival time of the process with the time the process would
		// come back from the IO.
		setBurstTime(processes[currentProcess], period,
					 getBurstTime(processes[currentProcess], period)-1);


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
			if (status_period_0[i] == false || status_period_1[i] == false) {
				flag = true;
				break;
			};
		}
		allFinished = !flag;
	}
}

