# Substitution Cipher

**Author:** Dakreen  
**Date:** July 2025
**Course:** CS50x – Problem Set 2

---

## Overview
This program implements a **Substitution Cipher**, where each letter in the plaintext is replaced with a corresponding letter from a user-provided key.  
The key must contain all 26 letters of the English alphabet exactly once (case-insensitive) and can be provided in any order.

---

## Problem Solved
In classical cryptography, substitution ciphers provide a simple way to encrypt messages by substituting letters according to a fixed mapping.  
This program:
- Validates the encryption key before use.
- Preserves the case of each letter in the plaintext.
- Leaves non-alphabetic characters unchanged.

---

## How It Works
1. **User provides a key** as a command-line argument.
2. **Key validation** checks:
   - Length of exactly 26 characters.
   - All characters are alphabetic.
   - No duplicate letters (case-insensitive).
3. **Plaintext prompt** using the CS50 library’s `get_string()`.
4. **Encryption loop**:
   - For each alphabetic character, find its position in the alphabet.
   - Replace it with the letter at the same position in the key.
   - Preserve original case.
   - Copy non-alphabetic characters as-is.
5. Output the **ciphertext**.

---

## Key Functions
- `key_checker()` → Validates the encryption key for length, alphabetic characters, and uniqueness.
- `cipher()` → Applies the substitution cipher to the provided plaintext.

---

## Why This Project Is Interesting
- Reinforces string manipulation and validation logic.
- Demonstrates **character property handling** via `ctype.h` functions (`isalpha`, `toupper`, `tolower`).
- Introduces mapping between two alphabets using indexing.

---

## References
- [Substitution cipher – Wikipedia](https://en.wikipedia.org/wiki/Substitution_cipher)  
- [CS50x Problem Set 2 Specification](https://cs50.harvard.edu/x/)

---

## Note
This project was developed as part of **CS50x** while learning C.  
It uses the **CS50 Library** (`cs50.h`) for simplified input handling via `get_string()`.  
For production-grade code, you could replace this with standard C functions like `fgets()` and optimize encryption by **precomputing a mapping array** to achieve `O(n)` encryption.
