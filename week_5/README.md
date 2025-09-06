# Speller (CS50 Problem Set 5)

## Overview

This program implements a spell-checker that verifies words in a text against a dictionary.
The main logic is implemented in dictionary.c, which defines how the dictionary is stored, searched, and unloaded from memory.

Steps:
1. Load words from a **dictionary** file into a **hash table**.
2. For each word in a text, check if it exists in the **dictionary**.
3. Report misspelled words and **performance statistics**.

---

## How It Works

1. **Input**
- The program is run as: `./speller dictionary.txt text.txt`
- dictionary.txt → list of words used as reference.
- text.txt → text file to spell-check.

2. **Data Structures**
- Hash table of size 26^3 (17,576 buckets).
- Each bucket is a linked list of node structs, where each node stores:
- `char word[LENGTH + 1]`
- `struct node *next`

3. **Functions (dictionary.c)**
- `bool check(const char *word)` → searches for a word in the hash table.
- `unsigned int hash(const char *word)` → maps a word into a bucket index.
- `bool load(const char *dictionary)` → loads all words from the dictionary file.
- `unsigned int size(void)` → returns number of words loaded.
- `bool unload(void)` → frees memory used by the dictionary.

4. **Hashing Strategy**
- Uses the first three alphabetic characters of each word to compute the hash index.
- Formula: index = 26*26*first + 26*second + third
- Case-insensitive and ignores apostrophes.

---

## File Structure
- **dictionary.c** → my implementation (all main logic written here).
- **dictionary.h** → header file with definitions.
- **speller.c** → provided by CS50 staff (handles file I/O and testing, not modified).

## Example Run
```bash
$ ./speller dictionaries/large texts/lalaland.txt
MISSPELLED WORDS
...

WORDS MISSPELLED:     130
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        36742
TIME IN load:         0.12
TIME IN check:        0.08
TIME IN size:         0.00
TIME IN unload:       0.03
TIME IN TOTAL:        0.23
```
## Notes
- Work is focused only on **dictionary.c**.
- **speller.c and dictionary.h** were provided by CS50 and left unchanged.
- **Design choice: 26³ buckets** balances memory and speed, while using linked lists to handle collisions.
- **Potential improvements:** alternative hash functions for better distribution, inserting nodes at the head for faster load times.

---

## Author
- **Name:** Jerome Henry
- **Date:** September 2025