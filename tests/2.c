#include "../src/vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ITEMS ((size_t)1000000)

int main() {
    Vec *v = vec_init(sizeof(size_t));
    vec_callback(vec_error_handler);

    assert(vec_len(v) == 0);
    for (size_t i = 0; i < ITEMS; i++) {
        vec_push(v, &i);
    }
    assert(vec_len(v) == ITEMS);

    vec_free(v);
}