# Substitution Cipher (CS50 Problem Set 2)

## Overview
This program implements a **substitution cipher**.  
A substitution cipher replaces each letter of the plaintext with another letter according to a given key.  
The key must contain **26 unique alphabetic characters** (case-insensitive).  

The program preserves:
- Uppercase → stays uppercase  
- Lowercase → stays lowercase  
- Non-alphabetic characters → remain unchanged  

---

## How It Works

1. **Command-line Argument**
   - The program expects exactly one argument: the substitution key (26 unique letters).
   - Example valid keys:  
     ```
     NQXPOMAFTRHLZGECYJIUWSKDVB
     nqxpomaftrhlzgecyjiuwskdvb
     NqXpOmAfTrHlZgEcYjIuWsKdVb
     ```

2. **Key Validation**
   - Must be **26 characters long**.  
   - All characters must be alphabetic (A–Z or a–z).  
   - Each letter must appear **exactly once** (no duplicates).  

3. **Encryption**
   - Reads plaintext from the user (`get_string`).  
   - For each character:
     - If alphabetic → substitute with corresponding key letter (preserve case).  
     - If not alphabetic → leave as-is.  
   - Outputs the result as ciphertext.  

---

## File Structure
- **substitution.c** → main program
- Functions:
  - `main()` → handles input, validates key, manages flow.
  - `key_checker(string key)` → validates the key against the rules.
  - `cipher(string text, string key)` → applies substitution to produce ciphertext.

---

## Example Runs

```bash
$ ./substitution YTNSHKVEFXRBAUQZCLWDMIPGJO
plaintext:  HELLO
ciphertext: EHBBQ
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext:  hello, world
ciphertext: jrssb, ybwsp
$ ./substitution QWERTYUIOPASDFGHJKLZXCVBNM
plaintext:  CS50!
ciphertext: EQ50!
$ ./substitution ABC
Key must contain 26 characters.
```

---

## Notes
- Uses CS50’s `get_string()` for input.
- Validates command-line arguments before encrypting.
- Demonstrates **arrays**, **loops**, **conditionals**, and **string** handling in C.

---

## Author
- **Name:** Jerome Henry
- **Date:** July 2025

---

## Recruiter Note
This project demonstrates my ability to:
   - Implement **string validation** and error handling.
   - Work with **arrays** and **character manipulation** in C.
   - Preserve **case sensitivity and handle edge cases**.
   - Write **modular, well-documented code**.

It reflects my growing skills in algorithmic thinking and secure handling of text transformations — both useful in systems programming and cybersecurity.