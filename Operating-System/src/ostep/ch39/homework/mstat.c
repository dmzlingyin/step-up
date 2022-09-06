#include <stdio.h>
#include <sys/stat.h>

int
main(int argc, char *argv[])
{
    if(argc < 2) {
        fprintf(stderr, "mstat: mstat path(file path)\n");
        return 0;
    } 

    struct stat st;
    for(int i = 1; i < argc; i++) {
        if(stat(argv[i], &st) != 0) {
            printf("%s stat error", argv[i]);
            continue;
        }
        printf("-------------------------------------\n");
        printf("file size: %d\n", (int)st.st_size);
        printf("blocks allocated: %ld\n", st.st_blksize);
        printf("link count: %d\n", (int)st.st_nlink);
        printf("-------------------------------------\n");
    }
    return 0;
}
