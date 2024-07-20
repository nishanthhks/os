#include <stdio.h>
#include <limits.h>

struct Process {
    int id;
    int bt;  // Burst Time
    int at;  // Arrival Time
    int q;   // Queue (1 for system, 2 for user)
    int wt;  // Waiting Time
    int tat; // Turnaround Time
    int rt;  // Response Time
    int st;  // Start Time
    int et;  // End Time
    int v;   // Visited flag
};

int main() {
    int n, ct = 0;  // Current time
    float awt = 0, atat = 0, art = 0, tp;  // Average metrics

    printf("Queue 1 is system process\nQueue 2 is User Process\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], temp;
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        p[i].v = 0;
        printf("Enter Burst Time, Arrival Time and Queue of P%d: ", i + 1);
        scanf("%d %d %d", &p[i].bt, &p[i].at, &p[i].q);
    }

    // Sort processes based on Arrival Time, and Queue priority in case of tie
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at || (p[i].at == p[j].at && p[i].q > p[j].q)) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int cf = p[0].bt;  // Completion time
    int min = INT_MAX, m, count = 0;
    p[0].v = 1;

    while (count < n - 1) {
        for (int i = 0; i < n; i++) {
            if (p[i].at <= cf && p[i].v == 0) {
                if (p[i].q < min) {
                    min = p[i].q;
                    m = i;
                }
            }
        }
        p[m].v = 1;
        cf += p[m].bt;
        min = INT_MAX;

        // Move the selected process to the next position
        temp = p[count + 1];
        p[count + 1] = p[m];
        p[m] = temp;

        count++;
    }

    printf("\nProcess\tWaiting Time\tTurnaround Time\tResponse Time\n");

    for (int i = 0; i < n; i++) {
        if (p[i].at < ct) {
            p[i].st = ct;
        } else {
            p[i].st = p[i].at;
        }
        p[i].et = p[i].st + p[i].bt;
        ct = p[i].et;

        p[i].tat = p[i].et - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].st - p[i].at;

        printf("%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].wt, p[i].tat, p[i].rt);
        awt += p[i].wt;
        atat += p[i].tat;
        art += p[i].rt;
    }

    tp = (float)n / p[n - 1].et;
    printf("Average Waiting Time: %.2f\n", awt / n);
    printf("Average Turnaround Time: %.2f\n", atat / n);
    printf("Average Response Time: %.2f\n", art / n);
    printf("Throughput: %.2f\n", tp);

    return 0;
}
