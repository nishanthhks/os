#include <stdio.h>
#include <limits.h>

// Structure to represent a memory hole
struct hole {
    int size;
    int v; // -1 indicates the hole is free, otherwise it holds the process index
};

// Structure to represent a process
struct p {
    int size;
    int d; // -1 indicates the process is not allocated, otherwise it is allocated
};

int main() {
    int n1, n2, n, m = -1;

    printf("Enter number of holes: \n");
    scanf("%d", &n1);
    struct hole h[n1];

    printf("Enter hole sizes: \n");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &h[i].size);
        h[i].v = -1;
    }

    printf("Enter number of processes: \n");
    scanf("%d", &n2);
    struct p p[n2];

    printf("Enter process sizes: \n");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &p[i].size);
        p[i].d = -1;
    }

    // First Fit
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n1; j++) {
            if (p[i].size <= h[j].size && h[j].v == -1) {
                p[i].d = 1;
                h[j].v = i;
                break;
            }
        }
    }

    printf("\nFirst Fit:\n");
    for (int i = 0; i < n1; i++) {
        if (h[i].v == -1) {
            printf(" -- ");
        } else {
            printf(" P%d ", h[i].v + 1);
        }
    }
    printf("\n");

    for (int i = 0; i < n2; i++) {
        if (p[i].d == -1) {
            printf("Process P%d(%d) is unfinished\n", (i + 1), p[i].size);
        }
    }

    // Reset the hole and process allocation status
    for (int i = 0; i < n1; i++) {
        h[i].v = -1;
    }
    for (int i = 0; i < n2; i++) {
        p[i].d = -1;
    }

    // Best Fit
    printf("\nBest Fit:\n");
    for (int i = 0; i < n2; i++) {
        n = INT_MAX;
        for (int j = 0; j < n1; j++) {
            if (p[i].size <= h[j].size && h[j].v == -1 && h[j].size < n) {
                m = j;
                n = h[j].size;
            }
        }
        if (n != INT_MAX) {
            p[i].d = 1;
            h[m].v = i;
        }
    }

    for (int i = 0; i < n1; i++) {
        if (h[i].v == -1) {
            printf(" -- ");
        } else {
            printf(" P%d ", h[i].v + 1);
        }
    }
    printf("\n");

    for (int i = 0; i < n2; i++) {
        if (p[i].d == -1) {
            printf("Process P%d(%d) is unfinished\n", (i + 1), p[i].size);
        }
    }

    // Reset the hole and process allocation status
    for (int i = 0; i < n1; i++) {
        h[i].v = -1;
    }
    for (int i = 0; i < n2; i++) {
        p[i].d = -1;
    }

    // Worst Fit
    printf("\nWorst Fit:\n");
    for (int i = 0; i < n2; i++) {
        n = -1;
        for (int j = 0; j < n1; j++) {
            if (h[j].v == -1 && h[j].size > n) {
                m = j;
                n = h[j].size;
            }
        }
        if (n != -1 && p[i].size <= h[m].size) {
            p[i].d = 1;
            h[m].v = i;
        }
    }

    for (int i = 0; i < n1; i++) {
        if (h[i].v == -1) {
            printf(" -- ");
        } else {
            printf(" P%d ", h[i].v + 1);
        }
    }
    printf("\n");

    for (int i = 0; i < n2; i++) {
        if (p[i].d == -1) {
            printf("Process P%d(%d) is unfinished\n", (i + 1), p[i].size);
        }
    }

    return 0;
}
