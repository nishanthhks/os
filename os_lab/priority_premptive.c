#include <stdio.h>

// Function prototypes
void sortProcesses(int proc_id[], int p[], int at[], int bt[], int b[], int n);
void inputProcesses(int n, int proc_id[], int p[], int at[], int bt[], int b[], int m[], int rt[]);
void calculateCompletionTime(int n, int proc_id[], int p[], int at[], int bt[], int b[], int ct[], int m[], int rt[]);
void calculateTurnaroundTime(int n, int at[], int ct[], int tat[]);
void calculateWaitingTime(int n, int bt[], int tat[], int wt[]);
void displayResults(int n, int proc_id[], int p[], int at[], int bt[], int ct[], int tat[], int wt[], int rt[]);
void calculateAndDisplayAverages(int n, int tat[], int wt[]);

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int proc_id[n], at[n], bt[n], ct[n], tat[n], wt[n], m[n], b[n], rt[n], p[n];
    double avg_tat = 0.0, ttat = 0.0, avg_wt = 0.0, twt = 0.0;

    // Input process details
    inputProcesses(n, proc_id, p, at, bt, b, m, rt);

    // Sort processes based on priority
    sortProcesses(proc_id, p, at, bt, b, n);

    // Calculate completion time
    calculateCompletionTime(n, proc_id, p, at, bt, b, ct, m, rt);

    // Calculate turnaround time
    calculateTurnaroundTime(n, at, ct, tat);

    // Calculate waiting time
    calculateWaitingTime(n, bt, tat, wt);

    // Display results
    displayResults(n, proc_id, p, at, bt, ct, tat, wt, rt);

    // Calculate and display averages
    calculateAndDisplayAverages(n, tat, wt);

    return 0;
}

void sortProcesses(int proc_id[], int p[], int at[], int bt[], int b[], int n) {
    int min, temp;
    for (int i = 0; i < n; i++) {
        min = p[i];
        for (int j = i; j < n; j++) {
            if (p[j] < min) {
                // Swap arrival times
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap burst copy times
                temp = b[i];
                b[i] = b[j];
                b[j] = temp;

                // Swap priorities
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;

                // Swap process IDs
                temp = proc_id[i];
                proc_id[i] = proc_id[j];
                proc_id[j] = temp;

                min = p[i]; // Update min value after swap
            }
        }
    }
}

void inputProcesses(int n, int proc_id[], int p[], int at[], int bt[], int b[], int m[], int rt[]) {
    for (int i = 0; i < n; i++) {
        proc_id[i] = i + 1;
        m[i] = 0;
    }
    printf("Enter priorities:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        b[i] = bt[i];
        m[i] = -1;
        rt[i] = -1;
    }
}

void calculateCompletionTime(int n, int proc_id[], int p[], int at[], int bt[], int b[], int ct[], int m[], int rt[]) {
    int c = 0, count = 0, priority, x;
    while (count < n) {
        priority = -1;
        x = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= c && m[i] != 1 && (x == -1 || p[i] > priority)) {
                x = i;
                priority = p[i];
            }
        }

        if (x == -1) {
            c++;
            continue;
        }

        if (rt[x] == -1) {
            rt[x] = c - at[x];
        }

        if (at[x] <= c) {
            c += 1;
            b[x]--;
        } else {
            c = at[x] + 1;
            b[x]--;
        }

        if (b[x] == 0) {
            ct[x] = c;
            m[x] = 1;
            count++;
        }
    }
}

void calculateTurnaroundTime(int n, int at[], int ct[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
    }
}

void calculateWaitingTime(int n, int bt[], int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
    }
}

void displayResults(int n, int proc_id[], int p[], int at[], int bt[], int ct[], int tat[], int wt[], int rt[]) {
    printf("\nPriority scheduling (Pre-Emptive):\n");
    printf("PID\tPrior\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc_id[i], p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }
}

void calculateAndDisplayAverages(int n, int tat[], int wt[]) {
    double ttat = 0.0, twt = 0.0;
    for (int i = 0; i < n; i++) {
        ttat += tat[i];
        twt += wt[i];
    }
    double avg_tat = ttat / n;
    double avg_wt = twt / n;
    printf("\nAverage turnaround time: %lfms\n", avg_tat);
    printf("Average waiting time: %lfms\n", avg_wt);
}
