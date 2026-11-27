
#include <stdio.h>

int main() {
    int block[20], process[20];
    int first[20], best[20], worst[20];
    int nb, np, i, j;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    printf("Enter size of each block:\n");
    for (i = 0; i < nb; i++) {
        scanf("%d", &block[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &np);

    printf("Enter size of each process:\n");
    for (i = 0; i < np; i++) {
        scanf("%d", &process[i]);
    }

    // First Fit
    for (i = 0; i < nb; i++)
        first[i] = block[i];

    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (first[j] >= process[i]) {
                printf("First Fit: P%d -> Block %d\n",
                       i + 1, j + 1);
                first[j] -= process[i];
                break;
            }
        }

        if (j == nb)
            printf("First Fit: P%d not allocated\n", i + 1);
    }

    // Best Fit
    for (i = 0; i < nb; i++)
        best[i] = block[i];

    for (i = 0; i < np; i++) {
        int index = -1;

        for (j = 0; j < nb; j++) {
            if (best[j] >= process[i]) {
                if (index == -1 || best[j] < best[index])
                    index = j;
            }
        }

        if (index != -1) {
            printf("Best Fit: P%d -> Block %d\n",
                   i + 1, index + 1);
            best[index] -= process[i];
        } else {
            printf("Best Fit: P%d not allocated\n", i + 1);
        }
    }

    // Worst Fit
    for (i = 0; i < nb; i++)
        worst[i] = block[i];

    for (i = 0; i < np; i++) {
        int index = -1;

        for (j = 0; j < nb; j++) {
            if (worst[j] >= process[i]) {
                if (index == -1 || worst[j] > worst[index])
                    index = j;
            }
        }

        if (index != -1) {
            printf("Worst Fit: P%d -> Block %d\n",
                   i + 1, index + 1);
            worst[index] -= process[i];
        } else {
            printf("Worst Fit: P%d not allocated\n", i + 1);
        }
    }

    return 0;
}
