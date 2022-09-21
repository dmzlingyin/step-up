#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv) 
{
    int parent_p[2];
    int child_p[2];
    char buf[64];
    pipe(parent_p);
    pipe(child_p);

    if (fork() == 0) {
        // child
        read(parent_p[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        write(child_p[1], "pong", strlen("pong"));
    } else {
        // parent
        write(parent_p[1], "ping", strlen("ping"));
        read(child_p[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
    }
    exit(0);
}