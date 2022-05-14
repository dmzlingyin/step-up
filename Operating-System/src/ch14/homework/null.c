#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p;
    p = NULL;
    free(p);
    return 0;
}
