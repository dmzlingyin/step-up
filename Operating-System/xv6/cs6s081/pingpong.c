#include "kernel/types.h"
#include "user/user.h"

#define BUFSIZE 4

void mexit(char *s)
{
  fprintf(2, "%s\n", s);
  exit(1);
}

int
main(int argc, char *argv[])
{
  int p1[2], p2[2];
  char buf1[BUFSIZE], buf2[BUFSIZE];

  if (pipe(p1) < 0 || pipe(p2) < 0)
    mexit("pip error");

  int c = fork();
  if (c == 0) {
    read(p2[0], buf2, BUFSIZE);
    write(p1[1], "pong", BUFSIZE);
    printf("%d: received %s\n", getpid(), buf2);
  } else if (c > 0) {
    write(p2[1], "ping", BUFSIZE);
    wait(0);
    read(p1[0], buf1, BUFSIZE);
    printf("%d: reveived %s\n", getpid(), buf1);
  } else {
    mexit("fork error");
  }

  exit(0);
}
