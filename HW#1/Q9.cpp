/*Write a program that takes as input a list of jobs (processes with their arrival time and 
CPU burst time and schedules them based on FCFS policy. It outputs the  <Process Id, arrival 
time, CPU burst time, completion time> for each of the jobs. Assume that  the jobs are 
listed in the order of their arrival time.*/

#include <stdio.h>

typedef struct {
    int processID; // process ID
    int arrival; // arrival time of the process
    int CPU_burst; // CPU burst time of the process
    int completion; // time of which the process is completed
} Process;

int main() 
{
    int n = 4;
    Process p[4];

    // reading 4 lines - processID arrival bursts
    for (int i = 0; i < n; i++) 
    {
        if (scanf("%d %d %d", &p[i].processID, &p[i].arrival, &p[i].CPU_burst) !=3)
        {
            return 1; // incase there is an error reading the input 
        };
    }

    // FCFS scheduling - running in the order that they are given (bonus! they are already in FCFS)
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        if(currentTime < p[i].arrival) 
        {
            currentTime = p[i].arrival; 
        }
        currentTime += p[i].CPU_burst;
        p[i].completion = currentTime; // setting the completion time for the process
    }

    printf("ProcessID Arrival Burst Completion\n");
    printf("\n%-10s %-10s %-10s %-10s\n", 
       "ProcessID", "Arrival", "Burst", "Completion");

    for (int i = 0; i < n; i++) 
    {
        printf("%-10d %-10d %-10d %-10d\n",
            p[i].processID,
            p[i].arrival,
            p[i].CPU_burst,
            p[i].completion);
    }

    return 0;
}