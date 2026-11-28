
#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>

int main() {
    struct utsname system;

    if (uname(&system) == -1) {
        printf("Error getting system information\n");
        return 1;
    }

    printf("Kernel Information\n");
    printf("Kernel Name: %s\n", system.sysname);
    printf("Kernel Version: %s\n", system.release);
    printf("Machine Type: %s\n", system.machine);

    printf("\nCPU Information\n");

    FILE *fp = fopen("/proc/cpuinfo", "r");

    if (fp == NULL) {
        printf("Cannot open CPU information\n");
        return 1;
    }

    char line[200];

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "model name") != NULL) {
            printf("%s", line);
            break;
        }
    }

    fclose(fp);

    return 0;
}
