#include "Process.h"
struct Process
{
	unsigned int processID;
	unsigned int arrivalTime;
	unsigned int burstTime_FirstPeriod;
	unsigned int IOTime;
	unsigned int burstTime_SecondPeriod;
};

unsigned int getProcessID(const Process *process) { return process->processID; }
void setProcessID(Process *process, unsigned int _pid) { process->processID = _pid; }

unsigned int getArrivalTime(const Process *process) { return process->arrivalTime; }
void setArrivalTime(Process *process, unsigned int arrivalTime) { process->arrivalTime = arrivalTime; }

unsigned int getBurstTime(const Process *process, bool period)
{
	return (period == 0) ? process->burstTime_FirstPeriod : process->burstTime_SecondPeriod;
}
void setBurstTime(Process *process, bool period, unsigned int burstTime)
{
	(period == 0) ? (process->burstTime_FirstPeriod = burstTime) : (process->burstTime_SecondPeriod = burstTime);
}

unsigned int getIOTime(const Process *process) { return process->IOTime; }
void setIOTime(Process *process, unsigned int io_time) { process->IOTime = io_time; }

Process* createProcess(unsigned int pid, unsigned int at, unsigned int bt_1, unsigned int iot, unsigned int bt_2)
{
	Process *process = (Process*) malloc(sizeof(Process));
	setProcessID(process, pid);
	setArrivalTime(process, at);
	setBurstTime(process, 0, bt_1);
	setIOTime(process, iot);
	setBurstTime(process, 1, bt_2);
	return process;
}
