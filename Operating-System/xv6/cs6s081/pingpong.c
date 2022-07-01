#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int c = fork();

  if (c == 0) {
    printf("<%d>: child process\n", getpid());
  } else if (c > 0) {
    wait(0);
    printf("<%d>: parent process\n", getpid());
  } else {
    fprintf(2, "wrong\n");
    exit(1);
  }

  exit(0);
}
