#define NUMCPUS 4

typedef struct __counter_t 
{
    int global;
    pthread_mutex_t glock;
    int local[NUMCPUS];
    pthread_mutex_t llock[NUMCPUS];
    int threshold;
} counter_t;


void init(counter_t *c, int threshold)
{
    c->threshold = threshold;
    c->global = 0;
    Pthread_mutex_init(&c->glock, NULL);

    for (int i = 0; i < NUMCPUS; i++)
    {
        c->local[i] = 0;
        Pthread_mutex_init(&c->llock[i], NULL);
    }
}

void update(counter_t *c, int threadID, int amt)
{
    int cpu = threadID % NUMCPUS;
    Pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;

    if (c->lock[cpu] >= c->threshold)
    {
        Pthread_mutex_lock(&c->glock);
        c->global += c->lock[cpu];
        Pthread_mutex_unlock(&c->glock);
        c->lock[cpu] = 0;
    }
    Pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c)
{
    Pthread_mutex_lock(&c->glock);
    int val = c->global;
    Pthread_mutex_unlock(&c->glock);
    return val;
}
