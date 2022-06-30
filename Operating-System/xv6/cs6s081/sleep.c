#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) 
{
  if (argc <= 1 || argc >= 3)
  {
    fprintf(2, "%s\n", "usage: sleep seconds");
    exit(1);
  }

  int secs = atoi(argv[1]);
  printf("sleep %ds\n", secs);
  exit(0);
}

