#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) 
{
    int secs;
    if (argc < 2) {
        fprintf(2, "Usage: sleep seconds\n");
        exit(1);
    }

    secs = atoi(argv[1]);
    if (secs < 0) {
        fprintf(2, "Param wrong\n");
        exit(1);
    }

    sleep(secs); 
    exit(0);
}