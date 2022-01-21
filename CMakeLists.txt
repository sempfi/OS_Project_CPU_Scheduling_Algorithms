cmake_minimum_required(VERSION 3.20)
project(OS_Project_CPU_Scheduling_Algorithms C)

set(CMAKE_C_STANDARD 99)

add_executable(OS_Project_CPU_Scheduling_Algorithms main.c FCFS.c FCFS.h Process.c Process.h RoundRobin.c RoundRobin.h SJF.c SJF.h MLFQ.c MLFQ.h utilities.c utilities.h)
