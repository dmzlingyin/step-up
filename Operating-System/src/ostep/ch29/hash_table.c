#define BUCKETS (101)

typedef struct __hash_t {
    list_t lists[BUCKETS];
} hash_t;

void Hash_Init(hash_t *h) {
    for (int i = 0; i < BUCKETS; i++) {
        List_Init(&h->lists[i]);
    }
}

int Hash_Insert(hash_t *h, int key) {
    int bucket = key % BUCKETS;
    return List_Insert(&h->lists[bucket], key);
}

int Hash_Lookup(hash_t *h, int key) {
    int bucket = key % BUCKETS;
    return List_Lookup(&h->lists[bucket], key);
}
