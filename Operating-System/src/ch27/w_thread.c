#include <stdio.h>
#include <stdlib.h>
#include "mythreads.h"

typedef struct __myarg_t {
    int a;
    int b;
}myarg_t;

typedef struct __myret_t {
    int a;
    int b;
    int sum;
}myret_t;

void *mythread(void *arg) {
    myarg_t *m = (myarg_t *)arg;
    printf("%d %d\n", m->a, m->b);
    myret_t *r = malloc(sizeof(myret_t));
    r->a = m->a;
    r->b = m->b;
    r->sum = (m->a) + (m->b);
    return (void *)r;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    myret_t *m;

    myarg_t args;
    args.a = 10;
    args.b = 20;
    Pthread_create(&p, NULL, mythread, &args);
    Pthread_join(p, (void **)&m);
    
    printf("returnd %d+%d=%d\n", m->a, m->b, m->sum);
    return 0;
}
