# CS50x – Week 2: Substitution

## Goal

Create a program that encrypts plaintext using a **substitution cipher**, where each letter in the alphabet is replaced by a corresponding letter in a user-provided key.

## Description

This program takes a single command-line argument: a **26-character key** containing each letter of the alphabet exactly once.  
The key is case-insensitive but must be valid (alphabetic, no duplicates, correct length).

After validating the key, the program prompts the user for plaintext input and produces a ciphertext where each letter is substituted according to the key. The case of each letter is preserved, and non-alphabetical characters remain unchanged.

## Key Features

- Validates key (26 letters, all alphabetic, no duplicates)
- Preserves case (uppercase/lowercase)
- Ignores non-alphabetic characters
- Uses `cs50.h`, `ctype.h`, `string.h`

## Files

- `substitution.c`: Main source code

## How to Compile and Run

```bash
make substitution
./substitution NQXPOMAFTRHLZGECYJIUWSKDVB
```

## Note

This program uses `get_string()` from `cs50.h` to get user input.
To run it outside CS50.dev, make sure to:

Install the CS50 library, or

Replace `get_string()` with `fgets()` or `scanf()` as needed

## Personal Note

> I really enjoyed this problem because it involved combining **string validation**, **loop logic**, and **character manipulation**.  
> Writing the `key_checker()` function taught me how to catch invalid inputs and enforce constraints.  
> 
> 🧪 This was also my **first time working seriously with command-line arguments** in C. It helped me understand how programs can be customized and controlled directly from the terminal.
>  
> 💻 I also used the **debugger in VS Code again**, and it helped me track how characters were being mapped during encryption.  
> This kind of challenge is exactly why I like learning C — it's low-level but very satisfying when it works.



