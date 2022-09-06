#include <stdio.h>
#include <pthread.h>
#include "common_threads.h"

int buffer;
int count = 0;
int loops = 100;

// lock, condition 初始化
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

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
    for (i = 0; i < loops; i++){
        Pthread_mutex_lock(&lock);        
        while (count == 1)
            pthread_cond_wait(&cond, &lock);
        put(i);
        pthread_cond_signal(&cond);
        Pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void
*consumer(void *arg)
{
    int i;
    for(i = 0; i < loops; i++){
        Pthread_mutex_lock(&lock);
        while (count == 0)
            pthread_cond_wait(&cond, &lock);
        int tmp = get();
        pthread_cond_signal(&cond);
        Pthread_mutex_unlock(&lock);
        printf("%d\n", tmp);
    }
    return NULL;
}

int 
main(int argc, char *argv[])
{
    pthread_t p1, p2;
    pthread_t p3;
    Pthread_create(&p1, NULL, producer, NULL);
    Pthread_create(&p2, NULL, consumer, NULL);
    Pthread_create(&p3, NULL, consumer, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    Pthread_join(p3, NULL);

    return 0;
}
