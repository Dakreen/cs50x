# Speller (CS50 Problem Set 5)

## Overview

This project is part of **CS50x Problem Set 5**.
It implements a **spell-checker** that verifies words in a text against a dictionary.

This repository only contains my work on `dictionary.c` and `dictionary.h`.
Other files (`speller.c`, test dictionaries, texts) were provided by CS50 staff and are not included here.

---

## How It Works

### Core Logic
- `dictionary.c` defines how the dictionary is:
  - Loaded into memory  
  - Searched for matches  
  - Unloaded (memory freed)  

### Data Structures
- **Hash table** of size 26³ (17,576 buckets)  
- Each bucket is a linked list of nodes:
  ```c
  char word[LENGTH + 1];
  struct node *next;
  ```

3. **Functions (dictionary.c)**
- `bool check(const char *word)` → searches for a word in the hash table.
- `unsigned int hash(const char *word)` → maps a word into a bucket index.
- `bool load(const char *dictionary)` → loads all words from the dictionary file.
- `unsigned int size(void)` → returns number of words loaded.
- `bool unload(void)` → frees memory used by the dictionary.
- `void insert_hash_table(const char *word, int hash_number)` → helper function that inserts a word into the correct bucket’s linked list

4. **Hashing Strategy**
- Uses the **first three alphabetic characters** of each word to compute the hash index.
- Formula: 
```
index = 26*26*first + 26*second + third
```
- Case-insensitive and ignores apostrophes.

---

## File Structure
- **dictionary.c** → my implementation.
- **dictionary.h** → header file with definitions.

---

## Notes
- **Design choice:** 26³ buckets balances memory and speed, while using linked lists to handle collisions.
- **Insert strategy** (`insert_hash_table`):
    - Appends words to the end of the linked list.
    - This makes insertion **O(n)** per bucket.
    - Prepending would improve to **O(1)** but appending was kept for clarity.

---

## Author
- **Name:** Jerome Henry
- **Date:** September 2025