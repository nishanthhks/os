#include <stdio.h>

int main() {
    int n, m, i, j, k;
    n = 5; // Number of processes
    m = 3; // Number of resources

    // Allocation matrix
    int alloc[5][3] = { 
        { 0, 1, 0 }, 
        { 2, 0, 0 }, 
        { 3, 0, 2 }, 
        { 2, 1, 1 }, 
        { 0, 0, 2 } 
    };

    // Maximum demand matrix
    int max[5][3] = { 
        { 7, 5, 3 }, 
        { 3, 2, 2 }, 
        { 9, 0, 2 }, 
        { 2, 2, 2 }, 
        { 4, 3, 3 } 
    };

    // Available resources
    int avail[3] = { 3, 3, 2 };

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0; // Initialize finish array to false (0)
    }

    // Need matrix
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j]; // Calculate need matrix
        }
    }

    int y = 0;
    for (k = 0; k < n; k++) { // Loop to check all processes
        for (i = 0; i < n; i++) {
            if (f[i] == 0) { // If process is not finished
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) { // If resources needed are more than available
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) { // If all resources needed are less than available
                    ans[ind++] = i;
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y]; // Release resources
                    }
                    f[i] = 1; // Mark process as finished
                }
            }
        }
    }

    // Check if system is in a safe state
    int flag = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) { // If any process is not finished
            flag = 0;
            printf("The following system is not safe\n");
            break;
        }
    }

    // Print the safe sequence
    if (flag == 1) {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++) {
            printf(" P%d ->", ans[i]);
        }
        printf(" P%d\n", ans[n - 1]);
    }

    return 0;
}
