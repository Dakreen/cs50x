🔤 Tries in C

1. What is a Trie?

A trie (from “retrieval”) is a tree-like data structure for storing strings (words).

Each node represents one character.

Paths from root → leaf form words.

Great for dictionaries, autocomplete, spell-checkers.



---

2. Structure of a Trie Node

Each node needs:

A flag is_word → true if path forms a complete word.

An array of children → one per possible character.



For English lowercase + apostrophe = 26 + 1 = 27 children.

typedef struct node
{
    bool is_word;
    struct node *children[27];  // 26 letters + apostrophe
} node;


---

3. Mapping a Character to Index

int char_to_index(char c)
{
    if (c == '\'')
        return 26;
    return tolower(c) - 'a';
}


---

4. Inserting a Word

bool insert(node *root, const char *word)
{
    node *cursor = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = char_to_index(word[i]);

        if (cursor->children[index] == NULL)
        {
            cursor->children[index] = calloc(1, sizeof(node));
            if (cursor->children[index] == NULL)
                return false;
        }
        cursor = cursor->children[index];
    }
    cursor->is_word = true;  // mark word end
    return true;
}


---

5. Searching for a Word

bool search(node *root, const char *word)
{
    node *cursor = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = char_to_index(word[i]);
        if (cursor->children[index] == NULL)
            return false;
        cursor = cursor->children[index];
    }
    return cursor->is_word;
}


---

6. Freeing a Trie

void free_trie(node *root)
{
    for (int i = 0; i < 27; i++)
    {
        if (root->children[i] != NULL)
            free_trie(root->children[i]);
    }
    free(root);
}


---

✅ Key Takeaways

A trie stores words by characters, not whole strings.

Super efficient for checking prefixes and words (time = length of word, not number of words).

Uses more memory than a hash table, but predictable lookup.

In CS50 speller, a trie is a good choice for storing the dictionary.

