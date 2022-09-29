#include <stdio.h>

int
main()
{
    int i;
    for (i = 0; i < 3; i++) {
        fork();
        printf("%d *\n", getpid());
    }
    
    return 0;
}
