#include <stdio.h>
#include "common_threads.h"
// How to ensure that producer run first?

int buffer;
int count = 0;

void
put(int value)
{
    assert(count == 0);
    count = 1;
    buffer = value;
}

int
get()
{
    assert(count == 1);
    count = 0;
    return buffer;
}

void 
*producer(void *arg)
{
    int i;
    int loops = 10;
    for (i = 0; i < loops; i++){
        put(i);
    }
}

void
*consumer(void *arg)
{
    while(1){
        int tmp = get();
        printf("%d\n", tmp);
    }
}

int
main(int argc, char *argv[])
{
    pthread_t p1, p2;
    Pthread_create(&p1, NULL, producer, NULL);
    Pthread_create(&p2, NULL, consumer, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);

    return 0;
}
