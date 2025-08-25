📖 Dictionaries in C

1. What is a Dictionary?

A dictionary is a data structure that stores key → value pairs.

In C (no built-in type), you implement it yourself using:

Hash tables (most common).

Tries (great for words).

Or even binary search trees.




---

2. Basic Operations

Insert → add a key/value.

Search → check if key exists.

Delete → remove a key/value.

Load → read keys/values from a file.

Unload → free memory.



---

3. Using a Hash Table

A hash table is an array of linked lists.

Use a hash function to map the key (string) → index.

If multiple keys map to the same index → use a linked list to handle collisions.


// Node structure for linked list
typedef struct node
{
    char word[LENGTH + 1]; // key (example: dictionary word)
    struct node *next;
} node;

// Hash table
const unsigned int N = 1000;  // number of buckets
node *table[N];


---

4. Hash Function Example

unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % N;
}


---

5. Insert a Word

bool insert(const char *word)
{
    unsigned int index = hash(word);
    node *n = malloc(sizeof(node));
    if (n == NULL)
        return false;

    strcpy(n->word, word);
    n->next = table[index];
    table[index] = n;
    return true;
}


---

6. Search for a Word

bool check(const char *word)
{
    unsigned int index = hash(word);
    node *tmp = table[index];
    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}


---

7. Free the Dictionary

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


---

✅ Key Takeaways

A dictionary maps keys → values.

In C, you implement it with hash tables (fast) or tries (good for text).

Important for spell-checkers, databases, routing tables.

Core CS50 Problem Set 5 (Speller) is all about this.

