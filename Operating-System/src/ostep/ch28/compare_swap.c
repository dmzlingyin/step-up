// compare and swap

typedef struct __lock_t 
{
    int flag;
} lock_t;

void init(lock_t* lock)
{
    lock->flag = 0;
}

void lock(lock_t* lock)
{
    while(CompareAndSwap(&lock->flag, 0, 1) == 1);
}

void unlock(lock_t* lock)
{
    lock->flag = 0;
}

char ComareAndSwap(int *ptr, int old, int new)
{
    unsigned char ret;

    __asm__ __volatile__(
        "lock\n"
        "cmpxchgl %2,%1\n"
        "sate %0\n"
        :"=q" (ret), "=m" (*ptr)
        :"r" (new), "m" (*ptr), "a" (old)
        :"memory"
    );
    return ret;
}