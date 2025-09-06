# Memory in C — Stack vs Heap


---

## 1. What is Memory?

When a C program runs, it uses memory (RAM) to store:

Code → the program instructions.

Data → variables, arrays, strings.

Metadata → function calls, return addresses.


This memory is divided into different regions, each with its own rules.


---

## 2. The Stack

Automatically managed by the compiler.

Stores local variables, function parameters, and return addresses.

Memory is released automatically when the function exits.

Very fast, but limited in size (a few MB).


### Example:

```c
void foo() {
    int x = 10;          // stored on stack
    int arr[3] = {1,2,3}; // stored on stack
} // x and arr are destroyed here
```

Risks:

Stack overflow (too much recursion or huge arrays).

Cannot dynamically resize arrays.



---

## 3. The Heap

Manually managed by the programmer.

Memory allocated with malloc, calloc, realloc.

Larger than stack, can persist until freed.

Slower access, because the system has to manage allocations.


### Example:

```c
void foo() {
    int *list = malloc(3 * sizeof(int));  // allocated on heap
    list[0] = 42;
    free(list); // must be freed manually
}
```

Risks:

Memory leaks → forgetting to free.

Dangling pointers → using freed memory.

Double free → freeing the same block twice.



---

## 4. Stack vs Heap — Quick Comparison

```
Feature	| Stack                        | Heap
+--------------------------------------------------------------------+
Managed | by Compiler (automatic)      | Programmer (malloc/free)
Size	| Small, fixed                 | Large, flexible
Lifetime| Ends when function ends      | Until manually freed
Speed	| Very fast                    | Slower
Typical | use Local vars, small arrays | Dynamic data structures
Risks	| Overflow	                   | Leaks, dangling, double free 
```



---

## 5. Memory Layout

```
+-----------------------+
|  Code (program text)  |  <- instructions
+-----------------------+
|  Global variables     |  <- static storage
+-----------------------+
|        Heap           |  <- grows upward
|   (malloc/free)       |
+-----------------------+
|        Stack          |  <- grows downward
|   (local vars)        |
+-----------------------+
```


---

## 6. Cybersecurity Angle

Stack → target of buffer overflows.

Heap → target of use-after-free, memory corruption, heap spraying.

Many vulnerabilities in C/C++ come from poor memory management.



---

## In short:

Stack = fast, temporary, automatic.

Heap = flexible, persistent, manual.

A good programmer (and security analyst) must understand both.
