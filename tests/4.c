#include "../src/vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ITEMS ((size_t)1024 * 1024)

int main() {
    Vec *v = vec_init(sizeof(size_t));
    size_t *arr = malloc(sizeof *arr * ITEMS);
    assert(vec_len(v) == 0);
    for (size_t i = 0; i < ITEMS; i++) {
        size_t val = rand() % ITEMS;
        arr[i] = val;
        vec_push(v, &val);
    }

    for (size_t i = 0; i < ITEMS; i++) {
        assert(arr[i] == *(size_t*)vec_get(v, i));
    }
    free(arr);
    vec_free(v);
}