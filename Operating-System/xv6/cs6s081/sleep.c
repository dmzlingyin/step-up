#include "kernel/types.h"
#include "user/user.h"

void mpanic(){
    fprintf(2, "%s\n", "Usage: sleep seconds(positive)");
    exit(1);
}

int 
main(int argc, char *argv[]) 
{
  if (argc <= 1 || argc >= 3){
      mpanic();
  }

  int secs = atoi(argv[1]);
  if (secs < 0)
      mpanic();
  sleep(secs);

  exit(0);
}

