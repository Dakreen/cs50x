📝 Notes: Pointers in C


---

1. What is a Pointer?

A pointer is a variable that stores the memory address of another variable.

Instead of holding a value like 42, it holds a location like 0x7ffee3a4.


Example:

int x = 42;       // normal variable
int *p = &x;      // pointer p stores the address of x

&x → “address of x”

*p → “value at address p” (dereferencing)



---

2. Declaring Pointers

int *p;    // pointer to int
char *c;   // pointer to char
float *f;  // pointer to float

The * means the variable is a pointer to type.


---

3. Using Pointers

int x = 10;
int *p = &x;     // p points to x

printf("%p\n", p);  // prints address of x
printf("%d\n", *p); // prints value at that address = 10

*p = 20;            // change value of x via pointer
printf("%d\n", x);  // x is now 20


---

4. Pointers and Arrays

In C, arrays decay into pointers to their first element.

That’s why pointers can act like arrays.


int arr[3] = {10, 20, 30};
int *p = arr;   // same as &arr[0]

printf("%d\n", p[1]);     // 20
printf("%d\n", *(p + 2)); // 30

⚠️ arr is not reassignable, but p is.


---

5. Pointer Arithmetic

Adding i to a pointer moves it by i * sizeof(type).

Example with int (4 bytes on most systems):


int arr[3] = {1,2,3};
int *p = arr;

printf("%p\n", p);     // address of arr[0]
printf("%p\n", p+1);   // address of arr[1] (+4 bytes)
printf("%p\n", p+2);   // address of arr[2] (+8 bytes)


---

6. Pointers and malloc (Heap Allocation)

int *list = malloc(3 * sizeof(int));
list[0] = 10;
list[1] = 20;
list[2] = 30;

free(list);   // must free when done

list is a pointer to heap memory.

You can access it like an array (list[i]).



---

7. Null Pointers

A pointer that doesn’t point anywhere = NULL.

Always initialize pointers to NULL if not set.


int *p = NULL;
if (p == NULL) {
    printf("Pointer is empty\n");
}


---

8. Common Pointer Errors

❌ Dangling pointer → using memory after free.
❌ Uninitialized pointer → random address, crash.
❌ Double free → freeing same memory twice.
❌ Segmentation fault → accessing memory you don’t own.


---

9. Pointers to Pointers

A pointer can also store the address of another pointer.


int x = 5;
int *p = &x;      // pointer to int
int **pp = &p;    // pointer to pointer

printf("%d\n", **pp); // 5


---

10. Why Pointers Matter

Allow dynamic memory (heap).

Allow functions to modify variables outside their scope.

Foundation for data structures (linked lists, trees, tries).

Critical in system programming, cybersecurity (buffer overflows).



---

✅ In short:

Pointers = variables that store memory addresses.

& = get address, * = dereference.

Arrays and pointers are closely related.

Essential for heap allocation and advanced data structures.

