#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed.\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello world.\n");
        int cwc = wait(NULL);
        printf("the child process return value of wait is: %d\n", cwc);
    } else {
        int wc = wait(NULL);
        printf("the parent process return value of wait is: %d\n", wc);
    }
    return 0;
}



