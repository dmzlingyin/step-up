#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed.\n");
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("test\n");
    } else {
        wait(NULL);
        printf("nothing.\n");
    }
    return 0;
}

