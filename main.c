#include <stdio.h>
#include <stdlib.h>
#include "FCFS.h"
#define MAX_SIZE_PROCESSES 100
#define MAX_SIZE_CHARS 100
#define MAX_TIME 1000

#define MAX(a,b) \
({ __typeof__ (a) _a = (a); \
 __typeof__ (b) _b = (b); \
 _a > _b ? _a : _b; })

Process *processes[MAX_SIZE_PROCESSES];
unsigned int p_len;
void addProcess(Process *p)
{
	processes[p_len] = p;
	p_len++;
}

void call_FCFS() {
	int *ganttChart = (int*) malloc(sizeof(int) * MAX_TIME);
	unsigned int *finishedTime = (unsigned int*) malloc(sizeof(unsigned int) * p_len);
	unsigned int *responseTime = (unsigned int*) malloc(sizeof(unsigned int) * p_len);
	unsigned int arrivalTime[p_len];
	unsigned int waitingTime[p_len];
	unsigned int turnaroundTime[p_len];
	unsigned int totalWaitingTime = 0;
	unsigned int completionTime = 0;
	unsigned int totalResponseTime = 0;
	unsigned int totalTurnaroundTime = 0;

	for (int i = 0; i < p_len; i++) {
		arrivalTime[i] = getArrivalTime(processes[i]);
	}

	FCFS(processes, p_len, finishedTime, responseTime, ganttChart);

	for (int i = 0; i < p_len; i++) {
		Process *p = processes[i];
		waitingTime[i] = finishedTime[i] -
				arrivalTime[i] -
				getBurstTime(p, 0) -
				getIOTime(p) -
				getBurstTime(p, 1);
		turnaroundTime[i] = finishedTime[i] - arrivalTime[i];

		totalTurnaroundTime += turnaroundTime[i];
		totalWaitingTime += waitingTime[i];
		totalResponseTime += responseTime[i];

		completionTime = MAX(completionTime, finishedTime[i]);
	}
	float avgResponseTime = ((float) totalResponseTime) / ((float) p_len);
	float avgTurnaroundTime = ((float) totalTurnaroundTime) / ((float) p_len);
	float avgWaitingTime = ((float) totalWaitingTime) / ((float) p_len);

	unsigned int idleTime = 0;
	for (int t = 0; t < completionTime; t++) {
		if (ganttChart[t] == -1) {
			idleTime++;
		}
	}
	float utilization = (1- (float) idleTime / (float) completionTime) * 100;
	float throughput = 1000 * ((float) p_len / (float) completionTime);
	printf("\n=====================\n\tFCFS\n=====================\n\n");
	printf("---------------------------------------------------------------------\n");
	printf("Process ID \t Response Time \t Turnaround Time \t Waiting Time\n");
	for (int i = 0; i < p_len; i++) {
		printf("P%u \t\t %u \t\t %u \t\t\t %u\n", getProcessID(processes[i]), responseTime[i],
			   turnaroundTime[i], waitingTime[i]);
	}
	printf("---------------------------------------------------------------------\n");
	printf("Average: \t%f \t%f \t\t%f", avgResponseTime, avgTurnaroundTime, avgWaitingTime);

	printf("\n\nTotal Time: %u\n", completionTime);
	printf("Idle Time: %u\n", idleTime);
	printf("Burst Time: %u\n", completionTime - idleTime);
	printf("CPU Utilization: %f %%\n", utilization);
	printf("Throughput: %f\n", throughput);
}

void readFile()
{
	FILE *input = fopen("H:\\Books\\Codes\\OS-Project-CPU-Scheduling-Algorithms\\process_inputs.csv","r");
	char str[MAX_SIZE_CHARS];
	fgets(str, MAX_SIZE_CHARS, input);

	unsigned int pid, at, bt_1, iot, bt_2;

	while (fscanf(input, "%d,%d,%d,%d,%d\n", &pid, &at, &bt_1, &iot, &bt_2) == 5) {
		addProcess(createProcess(pid, at, bt_1, iot, bt_2));
	}
	fclose(input);
}

int driver()
{
	readFile();
	call_FCFS();
	return 1;
}

int main()
{
	driver();
	return 0;
}
