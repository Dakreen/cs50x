📌 Notes: Linked List in C

1. What is a Linked List?

A dynamic data structure made of nodes.

Each node contains:

1. Data (e.g., an int).


2. A pointer to the next node.





---

2. Defining a Node

typedef struct node
{
    int number;           // data
    struct node *next;    // pointer to next node
}
node;


---

3. Creating a List

Start with an empty list:

node *list = NULL;   // head of the list

Add a first node:

node *n = malloc(sizeof(node));
n->number = 1;
n->next = NULL;
list = n;            // head points to first node

Add another node:

n = malloc(sizeof(node));
n->number = 2;
n->next = NULL;
list->next = n;      // link after first node

List now looks like:

list ──▶ [1 | *-] ──▶ [2 | NULL]


---

4. Traversing (Loop Through)

for (node *tmp = list; tmp != NULL; tmp = tmp->next)
{
    printf("%i\n", tmp->number);
}


---

5. Freeing (Avoid Memory Leaks)

while (list != NULL)
{
    node *tmp = list->next;  // save next
    free(list);              // free current
    list = tmp;              // move to next
}


---

6. Pros & Cons

✅ Flexible size (grow/shrink at runtime).
✅ Easy to insert/delete nodes.
❌ Uses more memory (extra pointers).
❌ Access is slower (must follow arrows, no direct indexing like arrays).


---

👉 Rule of thumb:

Use arrays when you need fast random access.

Use linked lists when you need fast insertions/deletions.

