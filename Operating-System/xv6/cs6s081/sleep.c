#include <stdio.h>

int 
main(int argc, char *argv[]) 
{
  if (argc == 1 || argc >= 3)
    panic("sleep usage: sleep secs");
  return 0;
}

void
panic(char *s) 
{
  fprintf(2, "%s\n", s);
  exit(1);
}
