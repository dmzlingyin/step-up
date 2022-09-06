#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd[2];
    char readbuffer[1024];
    pipe(fd);

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork faild.\n");
        exit(1);
    } else if (rc == 0) {
        // child process closes reading side of pipe
        close(fd[0]);
        // send stdout and stderr to pipe
        dup2(fd[1], 1);
        dup2(fd[1], 2);
        execlp("ls", "./", NULL);
        exit(0);
    } else {
        close(fd[1]);
        //read(fd[0], readbuffer, sizeof(readbuffer));
        while (read(fd[0], readbuffer, sizeof(readbuffer)) != 0) {
            printf("Received string: %s", readbuffer);
        }
    }
    return 0;
}

