#include "../src/vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ITEMS ((size_t)1024 * 1024)

int main() {
    Vec *v = vec_init(sizeof(size_t));
    vec_callback(vec_error_handler);
    assert(vec_len(v) == 0);
    size_t i = 1000000;
    vec_set(v, i, &i);
    assert(vec_len(v) == 0);
    assert(i == *(size_t*) vec_get(v, i));
    assert(vec_len(v) == 0);
    vec_free(v);
}