#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("Child: Before closing stdout\n");
        fflush(stdout);  // Ensure the message is printed before closing
        close(STDOUT_FILENO);
        printf("Child: After closing stdout (you shouldn't see this)\n");
        exit(0);
    } else {
        // Parent process
        wait(NULL);
        printf("Parent: Child process has finished\n");
    }
    return 0;
}
