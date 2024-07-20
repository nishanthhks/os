#include <stdio.h>
#define MAX_PROCESSES 10

struct Process {
    int id;
    int at; // Arrival Time
    int bt; // Burst Time
    int wt; // Waiting Time
    int tat; // Turnaround Time
    int st; // Start Time
    int et; // End Time
    int rt; // Response Time
};

int main() {
    struct Process processes[MAX_PROCESSES];
    int n;
    int total_wt = 0;
    int total_tat = 0;
    int total_rt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
    }

    // Sorting processes by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].at > processes[j].at) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int curr_time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].st = processes[i].at < curr_time ? curr_time : processes[i].at;
        processes[i].et = processes[i].st + processes[i].bt;
        curr_time = processes[i].et;
    }

    for (int i = 0; i < n; i++) {
        processes[i].tat = processes[i].et - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        processes[i].rt = processes[i].st - processes[i].at;
    }

    for (int i = 0; i < n; i++) {
        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
        total_rt += processes[i].rt;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat, processes[i].rt);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Throughput: %.2f\n", (float)n / curr_time);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);

    return 0;
}
