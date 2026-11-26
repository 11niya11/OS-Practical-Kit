
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        printf("Child process\n");
        printf("Child PID: %d\n", getpid());

        execlp("ls", "ls", "-l", NULL);

        perror("exec failed");
    }
    else if (pid > 0) {
        wait(NULL);
        printf("Parent process\n");
        printf("Parent PID: %d\n", getpid());
    }
    else {
        perror("fork failed");
    }

    return 0;
}
