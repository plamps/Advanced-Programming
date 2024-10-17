#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define FILE_NAME "p6_output.txt"

int main(int argc, char *argv[]) {
    int fd = open(FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    printf("File opened with descriptor: %d\n", fd);

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        const char *child_msg = "Hello from child!\n";
        write(fd, child_msg, strlen(child_msg));
        printf("Child wrote to file\n");
    } else {
        // Parent process
        const char *parent_msg = "Hello from parent!\n";
        write(fd, parent_msg, strlen(parent_msg));
        printf("Parent wrote to file\n");
        wait(NULL);
    }

    close(fd);
    return 0;
}

