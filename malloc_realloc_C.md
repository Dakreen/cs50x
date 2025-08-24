# malloc and realloc in C

## 1. malloc → memory allocation

Allocates a block of memory on the heap.

Size is given in bytes.

Returns a pointer to the beginning of the block.

Memory contents are uninitialized (garbage values).

```c
int *arr = malloc(5 * sizeof(int)); // space for 5 ints
if (arr == NULL)   // always check for failure
{
    // allocation failed
}
```
You must free(arr) later to avoid a memory leak.


---

## 2. realloc → resize allocated memory

Changes the size of a previously allocated block.

Syntax:
```c
void *realloc(void *ptr, size_t new_size);
```
Cases:

If ptr == NULL → works like malloc(new_size).

If new_size == 0 → works like free(ptr).

Otherwise →

Tries to resize the block in place.

If not possible, allocates a new block, copies old data, frees old block.




Example:
```c
int *tmp = realloc(arr, 10 * sizeof(int)); // resize from 5 to 10
if (tmp != NULL)
{
    arr = tmp; // only update if realloc succeeded
}
else
{
    // realloc failed, arr is still valid, must free later
}
```

---

### Important Notes

Never overwrite the original pointer with realloc directly:
```c
arr = realloc(arr, new_size); // dangerous if realloc fails
```
Use a temporary pointer instead.

realloc may move the memory block → the old pointer may become invalid.

Data beyond the old size is uninitialized (must be filled by you).



---

## Summary

malloc(size) → allocate new memory.

realloc(ptr, new_size) → resize memory safely:

May return new pointer.

Always check for NULL.


Always free when done.

