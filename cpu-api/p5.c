#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;
    printf("hello world (pid:%d)\n", (int) getpid());
    printf("x = %d (before fork)\n", x);
    
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello I am child (pid:%d)\n", (int) getpid());
        printf("x = %d (in child)\n", x);
        x = 200;
        printf("x = %d (in child after changing)\n", x);
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
        printf("x = %d (in parent)\n", x);
        x = 300;
        printf("x = %d (in parent after changing)\n", x);
    }
    return 0;
}