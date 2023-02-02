# VEC - WARNING: STILL IN DEVELOPMENT
C99 vector implementation

## DOCUMENTATION
```c
Vec *vec_init(size_t size)
```
### DESCRIPTION
&emsp;Initializes the Vec struct.
### PARAMETERS
&emsp;`size` size of element in Vec, in bytes.
### RETURN
&emsp;pointer to a new Vec struct, should be freed with `vec_free()`.

```c
void vec_free(Vec *vec);
```
### DESCRIPTION
&emsp;Frees the Vec struct.
### PARAMETERS
&emsp;`vec` pointer to the Vec struct.

```c
void vec_push(Vec *vec, void *item);
```
### DESCRIPTION
&emsp;Push `item` to the end of `vec` and increment the internal length counter.
### PARAMETERS
&emsp;`vec` pointer to the Vec struct.
### ERRORS
&emsp;`VecCapacityLimitReached` if the capacity increases beyond `vec_max()`.<br>
&emsp;`VecRealloc` if your system runs out of memory to allocate.

```c
void *vec_pop(Vec *vec);
```
### DESCRIPTION
&emsp;Decrement the internal length counter and pop one item off `vec`.
### PARAMETERS
&emsp;`vec` pointer to the Vec struct.
### RETURN
&emsp;Valid pointer to the item or `NULL` if there were no items left to pop.

```c
void vec_set(Vec *vec, size_t index, void *item);
```
### DESCRIPTION
&emsp;Set element at `index` in `vec` to `item`. If `index > Vec.len` the
internal length counter for `vec_push()`, `vec_pop()` and `vec_len` will no longer
be accurate.
### PARAMETERS
&emsp;`vec` pointer to the Vec struct.
&emsp;`index` should be smaller than `vec_max()`
&emsp;`item` pointer to the item.

### ERRORS
&emsp;`VecCapacityLimitReached` if the index goes beyond `vec_max()`.<br>
&emsp;`VecRealloc` if your system runs out of memory to allocate.

```c
void *vec_get(Vec *vec, size_t index);
```
### DESCRIPTION
&emsp;Get element at `index` in `vec`.
### PARAMETERS
&emsp;`vec` pointer to the Vec struct.
&emsp;`index` should be smaller than `vec_max()`
### RETURN
&emsp;pointer to the item or `NULL` if `index > Vec.cap`.

```c
size_t vec_len(Vec *vec);
```
### DESCRIPTION
&emsp;Returns the amount of elements in `vec`. May return an incorrect value if
`vec_set` indexed beyond `Vec.len`.
### PARAMETERS
&emsp;`vec` pointer to the Vec struct.
### RETURN
&emsp;pointer to the item or `NULL` if `index > Vec.cap`.

```c
size_t vec_max(void);
```
### DESCRIPTION
&emsp;Returns the maximum number of elements that may be stored in Vec.
### RETURN
&emsp;Maximum number of elements.

```c
void vec_callback(void (*fn)(VecError));
```
### DESCRIPTION
&emsp;Specifies a callback function for Vec. If left `NULL`, any error Vec produces
will terminate the process with `exit(-1)`.
### PARAMETERS
&emsp;`fn` callback function.

```c
void vec_error_handler(VecError type);
```
### DESCRIPTION
&emsp;An example for a Vec error handler. To use it call `vec_callback(vec_error_handler)`.
### PARAMETERS
&emsp;`type` type of the error.

## NOTES
&emsp;Any errors Vec produces, are considered fatal.

## TODO
&emsp;check check pops past the 0th element