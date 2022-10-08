#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void
find(char *path, char *name) 
{
    char buf[512], *p;
    int fd;
    struct stat st;
    struct dirent de;

    fd = open(path, 0);    
    if (fd < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if (fstat(fd, &st) < 0 || st.type != T_DIR) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }
  
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
        strcpy(buf, path);
        p = buf + strlen(path);
        *p++ = '/';
        if (de.inum == 0) {
           continue; 
        }

        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0) {
            fprintf(2, "cannot stat path\n");
            continue;
        }
        switch (st.type) {
            case T_FILE:
                if (strcmp(de.name, name) == 0) {
                    printf("%s\n", buf);
                }
                break;
            case T_DIR:
                if (strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0) {
                    find(buf, name);
                }
                break;
        }
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
    find(argv[1], argv[2]);
    exit(0);
}
