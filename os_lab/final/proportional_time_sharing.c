#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, sOT = 0;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n]; // Array to store the number of tickets for each process
    int l[n + 1]; // Array to store cumulative ticket counts

    l[0] = 0; // Initialize cumulative ticket count array

    // Input the number of tickets for each process
    printf("\nEnter the number of tickets for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("PID%d: ", i + 1);
        scanf("%d", &pid[i]);
        sOT += pid[i];
        l[i + 1] = sOT; // Update cumulative ticket counts
    }

    // Print probability of servicing each process
    for (int i = 0; i < n; i++) {
        printf("Probability of servicing process %d is %d%%\n", i + 1, (pid[i] * 100) / sOT);
    }

    srand(time(NULL)); // Seed the random number generator

    int t = 1; // Time counter
    int sum = sOT; // Remaining tickets to be serviced

    // Simulate the lottery scheduling
    while (sum > 0) {
        int x = rand() % sOT; // Draw a random number between 0 and sOT - 1
        int j;

        // Determine which process is selected based on the random draw
        for (j = 0; j < n; j++) {
            if (x < l[j + 1]) {
                printf("%d ms: Servicing Ticket of process %d\n", t, j + 1);
                pid[j]--; // Decrement the ticket count for the selected process
                sum--; // Decrement the remaining tickets
                t++; // Increment the time counter
                break;
            }
        }

        // No process found (should not occur in practice)
    }

    // Print completion status for each process
    for (int i = 0; i < n; i++) {
        if (pid[i] == 0) {
            printf("PID%d has finished executing\n", i + 1);
        }
    }

    return 0;
}
