
#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char line[200];

    long total = 0;
    long free_mem = 0;
    long available = 0;

    fp = fopen("/proc/meminfo", "r");

    if (fp == NULL) {
        printf("Cannot open memory information\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "MemTotal:", 9) == 0)
            sscanf(line, "MemTotal: %ld", &total);

        else if (strncmp(line, "MemFree:", 8) == 0)
            sscanf(line, "MemFree: %ld", &free_mem);

        else if (strncmp(line, "MemAvailable:", 13) == 0)
            sscanf(line, "MemAvailable: %ld", &available);
    }

    fclose(fp);

    printf("Total Memory: %ld kB\n", total);
    printf("Free Memory: %ld kB\n", free_mem);
    printf("Used Memory: %ld kB\n", total - available);

    return 0;
}
