#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int T;  // Period
    int C;  // Execution time
    int D;  // Deadline (equal to period for RMS)
    int R;  // Remaining execution time
    int id; // Task ID
} Task;

// Function to input tasks
void input(Task tasks[], int *n) {
    printf("Enter number of tasks: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        tasks[i].id = i + 1;
        printf("Enter period (T) of task %d: ", i + 1);
        scanf("%d", &tasks[i].T);
        printf("Enter execution time (C) of task %d: ", i + 1);
        scanf("%d", &tasks[i].C);
        tasks[i].D = tasks[i].T; // For RMS, deadline is the same as period
        tasks[i].R = tasks[i].C; // Initialize remaining execution time
    }
}

// Comparison function for sorting tasks by period
int compare_by_period(const void *a, const void *b) {
    return ((Task*)a)->T - ((Task*)b)->T;
}

// RMS scheduling function
void rms(Task tasks[], int n, int tf) {
    // Sort tasks by period
    qsort(tasks, n, sizeof(Task), compare_by_period);

    printf("\nRate-Monotonic Scheduling:\n");
    for (int t = 0; t < tf; t++) {
        int st = -1; // Index of the task to be scheduled

        // Check task deadlines and reset remaining execution times if needed
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].T == 0) {
                tasks[i].R = tasks[i].C;
            }
            if (tasks[i].R > 0 && (st == -1 || tasks[i].T < tasks[st].T)) {
                st = i;
            }
        }

        if (st != -1) {
            printf("Time %d: Task %d\n", t, tasks[st].id);
            tasks[st].R--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int n, tf;

    // Input task details
    input(tasks, &n);

    // Input time frame for simulation
    printf("Enter time frame for simulation: ");
    scanf("%d", &tf);

    // Perform RMS scheduling
    rms(tasks, n, tf);

    return 0;
}
