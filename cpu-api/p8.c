#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

int main(int argc, char *argv[]) {
    printf("Main program (pid:%d)\n", (int) getpid());

    char *args[] = {"ls", "-l", NULL};
    char *env[] = {"PATH=/bin:/usr/bin", NULL};

    for (int i = 0; i < 6; i++) {
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            // Child process
            printf("Child %d (pid:%d) calling exec variant %d\n", i, (int) getpid(), i);
            fflush(stdout);  // Ensure the message is printed before exec
            switch (i) {
                case 0:
                    execl("/bin/ls", "ls", "-l", NULL);
                    break;
                case 1:
                    execle("/bin/ls", "ls", "-l", NULL, env);
                    break;
                case 2:
                    execlp("ls", "ls", "-l", NULL);
                    break;
                case 3:
                    execv("/bin/ls", args);
                    break;
                case 4:
                    execvp("ls", args);
                    break;
                case 5:
                    execve("/bin/ls", args, env);
                    break;
            }
            // If exec() fails, we'll reach here
            perror("exec failed");
            exit(1);
        } else {
            // Parent process
            wait(NULL);
        }
    }

    return 0;
}
