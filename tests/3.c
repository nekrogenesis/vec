#include "../src/vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ITEMS ((size_t)1000000)

int main() {
    Vec *v = vec_init(sizeof(size_t));

    assert(vec_len(v) == 0);
    for (size_t i = 0; i < ITEMS; i++) {
        vec_push(v, &i);
    }
    assert(vec_len(v) == ITEMS);
    for (size_t i = ITEMS - 1; vec_len(v); i--) {
        //printf("%zu %zu\n", i, *(int*)vec_pop(v));
        assert((*(size_t*)vec_pop(v)) == i);
    }
    assert(vec_len(v) == 0);

    vec_free(v);
}