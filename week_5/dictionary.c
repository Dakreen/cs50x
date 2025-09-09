#include <ctype.h>    // for isalpha, toupper
#include <stdbool.h>  // for bool, true, false
#include <stdio.h>    // for file operations (fopen, fscanf, fclose)
#include <math.h>     // included but not needed
#include <stdlib.h>   // for malloc, free
#include <string.h>   // for strcpy
#include <strings.h>  // for strcasecmp (case-insensitive compare)
#include "dictionary.h" // constants like LENGTH and function prototypes

// ==========================================================
// CS50x – Problem Set 5: Speller
//
// Implements a dictionary using a hash table with linked lists.
// Strategy:
//   - Hash function maps words into 26^3 buckets (based on first 3 letters).
//   - Each bucket stores words in a linked list (chaining for collisions).
//   - check(): looks for a word in the correct bucket (case-insensitive).
//   - load(): reads all words from dictionary file into the hash table.
//   - size(): returns number of words loaded.
//   - unload(): frees all allocated memory.
//
// Result:
//   Provides O(1) average-time lookup for dictionary words, and
//   supports spell-checking large texts efficiently.
// ==========================================================

// Represents a node in a hash table (linked list element)
typedef struct node
{
    char word[LENGTH + 1];  // store the word (max LENGTH characters + '\0')
    struct node *next;      // pointer to the next node in the list
} node;

// Number of buckets in hash table (26^3 = 17,576)
const unsigned int N = 26 * 26 * 26;

// Hash table: array of pointers to linked lists
node *table[N];

// Global counter for words loaded
unsigned int word_counter = 0;

// ==========================================================
// check()
// Returns true if word is in dictionary, else false.
// Uses case-insensitive comparison with strcasecmp.
// ==========================================================
bool check(const char *word)
{
    int hash_num = hash(word);
    if (table[hash_num] == NULL)
    {
        return false;
    }
    else
    {
        node *tmp = table[hash_num];
        while (tmp != NULL)
        {
            if (strcasecmp(word, tmp->word) == 0)
            {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }
}

// ==========================================================
// hash()
// Hashes a word to a number between 0 and N-1.
// Uses up to the first three alphabetic characters of the word.
// ==========================================================
unsigned int hash(const char *word)
{
    int first = 0, second = 0, third = 0;
    int i = 0, j = 0;

    while (word[i] != '\0' && j < 3)
    {
        if (isalpha((unsigned char)word[i]))
        {
            if (j == 0)
            {
                first = toupper((unsigned char)word[i]) - 'A';
            }
            if (j == 1)
            {
                second = toupper((unsigned char)word[i]) - 'A';
            }
            if (j == 2)
            {
                third = toupper((unsigned char)word[i]) - 'A';
            }
            j++;
        }
        i++;
    }
    return (26 * 26 * first) + (26 * second) + third;
}

// ==========================================================
// insert_hash_table()
// Inserts a word into the hash table at the given bucket.
// Words are appended to the end of the linked list.
// ==========================================================
void insert_hash_table(const char *word, int hash_number)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("node cannot allocated memory.\n");
        return;
    }
    strcpy(n->word, word);
    n->next = NULL;
    if (table[hash_number] == NULL)
    {
        table[hash_number] = n;
    }
    else
    {
        node *tmp = table[hash_number];
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = n;
    }
}

// ==========================================================
// load()
// Loads dictionary into memory, returning true if successful.
// Reads each word from file, hashes it, and inserts into table.
// ==========================================================
bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    char format[5];
    snprintf(format, sizeof(format), "%%%ds", LENGTH);

    while (fscanf(source, format, word) != EOF)
    {
        word_counter++;
        int hash_num = hash(word);
        insert_hash_table(word, hash_num);
    }

    fclose(source);
    return true;
}

// ==========================================================
// size()
// Returns number of words in dictionary if loaded,
// else 0 if dictionary not yet loaded.
// ==========================================================
unsigned int size(void)
{
    return word_counter;
}

// ==========================================================
// unload()
// Frees all nodes in the hash table, releasing memory.
// Returns true if successful.
// ==========================================================
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
