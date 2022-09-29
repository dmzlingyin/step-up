#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed.\n");
        exit(1);
    } else if (rc == 0) {
        //execl("/usr/bin/ls", "./", NULL);
        execv("/usr/bin/ls", argv);
    } else {
        wait(NULL);
    }
    return 0;
}
