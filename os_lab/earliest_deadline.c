#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int proc[], int d[], int b[], int pt[], int n) {
    int temp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (d[j] < d[i]) {
                temp = d[j];
                d[j] = d[i];
                d[i] = temp;

                temp = pt[j];
                pt[j] = pt[i];
                pt[i] = temp;

                temp = b[j];
                b[j] = b[i];
                b[i] = temp;

                temp = proc[j];
                proc[j] = proc[i];
                proc[i] = temp;
            }
        }
    }
}

int gcd(int a, int b) {
    int r;
    while (b > 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int lcmul(int p[], int n) {
    int lcm = p[0];
    for (int i = 1; i < n; i++) {
        lcm = (lcm * p[i]) / gcd(lcm, p[i]);
    }
    return lcm;
}

void earliest_deadline_first(int time, int num_of_process, int execution_time[], int deadline[], int period[]) {
    int next_deadlines[num_of_process];
    int remain_time[num_of_process];

    for (int i = 0; i < num_of_process; i++) {
        next_deadlines[i] = deadline[i];
        remain_time[i] = execution_time[i];
    }

    printf("\nEarliest-Deadline First Scheduling:\n");
    printf("PID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < num_of_process; i++) {
        printf("%d\t%d\t%d\t%d\n", i + 1, execution_time[i], deadline[i], period[i]);
    }

    printf("\nScheduling occurs for %d ms\n", time);

    printf("\nSchedule:\n");
    int current_time = 0;
    while (current_time < time) {
        int min_deadline = time + 1;
        int task_to_execute = -1;

        for (int i = 0; i < num_of_process; i++) {
            if (remain_time[i] > 0 && next_deadlines[i] < min_deadline) {
                min_deadline = next_deadlines[i];
                task_to_execute = i;
            }
        }

        if (task_to_execute != -1) {
            printf("%dms : Task %d is running.\n", current_time, task_to_execute + 1);
            remain_time[task_to_execute]--;
        } else {
            printf("%dms: CPU is idle.\n", current_time);
        }

        for (int i = 0; i < num_of_process; i++) {
            if (current_time % period[i] == 0 && current_time != 0) {
                next_deadlines[i] = current_time + deadline[i];
                remain_time[i] = execution_time[i];
            }
        }

        current_time++;
    }
}

int main() {
    int num_of_process;

    printf("Enter the number of processes: ");
    scanf("%d", &num_of_process);

    int proc[num_of_process], b[num_of_process], pt[num_of_process], d[num_of_process], rem[num_of_process];

    // Input burst times, deadlines, and periods
    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < num_of_process; i++) {
        scanf("%d", &b[i]);
        rem[i] = b[i];
    }

    printf("Enter the deadlines:\n");
    for (int i = 0; i < num_of_process; i++) {
        scanf("%d", &d[i]);
        proc[i] = i + 1; // Initialize process IDs
    }

    printf("Enter the time periods:\n");
    for (int i = 0; i < num_of_process; i++) {
        scanf("%d", &pt[i]);
    }

    sort(proc, d, b, pt, num_of_process); // Sort processes by deadline for EDF

    // LCM calculation
    int l = lcmul(pt, num_of_process);
    printf("\nLCM = %d\n", l);

    // Perform Earliest-Deadline First scheduling
    earliest_deadline_first(l, num_of_process, b, d, pt);

    return 0;
}

