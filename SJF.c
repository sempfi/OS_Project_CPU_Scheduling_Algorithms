#include "SJF.h"
#define MAX_TIME 1000

void SJF(Process *processes[], unsigned int p_len,
		 unsigned int *finishedTime, unsigned int *responseTime, int *ganttChart)
{
	bool status_period_0[p_len];
	bool status_period_1[p_len];
	bool allFinished = false;
	for (int i = 0; i < p_len; i++) {
		status_period_0[i] = false;
		status_period_1[i] = false;
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

			// The variable "period" identifies which burst time must happen.
			bool period;
			if (!status_period_0[currentProcess]) {
				period = 0;
				responseTime[currentProcess] = timeElapsed - getArrivalTime(processes[currentProcess]);
			}
			else if (status_period_0[currentProcess] && !status_period_1[currentProcess]) {
				period = 1;
			}

			// It does NOT happen, but if we have unexpected values, it will exit.
			else { exit(1); }


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

			// Checking if all processes have been completed.
		}


	}
unsigned int findShortestProcess (Process *processes[], unsigned int p_len, unsigned int timeElapsed,
								  const bool status_period_0[p_len], const bool status_period_1[p_len])

{
	unsigned int minimum = UINT_MAX;
	unsigned int index;

	for (int i = 0; i < p_len; i++) {
		if (getArrivalTime(processes[i]) <= timeElapsed) {

			if (getBurstTime(processes[i], 0) < minimum && !status_period_0[i] && !status_period_1[i]) {
				minimum = getBurstTime(processes[i], 0);
				index = i;
			}
			else if (getBurstTime(processes[i], 1) < minimum && status_period_0[i] && !status_period_1[i]) {
				minimum = getBurstTime(processes[i], 1);
				index = i;
			}

		}
	}
	return index;
}


