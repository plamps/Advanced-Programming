#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
    int *shared = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shared = 0;

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("hello\n");
        *shared = 1;
    } else {
        // Parent process
        while (*shared == 0)
            ; // Busy wait
        printf("goodbye\n");
    }

    munmap(shared, sizeof(int));
    return 0;
}

