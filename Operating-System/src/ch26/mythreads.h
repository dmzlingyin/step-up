#ifndef __MYTHREADS_H__
#define __MYTHREADS_H__

#include <pthread.h>
#include <assert.h>

#define Pthread_create(thread, attr, start_routine, arg) assert(pthread_create(thread, attr, start_routine, arg) == 0);
#define Pthread_join(thread, value_ptr) assert(pthread_join(thread, value_ptr) == 0);

#endif

