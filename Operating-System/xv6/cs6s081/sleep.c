#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) 
{
  if (argc != 2){
    fprintf(2, "%s\n", "Usage: sleep seconds");
    exit(1);
  }

  int secs = atoi(argv[1]);
  sleep(secs);
  exit(0);
}

