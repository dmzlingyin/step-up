#include <semaphore.h>

sem_t s;
sem_init(&s, 0, 1);

sem_wait(&s);
// critical section
sem_post(&s);
