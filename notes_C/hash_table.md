# Hash Tables in C

## 1. What is a Hash Table?

A hash table is a data structure that maps keys → values.

Built from an array of buckets (fixed size).

Each bucket holds a linked list (or other structure) to handle collisions.

Super fast average lookup: O(1).



---

## 2. Structure in C

Each element is a node in a linked list.
```c
typedef struct node
{
    char word[LENGTH + 1];   // key (example: dictionary word)
    struct node *next;
} node;

const unsigned int N = 1000; // number of buckets
node *table[N];              // hash table: array of pointers to nodes
```

---

## 3. Hash Function

Converts a string into an index between 0 and N-1.
```c
unsigned int hash(const char *word)
{
    unsigned long h = 5381;
    int c;
    while ((c = *word++))
        h = ((h << 5) + h) + c;  // h * 33 + c
    return h % N;
}
```
Same word → always same index.

Different words → ideally different indices.

If collision → store multiple words in same bucket (linked list).



---

## 4. Insert into Hash Table
```c
bool insert(const char *word)
{
    unsigned int index = hash(word);

    node *n = malloc(sizeof(node));
    if (n == NULL)
        return false;

    strcpy(n->word, word);
    n->next = table[index];   // point to current head of list
    table[index] = n;         // new node becomes new head
    return true;
}
```

---

## 5. Search in Hash Table
```c
bool check(const char *word)
{
    unsigned int index = hash(word);

    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
            return true;
    }
    return false;
}
```

---

## 6. Free Hash Table
```c
void unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            node *next = tmp->next;
            free(tmp);
            tmp = next;
        }
    }
}
```

---

✅ Key Takeaways

Hash function → maps key to index.

Collisions → solved by chaining (linked lists).

Insert/Search/Delete all very fast on average.

Needs good hash function + enough buckets to reduce collisions.

Used everywhere: dictionaries, caches, routing tables, databases.

