typedef struct __lock_t {
    int flag;
    int guard;
    queue_t *q;
} lock_t;

int TestAndSet(int *old_ptr, int new)
{
    int old = *old_ptr;
    *old_ptr = new;
    return old;
}

void lock_init(lock_t *m) {
    m->flag = 0;
    m->guard = 0;
    queue_init(m->q);
}

void lock(lock_t *m) {
    while(TestAndSet(&m->guard, 1) == 1);
    if (m->flag == 0) {
        m->flag = 1;
        m->guard = 0;
    } else {
        queue_add(m->q, gettid());
        m->guard = 0;
        park();
    }
}

void unlock(lock_t *m) {
    while(TestAndSet(&m->guard, 1) == 1);
    if (queue_empty(m->q))
        m->flag = 0;
    else
        unpark(queue_remove(m->q));
    m->guard = 0;
}