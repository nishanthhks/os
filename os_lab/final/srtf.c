#include <stdio.h>
#include <limits.h>

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
    int vi; // Visit Indicator
    int obt; // Original Burst Time
};

int main() {
    struct Process p[MAX_PROCESSES];
    int n;
    int total_wt = 0;
    int total_tat = 0;
    int total_rt = 0;
    int total_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].obt = p[i].bt;
        p[i].st = -1;
        p[i].et = -1;
        p[i].vi = 0;
    }

    int count = 0;
    int i = 0;

    while (1) {
        int min_bt = INT_MAX;
        int ind = -1;
        for (int j = 0; j < n; j++) {
            if (p[j].at <= i && p[j].bt > 0 && p[j].bt < min_bt) {
                min_bt = p[j].bt;
                ind = j;
            } else if (p[j].at <= i && p[j].bt > 0 && p[j].bt == min_bt) {
                if (p[j].at < p[ind].at) {
                    ind = j;
                }
            }
        }
        if (ind == -1) {
            i++;
            continue;
        }
        p[ind].bt -= 1;
        if (p[ind].st == -1) {
            p[ind].st = i;
        }
        if (p[ind].bt == 0) {
            count += 1;
            p[ind].et = i + 1;
            total_time = i + 1;
        }
        if (count == n) {
            break;
        }
        i++;
    }

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].et - p[i].at;
        p[i].wt = p[i].tat - p[i].obt;
        p[i].rt = p[i].st - p[i].at;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        total_rt += p[i].rt;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].obt, p[i].wt, p[i].tat, p[i].rt);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Throughput: %.2f\n", (float)n / total_time);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);

    return 0;
}
