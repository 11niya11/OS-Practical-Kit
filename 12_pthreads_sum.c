
#include <stdio.h>
#include <pthread.h>

int a[100];
int sum1 = 0, sum2 = 0;
int n;

void *sum_first(void *arg) {
    int i;

    for (i = 0; i < n / 2; i++) {
        sum1 = sum1 + a[i];
    }

    return NULL;
}

void *sum_second(void *arg) {
    int i;

    for (i = n / 2; i < n; i++) {
        sum2 = sum2 + a[i];
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int i;

    printf("Enter even number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100 || n % 2 != 0) {
        printf("Enter an even number between 2 and 100\n");
        return 1;
    }

    printf("Enter %d numbers:\n", n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    pthread_create(&t1, NULL, sum_first, NULL);
    pthread_create(&t2, NULL, sum_second, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Sum of first half = %d\n", sum1);
    printf("Sum of second half = %d\n", sum2);
    printf("Total sum = %d\n", sum1 + sum2);

    return 0;
}
