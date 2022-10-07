#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

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
        for (int j = i + 1; j < processes_number; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                temp = processes[i].i;
                processes[i].i = processes[j].i;
                processes[j].i = temp; 

                temp = processes[i].arrival_time;
                processes[i].arrival_time = processes[j].arrival_time;
                processes[j].arrival_time = temp;

                temp = processes[i].burst_time;
                processes[i].burst_time = processes[j].burst_time;
                processes[j].burst_time = temp; 
            }
        }
    }
}

void 
sort_by_burst_time(process_t* processes) {
    double temp;
    for (int i = 0; i < processes_number - 1; i++) {
        for (int j = i + 1; j < processes_number; j++) {
            if ((processes[i].arrival_time == processes[j].arrival_time) && (processes[i].burst_time > processes[j].burst_time)) {
                temp = processes[i].i;
                processes[i].i = processes[j].i;
                processes[j].i = temp;

                temp = processes[i].arrival_time;
                processes[i].arrival_time = processes[j].arrival_time;
                processes[j].arrival_time = temp;
                
                temp = processes[i].burst_time;
                processes[i].burst_time = processes[j].burst_time;
                processes[j].burst_time = temp; 
            } else {
                continue;
            }
        }
    }
}

int 
main(int argc, char const *argv[]) {
    float average_tat, average_wt, arrival_time, burst_time;

    printf("Enter the number of processes: ");
    scanf("%d", &processes_number);
    printf("\n");

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
    sort_by_burst_time(processes);

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