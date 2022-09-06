typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L) {
    L->head = NULL;
    Pthread_mutex_lock(&L->lock, NULL);
}

void List_Insert(list_t *L, int key) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    new->key = key;
    
    // just lock the critical section
    Pthread_mutex_lock(&L->lock);
    new->next = L->head;
    L->head = new;
    Pthread_mutex_unlock(&L->lock);
}

int get(list_t *L, int key) {
    int rv = -1;
    Pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while(curr) {
        if (curr->key == key) {
            rv = 0;
            break;
        }
        curr = curr->next;
    }
    Pthread_mutex_unlock(&L->lock);
    return rv;
}

