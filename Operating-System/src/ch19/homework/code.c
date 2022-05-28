#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define PAGESIZE 4096

int
main(int argc, char *argv[]) 
{
    if (argc != 3) {
        fprintf(2, "wrong usage.");
        exit(1);
    }
    
    int NUMPAGES = *argv[1];
    int TRYS = *argv[2];
    
    int a[NUMPAGES*PAGESIZE/sizeof(int)];
    int jump = PAGESIZE / sizeof(int);
    printf("%s, %s\n", NUMPAGES, TRYS); 
    
    int sum = 0;
    for (int k = 0; k < TRYS; k++) {
        int start = mygettime();
        for(int i = 0; i < NUMPAGES * jump; i += jump) {
            a[i] = 1;
        }
        int end = mygettime();
        sum += (end - start);
   }
    
    printf("mean cost: %d ns.\n", sum / TRYS);
    return 0;
}

int
mygettime() 
{
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    return tv.tv_usec;
}
