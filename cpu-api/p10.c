#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Parent process (pid:%d)\n", (int) getpid());
    
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("Child process (pid:%d)\n", (int) getpid());
        int wc = waitpid(-1, NULL, 0);
        printf("Child: waitpid() returned %d\n", wc);
        sleep(1);  // Sleep to ensure child finishes after parent
    } else {
        // Parent process
        int wc = waitpid(rc, NULL, 0);
        printf("Parent: waitpid() returned %d\n", wc);
    }
    
    return 0;
}

