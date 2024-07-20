#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 4
#define NUM_RESOURCES 3

// Global variables for available resources, allocation matrix, and request matrix
int available[NUM_RESOURCES];
int allocation[NUM_PROCESSES][NUM_RESOURCES];
int request[NUM_PROCESSES][NUM_RESOURCES];
int avail_matrix[NUM_PROCESSES + 1][NUM_RESOURCES];

// Function to perform deadlock detection
bool deadlockDetection(int *safeSequence) {
    int work[NUM_RESOURCES]; // Work array to keep track of available resources
    bool finish[NUM_PROCESSES] = {false}; // Finish array to track process completion

    // Initialize work array and avail_matrix with available resources
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
        avail_matrix[0][i] = work[i];
    }

    int count = 0; // Count of processes that can complete
    while (count < NUM_PROCESSES) {
        bool found = false;

        // Check each process
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) { // If process is not yet finished
                bool canProceed = true;

                // Check if resources needed by the process can be satisfied
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                // If resources can be allocated, mark the process as finished
                if (canProceed) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocation[i][j]; // Release resources
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;

                    // Update avail_matrix with current available resources
                    for (int k = 0; k < NUM_RESOURCES; k++) {
                        avail_matrix[count][k] = work[k];
                    }
                }
            }
        }

        // If no process could be found to proceed, break the loop
        if (!found) {
            break;
        }
    }

    // Check if all processes are finished
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            printf("Deadlock detected. Process P%d is in deadlock.\n", i);
            return false;
        }
    }

    // Print the safe sequence if no deadlock is detected
    printf("No deadlock detected. The system is in a safe state.\n");
    printf("Safe sequence: ");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int i, j;

    // Input available resources
    printf("Enter the Available Resources Vector:\n");
    for (i = 0; i < NUM_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    // Display available resources
    printf("Available Resources: ");
    for (i = 0; i < NUM_RESOURCES; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    // Input allocation matrix
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < NUM_PROCESSES; i++) {
        for (j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input request matrix
    printf("Enter the Request Matrix:\n");
    for (i = 0; i < NUM_PROCESSES; i++) {
        for (j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Safe sequence array
    int safeSequence[NUM_PROCESSES];
    
    // Perform deadlock detection
    if (deadlockDetection(safeSequence)) {
        // Display available matrix if no deadlock is detected
        printf("Available Matrix:\n");
        for (i = 0; i <= NUM_PROCESSES; i++) {
            for (j = 0; j < NUM_RESOURCES; j++) {
                printf("%d ", avail_matrix[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
