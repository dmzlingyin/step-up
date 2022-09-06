// basic node structure
typedef struct __node_t 
{
    int key;
    struct __node_t *next;
} node_t;

typedef struct __list_t 
{
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L)
{
    L->head = NULL;
    Pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(list_t *L, int key)
{
    Pthread_mutex_lock(&L->lock);
    node_t * new = malloc(sizeof(node_t));
    if (new == NULL)
    {
        perror("malloc");
        Pthread_mutex_unlock(&L->lock);
        return -1;
    }

    new->key = key;
    new->next = L->next;
    L->head = new;
    Pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int key)
{
    Pthread_mutex_lock(&L->lock);
    node_t * curr = L->head;
    while (curr)
    {
        if (curr-key == key)
        {
            Pthread_mutex_unlock(&L->lock);
            return 0;
        }
        curr = curr->next;
    }
    Pthread_mutex_unlock(&L->lock);
    return -1; // no find.
}
