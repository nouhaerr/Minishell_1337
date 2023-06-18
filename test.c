#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]);  // Close the reading end of the pipe

        char modifiedData[] = "Hello from child process!";
        write(pipefd[1], modifiedData, strlen(modifiedData) + 1);  // Write modified data to the pipe

        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipefd[1]);  // Close the writing end of the pipe

        char buffer[BUFFER_SIZE];
        ssize_t bytesRead = read(pipefd[0], buffer, BUFFER_SIZE);  // Read data from the pipe

        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Output from child process: %s\n", buffer);

        close(pipefd[0]);
        wait(NULL);
    }

    return 0;
}
