
#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    int at[20], bt[20], rt[20], wt[20], tat[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival and burst time of P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);

        rt[i] = bt[i];
    }

    while (completed < n) {
        int shortest = -1;
        int min = 99999;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < min) {
                min = rt[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        rt[shortest]--;
        time++;

        if (rt[shortest] == 0) {
            completed++;

            tat[shortest] = time - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    return 0;
}
