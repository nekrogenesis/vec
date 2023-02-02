#include "../src/vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    Vec *v = vec_init(sizeof *v);
    assert(v);
    assert(v->arr);
    assert(v->cap != 0);
    assert(v->size != 0);
    assert(v->len == 0);
    assert(vec_len(v) == 0);
    vec_free(v);
}