#include <stdio.h>

// Function prototypes
void inputProcesses(int n, int proc_id[], int at[], int bt[]);
void calculateCompletionTime(int n, int at[], int bt[], int ct[]);
void calculateTurnaroundTime(int n, int at[], int ct[], int tat[]);
void calculateWaitingTime(int n, int bt[], int tat[], int wt[]);
void displayResults(int n, int proc_id[], int at[], int bt[], int ct[], int tat[], int wt[]);
void calculateAndDisplayAverages(int n, int tat[], int wt[]);

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int proc_id[n], at[n], bt[n], ct[n], tat[n], wt[n];

    // Input process details
    inputProcesses(n, proc_id, at, bt);

    // Calculate completion time
    calculateCompletionTime(n, at, bt, ct);

    // Calculate turnaround time
    calculateTurnaroundTime(n, at, ct, tat);

    // Calculate waiting time
    calculateWaitingTime(n, bt, tat, wt);

    // Display results
    displayResults(n, proc_id, at, bt, ct, tat, wt);

    // Calculate and display averages
    calculateAndDisplayAverages(n, tat, wt);

    return 0;
}

void inputProcesses(int n, int proc_id[], int at[], int bt[]) {
    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
        proc_id[i] = i + 1;
    }
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }
}

void calculateCompletionTime(int n, int at[], int bt[], int ct[]) {
    int c = 0, count = 0, min_bt_index, min_bt;
    int completed[n];

    // Initialize all processes as not completed
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    while (count < n) {
        min_bt = 1e9; // large value to ensure it gets overwritten

        // Find the process with the smallest burst time that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (at[i] <= c && !completed[i] && bt[i] < min_bt) {
                min_bt = bt[i];
                min_bt_index = i;
            }
        }

        // If no such process is found, advance time to the next process arrival
        if (min_bt == 1e9) {
            for (int i = 0; i < n; i++) {
                if (!completed[i]) {
                    c = at[i];
                    break;
                }
            }
            continue;
        }

        // Complete the selected process
        completed[min_bt_index] = 1;
        c += bt[min_bt_index];
        ct[min_bt_index] = c;
        count++;
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

void displayResults(int n, int proc_id[], int at[], int bt[], int ct[], int tat[], int wt[]) {
    printf("FCFS scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", proc_id[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

void calculateAndDisplayAverages(int n, int tat[], int wt[]) {
    double ttat = 0.0, twt = 0.0, avg_tat, avg_wt;

    for (int i = 0; i < n; i++) {
        ttat += tat[i];
        twt += wt[i];
    }

    avg_tat = ttat / n;
    avg_wt = twt / n;

    printf("\nAverage turnaround time: %lfms\n", avg_tat);
    printf("Average waiting time: %lfms\n", avg_wt);
}
