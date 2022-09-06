#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
    unsigned int time = 5;
    int rc = fork();
    int rc1 = fork();
    if (rc < 0 && rc1 < 0) {
        fprintf(stderr, "fork failed.\n");
        exit(1);
    } else if (rc == 0 || rc1 == 0) {
        sleep(rand_r(&time));
        printf("(pid: %d) hello world.\n", (int)getpid());
    } else {
        int wc = waitpid(rc, NULL, rc);
        printf("the parent process return value of wait is: %d\n", wc);
    }
    return 0;
}



