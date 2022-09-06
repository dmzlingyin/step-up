#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int
main(int argc, char *argv[]) 
{
    if (argc != 3) {
        fprintf(stderr, "wrong usage.\n");
        exit(1);
    }
    
    long PAGESIZE = sysconf(_SC_PAGESIZE);
    long jump = PAGESIZE / sizeof(int);
    int NUMPAGES = atoi(argv[1]);
    int TRYS = atoi(argv[2]);
    if (NUMPAGES <= 0 || TRYS <= 0) {
        fprintf(stderr, "Invalide input\n");
        exit(1);
    }

    int *a = calloc(NUMPAGES, PAGESIZE);
    struct timespec start, end;
    if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start) == -1) {
        fprintf(stderr, "time error.\n");
        exit(1);
    }

    for (int k = 0; k < TRYS; k++) {
        for(int i = 0; i < NUMPAGES * jump; i += jump) {
            a[i] = 1;
        }
    }
    
    if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end) == -1) {
        fprintf(stderr, "time error.\n");
        exit(1);
    }
printf("%f\n", ((end.tv_sec - start.tv_sec) * 1E9 + end.tv_nsec - start.tv_nsec) / (TRYS * NUMPAGES));
    free(a);
    return 0;
}

