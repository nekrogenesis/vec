#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec.h"

#define VEC_CAP_INIT    (8)
#define VEC_ERR_EXIT    (-1)
#define VEC_CAP_MAX     (~((~(size_t)0) >> 1))

void (*errhdl)(VecError type) = vec_error_handler;

#define VEC_ERROR(type) \
do {                    \
    if (errhdl) {       \
        errhdl(type);   \
        break;          \
    }                   \
    exit(VEC_ERR_EXIT); \
} while(0)              \

/**
 * @brief Initialize the Vec struct.
 * @param size Size of one item, in Vec, in bytes.
 * @return Pointer to the new Vec struct.
 */
Vec *vec_init(size_t size) {
    Vec *vec = malloc(sizeof *vec);
    if (!vec) {
        return NULL;
    }
    *vec = (Vec) {
        .arr  = malloc(VEC_CAP_INIT * size),
        .cap  = VEC_CAP_INIT,
        .len  = 0,
        .size = size
    };
    if (!vec->arr) {
        free(vec);
        return NULL;
    }
    return vec;
}

/**
 * @brief Free the Vec struct.
 * @param vec Pointer to the Vec struct.
 */
void vec_free(Vec *vec) {
    free(vec->arr);
    free(vec);
}

/**
 * @brief Push back `item` to `vec` and increment the internal length counter.
 * May fail with `VecCapacityLimitReached` if the capacity increases beyond `vec_max()`.
 * May fail with `VecRealloc` if realloc fails.
 * @param vec Pointer to the Vec struct.
 * @param item Pointer to the item.
 */
void vec_push(Vec *vec, void *item) {
    if (vec->cap < (vec->len + 1)) {
        if (vec->cap == VEC_CAP_MAX) {
            VEC_ERROR(VecCapacityLimitReached);
            return;
        }
        vec->cap <<= 1;
        vec->arr = realloc(vec->arr, vec->cap * vec->size);
        if (!vec->arr) {
            VEC_ERROR(VecRealloc);
            return;
        }
    }
    memcpy(((char*)vec->arr) + vec->len++ * vec->size, item, vec->size);
}

/**
 * @brief Pop item from `vec` and decrement the internal length counter.
 * @param vec Pointer to the Vec struct.
 * @return Pointer to the item or `NULL` if there were no items left to pop.
 */
void *vec_pop(Vec *vec) {
    if (vec->len) {
        return ((char*)vec->arr) + --vec->len * vec->size;
    }
    return NULL;
}

/**
 * @brief Set element at `index` in `vec` to `item`.
 * If the element at index does not exist, it will be allocated.
 * May fail with `IndexOutOfRange` if `index >= vec_max()`
 * May fail with `VecRealloc` if your system runs out of memory.
 * @param vec Pointer to the vec struct.
 * @param index
 * @param item Pointer to the item.
 */
void vec_set(Vec *vec, size_t index, void *item) {
    if (vec->cap < index) {
        if (index > VEC_CAP_MAX) {
            VEC_ERROR(VecIndexOutOfRange);
            return;
        }
        while (vec->cap < index)
            vec->cap <<= 1;
        vec->arr = realloc(vec->arr, vec->cap * vec->size);
        if (!vec->arr) {
            VEC_ERROR(VecRealloc);
            return;
        }
    }
    memcpy(((char*)vec->arr) + index * vec->size, item, vec->size);
}

/**
 * @brief Return item at `index` in `vec`.
 * @param vec Pointer to the Vec struct.
 * @param index
 * @return Pointer to the item or `NULL` if the index is bigger then the Vecs capacity.
 */
void *vec_get(Vec *vec, size_t index) {
    if (vec->cap < index) {
        return NULL;
    }
    return ((char*)vec->arr) + index * vec->size;
}

/**
 * @brief Returns the amount of items that have been pushed to Vec.
 * The value returned may be inaccurate if `vec_set()`s index was `index > Vec->len`.
 * @param vec Pointer to the Vec struct.
 * @return Amount of items that have been pushed to Vec.
 */
size_t vec_len(Vec *vec) {
    return vec->len;
}

/**
 * @brief Returns the maximum number of items Vec is able to store.
 * @return Maximum number of items.
 */
size_t vec_max(void) {
    return VEC_CAP_MAX - 1;
}

/**
 * @brief Sets the function that will be called if Vec fails.
 * Is set to `vec_error_handler()` by default.
 * If set to `NULL` Vec will terminate the process with -1 if an error occurs.
 * @param fn Function to call if an error occurs.
 */
void vec_callback(void (*fn)(VecError)) {
    errhdl = fn;
}

/**
 * @brief Default error handler.
 * @param type Vec error code.
 */
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
