// the child process's variable is just a copy of parent's.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    printf("The main process (pid: %d)\n", (int)getpid());
    int x = 100;
    printf(">>>>>> x value: %d\n", x);
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed.\n");
        exit(1);
    } else if (rc == 0) {
       sleep(3);
       printf("child process: x vlaue: %d\n", x);
       x = 200;
       printf("child process: x vlaue: %d\n", x);
    } else {
        x = 500;
        printf(">>>>>> x value: %d\n", x);
    }
    return 0;
}

