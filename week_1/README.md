# CS50x – Week 1: Mario (More Comfortable)

## Goal

Build a **double half-pyramid** (à la *Super Mario Bros*) based on user input, using nested loops and formatted output.

## Description

This program prompts the user for a height between `1` and `8` and then prints a **side-by-side pyramid** of that height. Each level of the pyramid consists of hashes (`#`) aligned with the proper number of leading spaces. A gap of two spaces separates the left and right halves.

This is part of CS50x Week 1's problem set — “Mario (more comfortable)”.


## Logic

- Input is validated to accept integers between 1 and 8.
- For each row:
  - Print spaces on the left
  - Print `#` characters (left side)
  - Print 2 spaces
  - Print `#` characters (right side)

## Technologies

- Language: C
- Tools: CS50 Library (`cs50.h`), `clang` compiler
- Environment: [CS50.dev](https://cs50.dev) or local setup with CS50 lib installed

## Note

> This program uses the `cs50.h` library for simplified user input (`get_int()`).
> To compile it outside CS50.dev, make sure the CS50 library is installed — or rewrite input using standard C (`scanf()`).

## 📁 File

- `mario.c`: Main source code

## ✍️ Personal Note

> I found this problem quite easy — I already have some basic experience with programming, so working with loops and conditions felt natural. Still, it's a fun warm-up exercise before diving into more complex problems like “Credit”.

# CS50x – Week 1: Credit

## Goal

Implement a program in C that **validates credit card numbers** using [Luhn’s algorithm](https://en.wikipedia.org/wiki/Luhn_algorithm) and determines the **type of card** (AMEX, MASTERCARD, or VISA).

---

## Description

The program prompts the user to enter a credit card number. It then:

1. Checks the number of digits (must be 13, 15, or 16).
2. Uses **Luhn’s algorithm** to validate the checksum.
3. Determines the card type based on its **starting digits**:
   - AMEX: 15 digits, starts with `34` or `37`
   - MASTERCARD: 16 digits, starts with `51` through `55`
   - VISA: 13 or 16 digits, starts with `4`

If the number is invalid or does not match a known format, the program prints `INVALID`.

---

## How It Works

- The `numberLength()` function counts the digits of the card.
- The `checksum()` function applies Luhn’s algorithm:
  - Doubles every second digit from the right.
  - Adds the digits of those products.
  - Sums them with the digits in the odd positions.
  - Valid if the total ends in 0.
- The first one or two digits are extracted to identify the card type.

---

## Files

- `credit.c`: Main source code

---

## Requirements

- Language: C
- Libraries: `cs50.h`, `stdio.h`
- Environment: [CS50.dev](https://cs50.dev) or local setup with the CS50 library installed

---

## Note

> This program uses the `cs50.h` library for `get_long()`.  
> If you plan to compile it outside CS50.dev, you may need to:
> - Install the CS50 library manually  
> - Or replace `get_long()` with `scanf()` for portability

---

## Personal Note

> I found this problem a bit more interesting than Mario — it required some logical thinking and manipulating digits mathematically.  
> Luhn’s algorithm was simple once broken down, and structuring the conditions for each card type helped reinforce control flow using `if`, `else`, and helper functions.  
> 
> Also, I used the **debugging tool in VS Code for the first time** to inspect variables step by step and understand how values changed during loops. It really helped me catch mistakes and understand the program flow better.






