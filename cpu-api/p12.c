#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2];
    pid_t child1, child2;
    // char buffer[BUFFER_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    child1 = fork();
    if (child1 < 0) {
        perror("fork");
        exit(1);
    } else if (child1 == 0) {
        // First child (writer)
        close(pipefd[0]);  // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);  // Execute 'ls -l'
        perror("execlp");
        exit(1);
    }

    child2 = fork();
    if (child2 < 0) {
        perror("fork");
        exit(1);
    } else if (child2 == 0) {
        // Second child (reader)
        close(pipefd[1]);  // Close unused write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin from pipe
        close(pipefd[0]);
        execlp("wc", "wc", "-l", NULL);  // Execute 'wc -l'
        perror("execlp");
        exit(1);
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}

