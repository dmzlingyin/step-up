#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 3;
    printf("location of code: %p\n", (void *)main);
    printf("location of head: %p\n", (void *)malloc(1));
    printf("location of stack: %p\n", (void *)&x);
    return 0;
}
