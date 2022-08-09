#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int 
main(int argc, char *argv[])
{
    if(argc != 3) {
        fprintf(2, "wrong usage");
        exit(1);
    }

    char *name = argv[2];
    exit(0);
}
