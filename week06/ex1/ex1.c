#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int processes_number;

typedef struct Process {
    int i;
    float arrival_time;
    float burst_time;
    float completion_time;
    float turnaround_time;
    float waiting_time
}process_t;

void 
sort_by_arrival_time(process_t* processes) {
    double temp;
    for (int i = 0; i < processes_number - 1; i++) {
        if (processes[i].arrival_time > processes[i+1].arrival_time) {
            temp = processes[i].i;
            processes[i].i = processes[i+1].i;
            processes[i+1].i = temp; 

            temp = processes[i].arrival_time;
            processes[i].arrival_time = processes[i+1].arrival_time;
            processes[i+1].arrival_time = temp;

            temp = processes[i].burst_time;
            processes[i].burst_time = processes[i+1].burst_time;
            processes[i+1].burst_time = temp; 
        }
    }
}

int 
main(int argc, char const *argv[]) {
    float average_tat, average_wt, arrival_time, burst_time;

    printf("Enter the number of processes: ");
    scanf("%d", &processes_number);
    printf("\n");

    // process_t* processes = calloc(processes_number, sizeof(process_t));
    process_t processes[processes_number];
    for (int i = 0; i < processes_number; i++) {
        processes[i].i = i;
        printf("Enter the arrival time of process %d: ", i);
        scanf("%e", &arrival_time);
        processes[i].arrival_time = arrival_time;
        printf("Enter the burst time of process %d: ", i);
        scanf("%e", &burst_time);
        printf("\n");
        processes[i].burst_time = burst_time;
    }

    sort_by_arrival_time(processes);

    for (int i = 0; i < processes_number; i++) {
        if (i == 0) {
            processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
            processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        } else {
            processes[i].completion_time = processes[i-1].completion_time + processes[i].burst_time;
            processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        }
        average_tat += processes[i].turnaround_time;
        average_wt += processes[i].waiting_time;
    }

    average_tat /= processes_number;
    average_wt /= processes_number;

    for (int i = 0; i < processes_number; i++) {
        printf("Process #%d\tCompletion time: %.2f\tTurnaround time: %.2f\t Waiting time: %.2f\t Arrival time: %.2f\t Burst time: %.2f\n", 
        processes[i].i, processes[i].completion_time, processes[i].turnaround_time,
        processes[i].waiting_time, processes[i].arrival_time, processes[i].burst_time);
    }

    printf("\nAverage Turnaround time: %.2f\n", average_tat);
    printf("Average waiting time: %.2f\n", average_wt);
    
    return 0;
}
/*  
    Completion time = Burst time + Arrival time
    Turnaround time = Completion time - Arrival time
    Waiting time = Turnaround time - Burst time
*/