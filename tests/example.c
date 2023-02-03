#include "../src/vec.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    puts("creating a vector of ints");
    Vec *vec = vec_init(sizeof(int));

    puts("pushing between 0 and 10 ints");
    srand(time(NULL));
    int amt = rand() % 11;
    for (int i = 0; i < amt; i++) {
        vec_push(vec, &i);
    }

    puts("retrieving the last pushed item");
    printf("%i\n", *(int*) vec_get(vec, vec_len(vec) - 1));

    puts("popping pushed items");
    while (vec_len(vec)) {
        printf("%i ", *(int*) vec_pop(vec));
    }

    puts("\nfreeing the vector");
    vec_free(vec);
}