typedef struct __lock_t {
    int flag;
} lock_t;

void lock(lock_t *lock) {
    while(1) {
        while(LoadLinked(&lock->flag) == 1);
        if(StoreConditional(&lock->flag, 1) == 1) {
            return;
        }
    }
}

void unlock(lock_t *lock) {
    lock->flag = 0;
}

int LoadLinked(int *ptr) {
    return *ptr;
}

// C pseudocode
int StoreConditional(int *ptr, int value) {
    if(no one has updated *ptr since the LoadLinked to this address) {
        *ptr = value;
        return 1;
    } else {
        return 0;
    }
}