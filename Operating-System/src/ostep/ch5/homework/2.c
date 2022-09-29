// both parent and child use same des to write something.
// answer is YES.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main() {
    int des = open("./test.txt",O_CREAT|O_WRONLY);
    if (des < 0) {
        fprintf(stderr, "open file failed.\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed.\n");
        exit(1);
    } else if (rc == 0) {
        // child process use des
        char *message = "I am child.\n";
        for (int i = 0; i < 10000; i++) {
            write(des, message, 13); 
        }
    } else {
        // parent process use des
        char *message = "I am parent.\n";
        for (int i = 0; i < 20000; i++) {
            write(des, message, 14);
        }
    }
    return 0;
}
