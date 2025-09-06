# Notes: Dot (.) vs Arrow (->) in C

## 1. Dot (.)

Used when you have a struct variable itself.

Syntax:

struct_variable.field

Example:
```c
typedef struct
{
    int age;
} Person;

Person p;
p.age = 30;     // use dot
```


---

## 2. Arrow (->)

Used when you have a pointer to a struct.

Syntax:

struct_pointer->field

Equivalent to:

(*struct_pointer).field

Example:
```c
Person *ptr = malloc(sizeof(Person));
ptr->age = 40;  // use arrow
```


---

## 3. Quick Analogy

. → “I already have the box, open it directly.”

-> → “I only have a map (address) to the box, follow it first, then open.”



---

## 4. Side-by-Side Example
```c
typedef struct
{
    int number;
} Node;

Node n;
n.number = 5;        // use .

Node *p = &n;
p->number = 10;      // use ->

printf("%i\n", n.number); // prints 10
```

---

## Rule of thumb:

Struct variable → .

Struct pointer → ->

