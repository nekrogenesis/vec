#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec.h"

#define VEC_ERR_EXIT    (-1)
#define VEC_CAP_INIT    (8)
#define VEC_CAP_MAX     (~(~((size_t)(0)) >> 1))

void (*errfn)(VecError type);

#define VEC_ERROR(type) \
do {                    \
    if (errfn) {        \
        errfn(type);    \
        return;         \
    }                   \
    exit(VEC_ERR_EXIT); \
while(0)                \

Vec *vec_init(size_t size) {
    Vec *vec = malloc(sizeof *vec);
    if (!vec) {
        return NULL;
    }
    vec->arr = calloc(VEC_CAP_INIT, size);
    if (!vec->arr) {
        free(vec);
        return NULL;
    }
    vec->cap = VEC_CAP_INIT;
    vec->size = size;
    return vec;
}

void vec_free(Vec *vec) {
    free(vec->arr);
    free(vec);
}

void vec_push(Vec *vec, void *item) {
    if (vec->cap < (vec->len + 1)) {
        if (vec->cap == VEC_CAP_MAX) {
            vec_error(VecCapacityLimitReached);
            return;
        }
        vec->cap <<= 1;
        vec->arr = realloc(vec->arr, vec->cap * vec->size);
        if (!vec->arr) {
            vec_error(VecRealloc);
            return;
        }
    }
    memcpy(((char*)vec->arr) + vec->len * vec->size, item, vec->size);
    vec->len++;
}

void *vec_pop(Vec *vec) {
    if (vec->len) {
        return ((char*)vec->arr) + --vec->len * vec->size;
    }
    return NULL;
}

void vec_set(Vec *vec, size_t index, void *item) {
    if (vec->cap < index) {
        if (index > VEC_CAP_MAX) {
            vec_error(VecIndexOutOfRange);
            return;
        }
        while (vec->cap < index)
            vec->cap <<= 1;
        vec->arr = realloc(vec->arr, vec->cap * vec->size);
        if (!vec->arr) {
            vec_error(VecRealloc);
            return;
        }
    }
    memcpy(((char*)vec->arr) + index * vec->size, item, vec->size);
    vec->len++;
}

void *vec_get(Vec *vec, size_t index) {
    if (vec->cap < index) {
        return NULL;
    }
    return ((char*)vec->arr) + index * vec->size;
}

size_t vec_len(Vec *vec) {
    return vec->len;
}

size_t vec_max(void) {
    return VEC_CAP_MAX;
}

void vec_callback(void (*fn)(VecError)) {
    errfn = fn;
}

void vec_error_handler(VecError type) {
    switch (type) {
    case VecCapacityLimitReached:
        fprintf(stderr, "Vec: capacity limit reached\n");
        break;
    case VecIndexOutOfRange:
        fprintf(stderr, "Vec: index out of range\n");
        break;
    case VecRealloc:
        fprintf(stderr, "Vec: realloc failed\n");
        break;
    }
    exit(VEC_ERR_EXIT);
}