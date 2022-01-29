#include <stdio.h>
#include <stdlib.h>
#include "FCFS.h"
#include "RoundRobin.h"
#include "SRTF.h"
#include "MLFQ.h"
#include "SJF.h"

#define MAX_SIZE_PROCESSES 100
#define MAX_SIZE_CHARS 100
#define MAX_TIME 1000
#define quantum_RR 5
#define quantum_0_MLFQ 8
#define quantum_1_MLFQ 16

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

void callFunction (
		void (*ptr_FCFS_SJF_SRTF)(Process **, const unsigned int,unsigned int *, unsigned int *, int *),
		void (*ptr_RR)(Process **, const unsigned int, const int unsigned, unsigned int *, unsigned int *, int *),
		void (*ptr_MLFQ)(Process **, const unsigned int, const int unsigned, const unsigned int,
				unsigned int *, unsigned int *, int *),
		char *name
		)
{
	int *ganttChart = (int*) malloc(sizeof(int) * MAX_TIME);
	unsigned int *finishedTime = (unsigned int*) malloc(sizeof(unsigned int) * p_len);
	unsigned int *responseTime = (unsigned int*) malloc(sizeof(unsigned int) * p_len);
	unsigned int arrivalTime[p_len];
	unsigned int burstTime[2][p_len];
	unsigned int waitingTime[p_len];
	unsigned int turnaroundTime[p_len];
	unsigned int totalWaitingTime = 0;
	unsigned int completionTime = 0;
	unsigned int totalResponseTime = 0;
	unsigned int totalTurnaroundTime = 0;

	unsigned int begin = minArrivalTime(processes, p_len);

	for (int i = 0; i < p_len; i++) {
		arrivalTime[i] = getArrivalTime(processes[i]);
		burstTime[0][i] = getBurstTime(processes[i], 0);
		burstTime[1][i] = getBurstTime(processes[i], 1);
	}

	if (strcmp(name, "FCFS") == 0 || strcmp(name, "SJF") == 0 || strcmp(name, "SRTF") == 0)
		ptr_FCFS_SJF_SRTF(processes, p_len, finishedTime, responseTime, ganttChart);
	else if (strcmp(name, "RR") == 0)
		ptr_RR(processes, p_len, quantum_RR, finishedTime, responseTime, ganttChart);
	else if (strcmp(name, "MLFQ") == 0)
		ptr_MLFQ(processes, p_len, quantum_0_MLFQ, quantum_1_MLFQ, finishedTime, responseTime, ganttChart);

	for (int i = 0; i < p_len; i++) {
		Process *p = processes[i];
		waitingTime[i] = finishedTime[i] -
				arrivalTime[i] -
				burstTime[0][i] -
				getIOTime(p) -
				burstTime[1][i];
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
	for (unsigned int t = begin; t < completionTime; t++) {
		if (ganttChart[t] == -1) {
			idleTime++;
		}
	}
	float utilization = (1- (float) idleTime / (float) completionTime) * 100;
	float throughput = 1000 * ((float) p_len / (float) completionTime);
	printf("\n=====================\n\t%s\n=====================\n\n", name);
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

void call_FCFS () { callFunction(FCFS, NULL, NULL, "FCFS" ); }
void call_SJF  () { callFunction(SJF, NULL, NULL, "SJF");    }
void call_SRTF () { callFunction(SRTF, NULL, NULL, "SRTF"); }
void call_RR () { callFunction(NULL, roundRobin, NULL, "RR"); }
void call_MLFQ () { callFunction(NULL, NULL, MLFQ, "MLFQ"); }

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
	printf("Enter the method number (FCFS: 1, RR: 2, SJF: 3, SRTF: 4, MLFQ: 5):\n");
	int mode;
	scanf("%d", &mode);

	switch (mode) {
		case 1: call_FCFS(); break;
		case 2: call_RR(); break;
		case 3: call_SJF(); break;
		case 4: call_SRTF(); break;
		case 5: call_MLFQ(); break;
		default: break;
	}
	return 1;
}

int main()
{
	driver();
	return 0;
}
