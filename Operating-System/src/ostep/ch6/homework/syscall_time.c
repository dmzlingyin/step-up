#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    struct timeval start_time;
    struct timeval end_time;
    gettimeofday(&start_time, NULL);
    for (int i = 0; i < 100000000; i++) {
       write(1, "s\n", 0); 
    }
    gettimeofday(&end_time, NULL);
    int du = end_time.tv_sec - start_time.tv_sec;
    printf("%.100f", (float)du / 100000000);

    return 0;
}
