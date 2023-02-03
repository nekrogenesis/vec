#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct Vec {
    void *arr;      /* array                    */
    size_t cap;     /* capacity                 */
    size_t len;     /* length                   */
    size_t size;    /* size of one item in .arr */
} Vec;

typedef enum VecError {
    VecCapacityLimitReached,
    VecIndexOutOfRange,
    VecRealloc,
} VecError;

Vec   *vec_init(size_t size);
void   vec_free(Vec *vec);
void   vec_push(Vec *vec, void *item);
void  *vec_pop(Vec *vec);
void   vec_set(Vec *vec, size_t index, void *item);
void  *vec_get(Vec *vec, size_t index);
size_t vec_len(Vec *vec);
size_t vec_max(void);
void   vec_callback(void (*fn)(VecError));
void   vec_error_handler(VecError type);

#endif /* VEC_H */
