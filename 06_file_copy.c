
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int source, destination;
    char buffer[100];
    int n;

    source = open("input.txt", O_RDONLY);

    if (source < 0) {
        perror("Error opening source file");
        return 1;
    }

    destination = open("output.txt",
                       O_WRONLY | O_CREAT | O_TRUNC,
                       0644);

    if (destination < 0) {
        perror("Error opening destination file");
        close(source);
        return 1;
    }

    while ((n = read(source, buffer, sizeof(buffer))) > 0) {
        write(destination, buffer, n);
    }

    close(source);
    close(destination);

    printf("File copied successfully!\n");

    return 0;
}
