#include <stdio.h>
#include "common_threads.h"

#define MAX 100

int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;
int loops = 200;

void
put(int value)
{
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int
get()
{
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}

// ----------------------- Producer and Consumer ------------------------
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;


void
*producer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++){      
        Pthread_mutex_lock(&lock);
        while (count >= MAX)
            pthread_cond_wait(&empty, &lock);
        put(i);
        pthread_cond_signal(&fill);
        Pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void
*consumer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++){
        Pthread_mutex_lock(&lock);
        while (count <= 0)
            pthread_cond_wait(&fill, &lock);
        int tmp = get();
        pthread_cond_signal(&empty);
        Pthread_mutex_unlock(&lock);
        printf("%d\n", tmp);
    }
    return NULL;
}

int
main(int argc, char *argv[])
{
    pthread_t threads[MAX];
    pthread_t pd;

    // 一个生产者
    Pthread_create(&pd, NULL, producer, NULL);
    
    // 多个消费者
    for (int i = 0; i < MAX; i++){
        Pthread_create(&threads[i], NULL, consumer, NULL);
    }
    
    Pthread_join(pd, NULL);
    for (int i = 0; i < MAX; i++){
        Pthread_join(threads[i], NULL);
    } 
    
    return 0;
}
