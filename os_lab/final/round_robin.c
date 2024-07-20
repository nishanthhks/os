#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

struct Process {
    int id;
    int at;
    int bt;
    int wt;
    int tat;
    int st;
    int et;
    int rt;
    int vi;
    int obt;
};

int main() {
    struct Process p[MAX_PROCESSES];
    int n;
    int total_wt = 0;
    int total_tat = 0;
    int total_rt = 0;
    int total_time = 0;
    int tq = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);

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
    int ind = 0;
    int curr_time = 0;

    while (1) {
        int skipped = 0;

        if (p[ind].at > curr_time) {
            ind = (ind + 1) % n;
            continue;
        }

        if (p[ind].st == -1) {
            p[ind].st = curr_time;
        }

        if (p[ind].bt > tq) {
            p[ind].bt -= tq;
            skipped = tq;
        } else if (p[ind].bt > 0) {
            skipped = p[ind].bt;
            p[ind].bt = 0;
            p[ind].et = curr_time + skipped;
            total_time = curr_time + skipped;
            count++;
        }

        curr_time += skipped;
        ind = (ind + 1) % n;

        if (count == n) {
            break;
        }
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
