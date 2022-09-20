#include "kernel/types.h"
#include "user/user.h"

/*
质数筛详情:https://swtch.com/~rsc/thread/
 */

int generateNatural();
int primeFilter(int in_fd, int prime);
int
main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);

    int c = fork();
    if (c > 0) {
        for (int i = 2; i <= 35; i++) {

        }
    } else if (c == 0) {
        printf("%d\n", getpid());
    } else {
        fprintf(2, "%s\n", "fork error");
        exit(1);
    }

    exit(0);
}
