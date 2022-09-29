#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
find(char *path) 
{
    int fd;
    struct stat st;

    fd = open(path, 0);    
    if (fd < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type) {
        case T_FILE:
            printf("%s", path);
            break;
        case T_DIR:
            printf("%s", path);
            break;
    }
    close(fd);
}

int
main(int argc, char *argv[]) 
{
    if (argc < 3) {
        fprintf(2, "Usage: find [path] [name]\n");
        exit(1);
    }
    find(argv[1]);
    exit(0);
}