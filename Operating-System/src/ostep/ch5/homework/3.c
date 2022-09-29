#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed.\n");
        exit(1);
    }else if (rc == 0) {
        printf("hello ");
    }else {
        sleep(2);
        printf("goodbye.\n");
    }
    return 0;
}
