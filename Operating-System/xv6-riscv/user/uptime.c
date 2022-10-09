#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  int tick;
  tick = uptime();
  printf("running time: %d ticks\n", tick);
  exit(0);
}
