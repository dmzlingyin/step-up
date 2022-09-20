#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

/*
 * 1. list files of given path
 * 2. search if file contain searched name
 * */
char*
fmtname(char *path) 
{
    static char buf[DIRSIZ+1];
    char *p;

    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;
    if(strlen(p) >= DIRSIZ) 
        return p;
    memmove(buf, p, strlen(p));
    memset(buf+strlen(p), '\0', DIRSIZ-strlen(p));
    return buf;
}

void
find(char *path, char *search) 
{
    char buf[512];
    int fd;
    struct stat st;

    if((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if(fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        clsoe(fd);
        return;
    }

    if(st.type == T_DIR) {
        searchDir(path, buf, fd, st, search);
    }
    close(fd);
}

void
searchDir(char *path, char *buf, int fd, struct stat st, char *search)
{
    char *p;
    struct dirent de;
    struct stat st2;

    if(strlen(path) + 1 + DIRSIZ + 1 > 512) {
        printf("find: path too long\n");
        return;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
        if(de.inum == 0) 
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0) {
            printf("find: cannot stat %s\n", buf);
            continue;
        }
        if(st.type == T_DIR) {
            if(strcmp(fmtname(buf), ".") != 0 && strcmp(fmtname(buf), "..") != 0) {
                int fd2 = open(buf, 0);
                if(fstat(fd2, &st2) < 0) {
                    fprintf(2, "find: cannot stat %s\n", path);
                    close(fd2);
                    return;
                }
                searchDir(buf, buf, fd2, st2, search);
                close(fd2);
            }
        } else if(st.type == T_FILE) {
            if(strcmp(fmtname(buf), search) == 0) {
                printf("%s\n", buf);
            }
        }
    }
} 

int 
main(int argc, char *argv[])
{
    if(argc < 2) {
        fprintf(2, "wrong usage\n");
        exit(1);
    } else if(argc == 2) {
        find(".", argv[1]);
    } else {
        for(i = 2; i < argc; i++) {
            find(argv[1], argv[i])
        }
    }
    exit(0);
}
